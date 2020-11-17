
/* Function commands and ROM commands for ds18b20*/
#define THERM_CMD_CONVERTTEMP 0x44
#define THERM_CMD_RSCRATCHPAD 0xbe
#define THERM_CMD_WSCRATCHPAD 0x4e
#define THERM_CMD_CPYSCRATCHPAD 0x48
#define THERM_CMD_RECEEPROM 0xb8
#define THERM_CMD_RPWRSUPPLY 0xb4
#define THERM_CMD_SEARCHROM 0xf0
#define THERM_CMD_READROM 0x33
#define THERM_CMD_MATCHROM 0x55
#define THERM_CMD_SKIPROM 0xcc
#define THERM_CMD_ALARMSEARCH 0xec


#define F_CPU 48000000UL //Your clock speed in Hz (48Mhz here)   
#define LOOP_CYCLES 8 //Number of cycles that the loop takes
#define us(num) (num/(LOOP_CYCLES*(1/(F_CPU/1000000.0))))


/* defines for ports and pin*/
#define THERM_PORT PORT[0]
#define THERM_PIN PORT_PA16  // (16ul)
#define THERM_DQ (16ul) // PIN D8 Mkr 1010 Wi-Fi
/* Utils */
#define THERM_INPUT_MODE() PORT->Group[0].PINCFG[16].reg = PORT_PINCFG_INEN // == 1    // PIN D8 as input
#define THERM_OUTPUT_MODE() PORT->Group[0].DIRSET.reg = THERM_PIN // PIN D8 as output // kan vara DIR0 istället för DIRSET
#define THERM_LOW() PORT->Group[0].OUTCLR.reg = THERM_PIN //PORT->Group[0].OUTCLR.reg     //THERM_PORT&=~(1<<THERM_DQ)
#define THERM_HIGH() PORT->Group[0].OUTSET.reg = THERM_PIN //PORT->Group[0].OUTSET.reg     //THERM_PORT|=(1<<THERM_DQ)

//inline __attribute__((gnu_inline)) void therm_delay(uint16_t delay){
//while(delay--) asm volatile("nop");
//}

uint8_t therm_reset(){
  uint8_t i;
  //Pull line low and wait for 480uS
  THERM_LOW();
  THERM_OUTPUT_MODE();
  delayMicroseconds(480);//therm_delay(us(480));
  //Release line and wait for 60uS
  THERM_INPUT_MODE();
  delayMicroseconds(60);//therm_delay(us(60));
  //Store line value and wait until the completion of 480uS period
  i = PORT->Group[0].IN.reg & THERM_PIN; //osäker          //(THERM_PIN & (1<<THERM_DQ));
  delayMicroseconds(420);//therm_delay(us(420));
  //Return the value read from the presence pulse (0=OK, 1=WRONG)
 // Serial.println("reset");
  return i;
}

void therm_write_bit(uint8_t bit){
  //Pull line low for 1uS
  THERM_LOW();
  THERM_OUTPUT_MODE();
  delayMicroseconds(1);//therm_delay(us(1));
  //If we want to write 1, release the line (if not will keep low)
  if(bit) THERM_INPUT_MODE();
  //Wait for 60uS and release the line
  delayMicroseconds(60);//therm_delay(us(60));
  //Serial.println("write bit");
  THERM_INPUT_MODE();
}
uint8_t therm_read_bit(void){
  uint8_t bit=0;
  //Pull line low for 1uS
  THERM_LOW();
  THERM_OUTPUT_MODE();
  delayMicroseconds(1);//therm_delay(us(1));
  //Release line and wait for 14uS
  THERM_INPUT_MODE();
  delayMicroseconds(14);//therm_delay(us(14));
  //Read line value
  //if (PORT->Group[0].IN.reg & (1<<8)) bit=1; //((PORT->Group[0].IN.reg & PORT_PA16)== 1)  //(THERM_PIN&(1<<THERM_DQ)) 
  if((REG_PORT_IN0 & PORT_PA16)!=0)
  //Wait for 45uS to end and return read value
  delayMicroseconds(45);//therm_delay(us(45));
  //Serial.println("read bit");
  Serial.println(PORT->Group[0].IN.reg);
  Serial.println(REG_PORT_IN0);
  //Serial.println(digitalRead(8));

  return bit;  // returnar 0 hela tiden
}
uint8_t therm_read_byte(void){
  uint8_t i=8, n=0;
  while(i--){
    //Shift one position right and store read value
    n>>=1;
    n|=(therm_read_bit()<<7);
  }
  return n;
}
void therm_write_byte(uint8_t byte){
  uint8_t i=8;
  while(i--){
    //Write actual bit and shift one position right to make the next bit ready
    therm_write_bit(byte&1);
    byte>>=1;
  }
}
#define THERM_DECIMAL_STEPS_12BIT 625 //.0625
void therm_read_temperature(char *buffer){
  // Buffer length must be at least 12bytes long! ["+XXX.XXXX C"]
  uint8_t temperature[2];
  int8_t digit;
  uint16_t decimal;
 
 
  //Reset, skip ROM and start temperature conversion
  therm_reset();
  therm_write_byte(THERM_CMD_SKIPROM);
  therm_write_byte(THERM_CMD_CONVERTTEMP);

  //Wait until conversion is complete
  while(!therm_read_bit());  // fastnar här
  
  //Reset, skip ROM and send command to read Scratchpad
  therm_reset();
  therm_write_byte(THERM_CMD_SKIPROM);
  therm_write_byte(THERM_CMD_RSCRATCHPAD);
  //Read Scratchpad (only 2 first bytes)
  temperature[0]=therm_read_byte();
  temperature[1]=therm_read_byte();
  therm_reset();
  //Store temperature integer digits and decimal digits
  digit=temperature[0]>>4;
  digit|=(temperature[1]&0x7)<<4;
  //Store decimal digits
  decimal=temperature[0]&0xf;
  decimal*=THERM_DECIMAL_STEPS_12BIT;
  //Format temperature into a string [+XXX.XXXX C]
  sprintf(buffer, "%+d.%04u C", digit, decimal);
  Serial.println(buffer);
}
