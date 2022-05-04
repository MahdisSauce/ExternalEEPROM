class EXT_EEPROM{
    public:
        int CHIP_SEL;
        int CLOCK;             
        int DATA_OUT;
        int DATA_IN;

        EXT_EEPROM(int w, int x, int y, int z){
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
        
        byte readEEPROM(byte address){
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

        void writeEEPROM(byte address, byte value){
            byte WRITE = 0b1010; 
            digitalWrite(CHIP_SEL, HIGH);
            shiftOut(DATA_OUT,CLOCK, MSBFIRST, WRITE); //sending WRITE instruction 
            shiftOut(DATA_OUT,CLOCK, MSBFIRST, address);   //sending low address
            shiftOut(DATA_OUT,CLOCK, MSBFIRST, value); //sendind data
            digitalWrite(CHIP_SEL, LOW);
            delay(100);
        }
        
        void enableWrite(){
            byte EWEN  = 0b10011000;                //erase write enable instruction
            digitalWrite(CHIP_SEL, HIGH);                  
            shiftOut(DATA_OUT,CLOCK, MSBFIRST, EWEN);     //sending EWEN instruction
            shiftOut(DATA_OUT,CLOCK, MSBFIRST, 0b0000); //the last 4 bits of EWEN ins  
            digitalWrite(CHIP_SEL, LOW);
            delay(10);
        }
        
        void disableWrite(){
            byte EWDS  = 0b10000;                //erase write enable instruction
            digitalWrite(CHIP_SEL, HIGH);                  
            shiftOut(DATA_OUT,CLOCK,MSBFIRST,EWDS);     //sending EWEN instruction
            shiftOut(DATA_OUT,CLOCK,MSBFIRST,0b0000); //the last 4 bits of EWEN ins  
            digitalWrite(CHIP_SEL ,LOW);
            delay(10);
        }
};



void setup(){
    Serial.begin(9600);
    
 }
 
void loop()
{
    byte Data[] = {B01111100,B11111110,B00011111,B00011111,B11111111,B11111110,B11101110,B11101110};
    EXT_EEPROM eeprom1(2, 3, 4, 5);
//    eeprom1.enableWrite();
//    Serial.println("Writing to EEPROM");
//    Serial.println();
//    for(int i = 0; i < 8; i++){
//        eeprom1.writeEEPROM(i, Data[i]);
//        eeprom1.writeEEPROM((i+8), 0);
//    }
//    eeprom1.disableWrite();
    
    Serial.println("Reading from EEPROM");
    for(int i = 0; i < 8; i++){
        Serial.print((String)"Address " + i + ": ");
        Serial.println(eeprom1.readEEPROM(i), BIN);
    }
    while(1);
}
