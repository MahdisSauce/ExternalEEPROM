#ifndef EXT_EELIB_H
#define EXT_EELIB_H
#include <Arduino.h>

class EXT_EEPROM{
    private:
        //Declaring pin variables
        byte CHIP_SEL;  //On EEPROM pin 1
        byte CLOCK;     //On EEPROM pin 2       
        byte DATA_OUT;  //Sending from Arduino to EEPROM
        byte DATA_IN;   //Receiving from EEPROM to Arduino
    
    public:

        EXT_EEPROM(byte w, byte x, byte y, byte z); //Initializes EEPROM
        
        byte readEEPROM(byte address);  //Reads selected byte from the EEPROM

        void writeEEPROM(byte address, byte value); //Write byte to EERPOM 
        
        void enableWrite(); //Enables writing to EEPROM
        
        void disableWrite();    //Disables writing to EEPROM
};

#endif
