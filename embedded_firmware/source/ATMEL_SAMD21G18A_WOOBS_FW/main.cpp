/*
 * ATMEL_SAMD21G18A_WOOBS_FW.cpp
 *
 * Created: 2020-11-11 18:39:12
 * Author : Simon
 */ 


#include "sam.h"


int main(void)
{
    /* Initialize the SAM system */
    SystemInit();

    /* Replace with your application code */
    while (1) 
    {
    }
}
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
#define F_CPU 48000000UL //Your clock speed in Hz (3Mhz here)   ÄNDRA ANTAR JAG
#define LOOP_CYCLES 8 //Number of cycles that the loop takes
#define us(num) (num/(LOOP_CYCLES*(1/(F_CPU/1000000.0))))
#define THERM_PORT PORT[0]
//#define THERM_DDR DDRC
#define THERM_PIN PORT_PA16  // (16ul)
#define THERM_DQ PA16 // PIN D8 Mkr 1010 Wi-Fi
/* Utils */
#define THERM_INPUT_MODE() PORT->Group[0].PINCFG[16].reg = PORT_PINCFG_INEN    // PIN D8 as input
#define THERM_OUTPUT_MODE() PORT->Group[0].DIRSET.reg = THERM_PIN // PIN D8 as output // kan vara DIR0 istället för DIRSET

#define THERM_LOW() PORT->Group[0].OUTCLR.reg = THERM_PIN //PORT->Group[0].OUTCLR.reg     //THERM_PORT&=~(1<<THERM_DQ)
#define THERM_HIGH() PORT->Group[0].OUTSET.reg = THERM_PIN //PORT->Group[0].OUTSET.reg     //THERM_PORT|=(1<<THERM_DQ)
inline __attribute__((gnu_inline)) void therm_delay(uint16_t delay){
while(delay--) asm volatile("nop");
uint8_t therm_reset(){
	uint8_t i;
	//Pull line low and wait for 480uS
	THERM_LOW();
	THERM_OUTPUT_MODE();
	therm_delay(us(480));
	//Release line and wait for 60uS
	THERM_INPUT_MODE();
	therm_delay(us(60));
	//Store line value and wait until the completion of 480uS period
	i = PORT->Group[0].IN.reg & THERM_PIN; //osäker          //(THERM_PIN & (1<<THERM_DQ));
	therm_delay(us(420));
	//Return the value read from the presence pulse (0=OK, 1=WRONG)
	return i;
}

void therm_write_bit(uint8_t bit){
	//Pull line low for 1uS
	THERM_LOW();
	THERM_OUTPUT_MODE();
	therm_delay(us(1));
	//If we want to write 1, release the line (if not will keep low)
	if(bit) THERM_INPUT_MODE();
	//Wait for 60uS and release the line
	therm_delay(us(60));
	THERM_INPUT_MODE();
}uint8_t therm_read_bit(void){
	uint8_t bit=0;
	//Pull line low for 1uS
	THERM_LOW();
	THERM_OUTPUT_MODE();
	therm_delay(us(1));
	//Release line and wait for 14uS
	THERM_INPUT_MODE();
	therm_delay(us(14));
	//Read line value
	if (PORT->Group[0].IN.reg & THERM_PIN) bit=1; //((PORT->Group[0].IN.reg & PORT_PA16)== 1)  //(THERM_PIN&(1<<THERM_DQ)) 
	//Wait for 45uS to end and return read value
	therm_delay(us(45));
	return bit;
}uint8_t therm_read_byte(void){
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
