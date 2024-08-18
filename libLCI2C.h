#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "builtins.h"

using byte = unsigned char;
using uint = unsigned int;

class LCD{

    public:
        LCD(const byte address, const byte cols, const byte rows);
        ~LCD() = default;

        void init   (void);
        void clear  (void);
        void reset  (void);

        void create_char            (byte location, byte* char_map);
        void print_char             (byte location, byte* char_map);
        void set_position_cursor    (byte col, byte row);
        void print                  (const char* str);

        void scroll_display         (DIRECTION dir);
        void scroll_display_left    (void);
        void scroll_display_right   (void);        


        void set_display    (bool flag);
        void set_backlight  (bool flag); 
        void set_blink      (bool flag);
        void set_cursor     (bool flag); 

        bool get_display    (void);
        bool get_backlight  (void);
        bool get_blink      (void);
        bool get_cursor     (void);

        inline void send_command    (byte);
        inline void write           (byte);


    private:
        static inline void __send          (byte, byte);
        static inline void __write_4bits   (byte);
        static inline void __write         (byte);
        static inline void __pulse         (byte);

        const byte address;
        const byte rows;
        const byte cols;

        byte display_function;
        byte display_control;
        byte display_mode;
        byte backlight_value;
        byte display_value;

        byte pos_x;
        byte pos_y;
};