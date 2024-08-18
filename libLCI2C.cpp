#include "libLCI2C.h"


LC_I2C::LC_I2C(byte address, byte cols, byte rows)
: __address(address), __cols(cols), __rows(rows){}


void LC_I2C::init(){
    WIRE_BEGIN();
    
    __display_function = C_4_BIT_MODE | C_ON_1_LINE | C_5x8_CHAR_SIZE;

    if(__rows > 1)
    {
        __display_function |= C_ON_2_LINE;
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

    set_display(true);

    clear();

    __display_mode = C_ENTRY_LEFT | C_ENTRY_SHIFT_DECREMENT;
    
    send_command(C_ENTRY_MODE_SET | __display_mode);

    reset();
}


void LC_I2C::reset(){
    send_command(C_RETURN_HOME);
    delayMicroseconds(1530); //~1.52(+-0.01) ms
}


void LC_I2C::clear(){
    send_command(C_DISPLAY_CLEAR);
    delayMicroseconds(2000);
}


void LC_I2C::set_display(bool flag){
    __display_control |= (flag)? C_DISPLAY_ON : C_DISPLAY_OFF;
    send_command(C_DISPLAY_CONTROL | __display_control);
}


void LC_I2C::set_backlight(bool flag){
    __display_control |= (flag)? C_BACKLIGHT_ON : C_BACKLIGHT_OFF;
    send_command(C_DISPLAY_CONTROL | __display_control);
}



inline void LC_I2C::send_command(byte command){
    __send(command, DF);
    return;
}


/// PRIVATE FUNC

inline void LC_I2C::__send(byte value, byte mode){
    byte HIGH_BIT = value & 0xF0;
    byte LOW_BIT = (value<<4) & 0xF0;
    __write_4bits((HIGH_BIT) | mode);
    __write_4bits((LOW_BIT) | mode);
}

inline void LC_I2C::__write_4bits(byte value){
    __write(value);
    __pulse(value);
}

inline void LC_I2C::__pulse(byte data){
    __write(data | EN);
    delayMicroseconds(1);

    __write(data & ~EN);
    delayMicroseconds(50);
}

inline void LC_I2C::__write(bye data){
    WIRE_BEGINTRANSMISSION(__address);
    WIRE_WRITE(data | __backlight_value);
    WIRE_ENDTRANSMISSION();
}