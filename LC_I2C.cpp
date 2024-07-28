#include "LCI2C.h"

#include <Wire.h>
#include <inttypes.h>
#include <Arduino.h>

LC_I2C::LC_I2C(uint address, 
               uint cols, 
               uint rows, 
               bool char_size,
               bool backlight) 
               : __address(address),
                 __cols(cols),
                 __rows(rows),
                 __char_size(char_size),
                 __backlight_value(backlight) {}


void LC_I2C::init()
{
    Wire.begin();

    __display_function = C_4_BIT_MODE | C_ON_1_LINE | C_5x8_CHAR_SIZE;

    if(__rows > 1)
    {
        __display_function |= C_ON_2_LINE;
    }

    if((__char_size != 0) && (__rows == 1))
    {
        __display_function |= C_5x8_CHAR_SIZE;
    }

    delay(50);

    __write(__backlight_value);
    delay(1000);

    __write_4bits(C_LCD_SETUP_FUNCTION_SET);//(0x03 << 4);
    delayMicroseconds(4500);
    __write_4bits(C_LCD_SETUP_FUNCTION_SET);//(0x03 << 4);
    delayMicroseconds(4500);
    __write_4bits(C_LCD_SETUP_FUNCTION_SET);//(0x03 << 4);
    delayMicroseconds(150);

    __write_4bits(C_LCD_SETUP_4BIT_INTERFACE);

    send_command(C_FUNCTION_SET | __display_function);

    // turn the display on with no cursor or blinking default
    __display_control = C_DISPLAY_ON | C_CURSOR_OFF | C_BLINK_OFF;
    set_display(true);

    clear();

    __display_mode = C_ENTRY_LEFT | C_ENTRY_SHIFT_DECREMENT;
    
    send_command(C_ENTRY_MODE_SET | __display_mode);

    reset();
}


void LC_I2C::reset(){
    send_command(C_RETURN_HOME);
    delayMicroseconds(1530); ///~1.52(+-0.01)ms
}


void LC_I2C::clear(){
    send_command(C_DISPLAY_CLEAR);
    delayMicroseconds(2000);
}


void LC_I2C::set_position_cursor(uint col, uint row){
    // send_command(C_SET_CURSOR | (x << 8) | y);
    static const uint ROW_SETS[] = {C_LCD_ADDR_0LINE, C_LCD_ADDR_1LINE,
                                    C_LCD_ADDR_2LINE, C_LCD_ADDR_3LINE};
    row = (row > __rows - 1) ? __rows -1 : row;
    send_command(C_SET_DDRAM_ADDR | (col + ROW_SETS[row]));
}


void LC_I2C::set_display(bool flag){
    if(flag){
        __display_control |= C_DISPLAY_ON;
    } else {
        __display_control &= C_DISPLAY_ON;
    }
    send_command(C_DISPLAY_CONTROL | __display_control);
}


void LC_I2C::set_cursor(bool flag){
    // if(flag){
    //     __display_control |= C_CURSOR_ON;
    // } else {
    //     __display_control &= C_CURSOR_ON;
    // }
    __display_control |= (flag)? C_CURSOR_ON : C_CURSOR_OFF;
    send_command(C_DISPLAY_CONTROL | __display_control);
}


void LC_I2C::set_blink(bool flag){
    __display_control |= (flag)? C_BLINK_ON : C_BLINK_OFF;
    send_command(C_DISPLAY_CONTROL | __display_control);
}


void LC_I2C::set_backlight(bool flag){
    __display_control |= (flag)? C_BACKLIGHT_ON : C_BACKLIGHT_OFF;
    send_command(C_DISPLAY_CONTROL | __display_control);
}


bool LC_I2C::get_backlight(void){
    return (C_BACKLIGHT_ON == __backlight_value);
}


bool LC_I2C::get_blink(void){
    return (C_BLINK_ON & __display_control) != 0;
}


bool LC_I2C::get_cursor(void){
    return (C_CURSOR_ON & __display_control) != 0;
}


bool LC_I2C::get_display(void){
    return (C_DISPLAY_ON & __display_control) != 0;
}


void LC_I2C::create_char(uint location, uint char_map[]){
    location &= 0x7;
    send_command(C_SET_CGRAM_ADDR | (location << 3));
    for(uint i = 0; i < 8; ++i){
        write(char_map[i]);
    }
}


void LC_I2C::print(const char* str){
    while(*str){
        write(*str);
        str++;
    }
}

inline void LC_I2C::send_command(uint value){
    __send(value, DF);
}


inline void LC_I2C::write(uint value){
    __send(value, RS);
}


void LC_I2C::__send(uint value, uint mode){
    uint HIGH_BIT = value&0xf0;
    uint LOW_BIT = (value<<4)&0xf0;
    __write_4bits((HIGH_BIT) | mode);
    __write_4bits((LOW_BIT) | mode);
}


void LC_I2C::__write_4bits(uint value){
    __write(value);
    __pulse(value);
}

void LC_I2C::__pulse(uint data){
    __write(data | EN);
    delayMicroseconds(1);

    __write(data & ~EN);
    delayMicroseconds(50);
}


void LC_I2C::__write(uint data){
    Wire.beginTransmission(__address);
    Wire.write((int)(data) | __backlight_value);
    Wire.endTransmission();
}

// bool LC_I2C::get_blink(void){
//     send_command(C_DISPLAY_CONTROL);
//     uint8_t status = __read();
//     return (status & C_BLINK_ON) != 0;
// }

// uint LC_I2C::__read(void){
//     Wire.beginTransmission(__address);
//     Wire.write(0x00);
//     Wire.endTransmission();
//     Wire.requestFrom(__address, 1);
//     return Wire.read();
// }


