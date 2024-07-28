#ifndef __LC_I2C_H__
#define __LC_I2C_H__

#include <inttypes.h>


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

#define EN B00000100
#define RW B00000010
#define RS B00000001
#define DF B00000000

using uint = uint8_t;


class LC_I2C
{
    public:
        LC_I2C(uint address, 
               uint cols,
               uint rows, 
               bool char_size = C_5x8_CHAR_SIZE, 
               bool backlight = C_BACKLIGHT_ON);

        void init   ();
        void clear  ();
        void reset  ();

        bool get_display    ();
        bool get_backlight  ();
        bool get_cursor     ();
        bool get_blink      ();

        void set_display    (bool flag);
        void set_backlight  (bool flag);
        void set_cursor     (bool flag);
        void set_blink      (bool flag);

        void create_char         (uint location, uint char_map[]);
        void set_position_cursor (uint col, uint row);
        void print               (const char *str);

        void send_command   (uint);
        void write          (uint);

    private:
        void __send         (uint, uint);
        void __write_4bits  (uint);
        void __write        (uint);
        void __pulse        (uint);

        uint __address;
        uint __display_function;
        uint __display_control;
        uint __display_mode;
        uint __char_size;
        uint __backlight_value;
        uint __cols;
        uint __rows;
};


#endif