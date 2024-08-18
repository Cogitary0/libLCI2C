#pragma once

#include <Wire.h>

inline void WIRE_BEGIN(void){
    Wire.begin();
} 

inline void WIRE_BEGINTRANSMISSION(byte ADDR){
    Wire.beginTransmission(ADDR);
}

inline void WIRE_WRITE(byte DATA){
    Wire.wire(DATA);
}

inline void WIRE_ENDTRANSMISSION(void){
    Wire.endTransmission();
}