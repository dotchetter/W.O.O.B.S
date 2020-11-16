/*
 * File: DS18B20.h
 * Author: Simon Olofsson
 * Program: Source file for driver module
 * Compiler: ARM-GCC 
 * Program Version 1.0
 * Program Description: This file contains source code
                        for the driver for the DSB18B20
                        onewire sensor module. It is not
                        designed for a one wire with several
                        devices to the same line, but takes
                        the pin it is connected to as parameter
                        and will only adress one of the devices.
 *
 * Written on 2020-11-13, Simon Olofsson
 */
#include "include/port.h"

/*

    // Assign LED0 as OUTPUT
    REG_PORT_DIR0 = LED0_PIN_MASK;
    
    // Set LED0 OFF
    REG_PORT_OUTCLR0 = LED0_PIN_MASK;

    // Turn the LED on PA17 ON
    REG_PORT_OUTSET0 = LED0_PIN_MASK;

*/

class DS12B20
{
private:
    uint8_t directionRegisterMask;
    uint8_t microControllerPort;


public:

};




/*

    

*/