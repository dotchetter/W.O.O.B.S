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
