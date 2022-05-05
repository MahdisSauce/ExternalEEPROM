#include "EXT_EELib.h"

void setup(){
    Serial.begin(9600);
}

EXT_EEPROM EEPROM1(4, 5, 6, 7);

void loop(){
    Serial.print(EEPROM1.readEEPROM(0), BIN);
    while(1);
}
