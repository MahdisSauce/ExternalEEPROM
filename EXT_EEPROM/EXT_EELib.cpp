#include "EXT_EELib.h"

EXT_EEPROM::EXT_EEPROM(byte w, byte x, byte y, byte z){
    CHIP_SEL = w; 
    CLOCK = x;             
    DATA_OUT = y;
    DATA_IN = z;
    
    pinMode(CLOCK, OUTPUT);
    pinMode(DATA_OUT, OUTPUT);
    pinMode(DATA_IN, INPUT);
    pinMode(CHIP_SEL, OUTPUT);
    digitalWrite(CHIP_SEL, LOW);
}

byte EXT_EEPROM::readEEPROM(byte address){
     byte READ  = 0b1100;
     char incoming; 
     digitalWrite(CHIP_SEL, HIGH);
     shiftOut(DATA_OUT, CLOCK, MSBFIRST, READ); //sending WRITE instruction 
     shiftOut(DATA_OUT, CLOCK, MSBFIRST, address);   //sending low address
     incoming = shiftIn(DATA_IN, CLOCK, MSBFIRST); //sendind data
     delay(20);
     digitalWrite(CHIP_SEL, LOW);
     delay(2);
     return incoming;
}

void EXT_EEPROM::writeEEPROM(byte address, byte value){
    byte WRITE = 0b1010; 
    digitalWrite(CHIP_SEL, HIGH);
    shiftOut(DATA_OUT,CLOCK, MSBFIRST, WRITE); //sending WRITE instruction 
    shiftOut(DATA_OUT,CLOCK, MSBFIRST, address);   //sending low address
    shiftOut(DATA_OUT,CLOCK, MSBFIRST, value); //sendind data
    digitalWrite(CHIP_SEL, LOW);
    delay(100);
}

void EXT_EEPROM::enableWrite(){
    byte EWEN  = 0b10011000;                //erase write enable instruction
    digitalWrite(CHIP_SEL, HIGH);                  
    shiftOut(DATA_OUT,CLOCK, MSBFIRST, EWEN);     //sending EWEN instruction
    shiftOut(DATA_OUT,CLOCK, MSBFIRST, 0b0000); //the last 4 bits of EWEN ins  
    digitalWrite(CHIP_SEL, LOW);
    delay(10);
}

void EXT_EEPROM::disableWrite(){
    byte EWDS  = 0b10000;                //erase write enable instruction
    digitalWrite(CHIP_SEL, HIGH);                  
    shiftOut(DATA_OUT,CLOCK,MSBFIRST,EWDS);     //sending EWEN instruction
    shiftOut(DATA_OUT,CLOCK,MSBFIRST,0b0000); //the last 4 bits of EWEN ins  
    digitalWrite(CHIP_SEL ,LOW);
    delay(10);
}
