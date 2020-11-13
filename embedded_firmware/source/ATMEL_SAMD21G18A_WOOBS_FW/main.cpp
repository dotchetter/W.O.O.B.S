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
