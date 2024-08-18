#include "libLCI2C.h"


LCD::LCD(const byte address, const byte cols, const byte rows)
:   address(address), 
    cols(cols), 
    rows(rows), 
    backlight_value(C_BACKLIGHT_ON){}


void LCD::init(){
    WIRE_BEGIN();
    
    this->display_function = C_4_BIT_MODE | C_ON_1_LINE | C_5x8_CHAR_SIZE;

    if(this->rows > 1)
    {
        this->display_function |= C_ON_2_LINE;
    }

    delay(50);

    __write(backlight_value);
    delay(1000);

    __write_4bits(C_LCD_SETUP_FUNCTION_SET);//(0x03 << 4);
    delayMicroseconds(4500);
    __write_4bits(C_LCD_SETUP_FUNCTION_SET);//(0x03 << 4);
    delayMicroseconds(4500);
    __write_4bits(C_LCD_SETUP_FUNCTION_SET);//(0x03 << 4);
    delayMicroseconds(150);

    __write_4bits(C_LCD_SETUP_4BIT_INTERFACE);

    send_command(C_FUNCTION_SET | this->display_function);

    set_display(true);

    clear();

    this->display_mode = C_ENTRY_LEFT | C_ENTRY_SHIFT_DECREMENT;
    
    send_command(C_ENTRY_MODE_SET | this->display_mode);

    reset();
}


///============ BASIC ===============///

void LCD::reset(){
    this->pos_x = 0;
    this->pos_y = 0;
    send_command(C_RETURN_HOME);
    delayMicroseconds(1530); //~1.52(+-0.01) ms
}


void LCD::clear(){
    send_command(C_DISPLAY_CLEAR);
    delayMicroseconds(2000);
}


void LCD::scroll_display(DIRECTION dir){
    send_command(C_CURSOR_SHIFT | C_DISPLAY_MOVE | dir);
}

void LCD::scroll_display_left(void){
    scroll_display(LEFT);
}

void LCD::scroll_display_right(void){
    scroll_display(RIGHT);
}


///============== CHAR ================///

void LCD::create_char(byte location, byte* char_map){
    location &= 0x7;
    send_command(C_SET_CGRAM_ADDR | (location << 3));
    for(byte i = 0;  i < 8; i++){
        write(char_map[i]);
    }
}

void LCD::set_position_cursor(byte col, byte row){
    row = (row > this->rows - 1)? this->rows - 1 : row;
    send_command(C_SET_DDRAM_ADDR | (col + ROW_SETS[row]));
}

void LCD::print_char(byte location, byte* char_map){
    create_char(location, char_map);
    reset();
    write(location);
}

void LCD::print(const char* str){
    while(*str){
        write(*str);
        str++;
    }
}



///============ SETs ===============///

void LCD::set_display(bool flag){
    this->display_control |= (flag)? C_DISPLAY_ON : C_DISPLAY_OFF;
    send_command(C_DISPLAY_CONTROL | this->display_control);
}


void LCD::set_backlight(bool flag){
    this->display_control |= (flag)? C_BACKLIGHT_ON : C_BACKLIGHT_OFF;
    send_command(C_DISPLAY_CONTROL | this->display_control);
}


void LCD::set_cursor(bool flag){
    this->display_control  |= (flag)? C_CURSOR_ON : C_CURSOR_OFF;
    send_command(C_DISPLAY_CONTROL | this->display_control);

}

void LCD::set_blink(bool flag){
    this->display_control |= (flag)? C_BLINK_ON : C_BLINK_OFF;
    send_command(C_DISPLAY_CONTROL | this->display_control);
}



///=========== GETTERS ================///

bool LCD::get_display(void){
    return (C_DISPLAY_ON & this->display_control) != 0;
}

bool LCD::get_backlight(void){
    return (C_BACKLIGHT_ON == this->backlight_value);
}

bool LCD::get_blink(void){
    return (C_BLINK_ON & this->display_control) != 0;
}

bool LCD::get_cursor(void){
    return (C_CURSOR_ON & this->display_control) != 0;
}


///============ SEND COMMAND ==========///

inline void LCD::send_command(byte command){
    __send(command, DF);
}


inline void LCD::write(byte data){
    __send(data, RS);
}



/// PRIVATE FUNC

inline void LCD::__send(byte value, byte mode){
    byte HIGH_BIT = value & 0xF0;
    byte LOW_BIT = (value<<4) & 0xF0;
    __write_4bits((HIGH_BIT) | mode);
    __write_4bits((LOW_BIT) | mode);
}

inline void LCD::__write_4bits(byte value){
    __write(value);
    __pulse(value);
}

inline void LCD::__pulse(byte data){
    __write(data | EN);
    delayMicroseconds(1);

    __write(data & ~EN);
    delayMicroseconds(50);
}

inline void LCD::__write(byte data){
    WIRE_BEGINTRANSMISSION(this->address);
    WIRE_WRITE(data | this->backlight_value);
    WIRE_ENDTRANSMISSION();
}