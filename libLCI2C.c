#include "libLCI2C.h"

static inline void __constructor(LCD* lcd, byte ADDR, byte ROWS, byte COLS){
    lcd->value = malloc(sizeof(Field));

    if(lcd->value != NULL){
        lcd->value->address = ADDR;
        lcd->value->rows = ROWS;
        lcd->value->columns = COLS;
    }
    return;
}

static inline void __destructor(LCD* lcd){
    free(lcd->value);
    return;
}

LCD* New(byte address, byte rows, byte cols){
    LCD* lcd = malloc(sizeof(LCD));
    __constructor(lcd, address, rows, cols);
    return lcd;
}

void Del(LCD* lcd){
    __destructor(lcd);
    free(lcd);
    return;
}