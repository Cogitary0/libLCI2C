#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "builtins.h"

using byte = unsigned char;
using uint = unsigned int;

class LC_I2C{

    public:
        LC_I2C(const byte address, const byte cols, const byte rows);
        ~LC_I2C() = default;

        void init(void);
        void clear(void);
        void reset(void)

        void set_display(bool flag);
        void set_backlight(bool flag); 

        inline void send_command(byte);


    private:
        inline void __send(byte, byte);
        inline void __write_4bits(byte);
        inline void __write(byte);
        inline void __pulse(byte);

        const byte __address;
        const byte __rows;
        const byte __cols;

        byte __display_function;
        byte __display_control;
        byte __display_mode;
        byte __backlight_value;
};