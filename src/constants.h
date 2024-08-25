#pragma once

#define EN B00000100
#define RW B00000010
#define RS B00000001
#define DF B00000000

enum MODE{
    OFF,
    ON
};

enum DIRECTION {
    LEFT = 0x00,
    RIGHT = 0x04
};

// enum class SET_DISPLAY{
//     DISPLAY_ON    =   0x04,
//     DISPLAY_OFF   =   0x00,
//     BACKLIGHT_ON  =   0x08,
//     BACKLIGHT_OFF =   0x00,
//     BLINK_ON      =   0x01,
//     BLINK_OFF     =   0x00,
//     CURSOR_OFF    =   0x00,
//     CURSOR_ON     =   0x02
// };

// enum class FUNCTION_SET_DISPLAY{
//     SET_4_BIT_MODE   =   0x00,
//     SET_8_BIT_MODE   =   0x10,
//     SET_ON_1_LINE    =   0x00,
//     SET_ON_2_LINE    =   0x08,
//     SET_5x8_CHAR_SIZE   =   0x00,
//     SET_5x10_CHAR_SIZE  =   0x04,
// };

// enum class MOVEMENT_ON_DISPLAY{
//     ENTRY_LEFT            =   0x02,
//     ENTRY_RIGHT           =   0x00,
//     ENTRY_SHIFT_INCREMENT =   0x01,
//     ENTRY_SHIFT_DECREMENT =   0x00,
//     CURSOR_SHIFT          =   0x10,
// };

// enum class COMMANDS_DISPLAY{
//     FUNCTION_SET      =   0x20,
//     DISPLAY_CLEAR     =   0x01,
//     RETURN_HOME       =   0x02,
//     DISPLAY_CONTROL   =   0x08,
//     ENTRY_MODE_SET    =   0x04, 

//     _3BITS_4BSHIFT_RIGHT   =   0x40,
//     _2BITS_4BSHIFT_RIGHT   =   0x20,

//     SET_CGRAM_ADDR = 0x40,
//     SET_DDRAM_ADDR = 0x80,

//     LCD_SETUP_FUNCTION_SET = 0x30,
//     LCD_SETUP_4BIT_INTERFACE = 0x20
// };

// enum class ADDR_LINE_DISPLAY{
//     ADDR_0LINE = 0x00,
//     ADDR_1LINE = 0x40,
//     ADDR_2LINE = 0x14,
//     ADDR_3LINE = 0x54,
// };

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
    C_CURSOR_SHIFT          =   0x10,
    C_DISPLAY_MOVE          =   0x08,

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

static const unsigned char ROW_SETS[4] = {C_LCD_ADDR_0LINE, C_LCD_ADDR_1LINE,
                                          C_LCD_ADDR_2LINE, C_LCD_ADDR_3LINE};