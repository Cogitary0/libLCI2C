#pragma once

enum {
    EN = B00000100,
    RW = B00000010,
    RS = B00000001,
    DF = B00000000
}

enum {
    // DISPLAY
    C_DISPLAY_ON    =   0x04,
    C_DISPLAY_OFF   =   0x00,
    C_BACKLIGHT_ON  =   0x08,
    C_BACKLIGHT_OFF =   0x00,
    C_BLINK_ON      =   0x01,
    C_BLINK_OFF     =   0x00,
    C_CURSOR_OFF    =   0x00,
    C_CURSOR_ON     =   0x02,

    // FUNCTION SET
    C_4_BIT_MODE   =   0x00,
    C_8_BIT_MODE   =   0x10,
    C_ON_1_LINE    =   0x00,
    C_ON_2_LINE    =   0x08,
    C_5x8_CHAR_SIZE   =   0x00,
    C_5x10_CHAR_SIZE  =   0x04,

    // MOVEMENT ON DISPLAY
    C_ENTRY_LEFT            =   0x02,
    C_ENTRY_RIGHT           =   0x00,
    C_ENTRY_SHIFT_INCREMENT =   0x01,
    C_ENTRY_SHIFT_DECREMENT =   0x00,

    // COMMANDS
    C_FUNCTION_SET      =   0x20,
    C_DISPLAY_CLEAR     =   0x01,
    C_RETURN_HOME       =   0x02,
    C_DISPLAY_CONTROL   =   0x08,
    C_ENTRY_MODE_SET    =   0x04, 

    C_3BITS_4BSHIFT_RIGHT   =   0x40,
    C_2BITS_4BSHIFT_RIGHT   =   0x20,

    C_SET_CGRAM_ADDR = 0x40,
    C_SET_DDRAM_ADDR = 0x80,

    C_LCD_SETUP_FUNCTION_SET = 0x30,
    C_LCD_SETUP_4BIT_INTERFACE = 0x20,

    C_LCD_ADDR_0LINE = 0x00,
    C_LCD_ADDR_1LINE = 0x40,
    C_LCD_ADDR_2LINE = 0x14,
    C_LCD_ADDR_3LINE = 0x54,
};

