#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"

typedef unsigned char byte;

typedef struct _value_field{
    byte address;
    byte rows;
    byte cols;
} Field;

typedef struct _LCD{
    Field* value;
} LCD;


static inline void __constructor(LCD* lcd, byte, byte, byte);
static inline void __destructor(LCD* lcd);

LCD* New(byte address, byte rows, byte cols);
void Del(LCD* lcd);