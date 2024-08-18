#pragma once

#include <Wire.h>
#include <Arduino.h>

inline void WIRE_BEGIN(void){
    Wire.begin();
} 

inline void WIRE_BEGINTRANSMISSION(byte ADDR){
    Wire.beginTransmission(ADDR);
}

inline void WIRE_WRITE(byte DATA){
    Wire.write(DATA);
}

inline unsigned char WIRE_ENDTRANSMISSION(void){
    Wire.endTransmission();
}
