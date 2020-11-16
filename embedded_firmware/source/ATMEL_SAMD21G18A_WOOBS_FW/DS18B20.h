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

The SAMD21 MCU has a different port layout than
many users and developers are used to, coming 
from the ATMEGA328P or alike. To use this driver,
you need to provide the port group and the pinmask
for the pin you selected to plug in the sensor to.

To make this easier for you, we have provided you
with this lookup table to find this information.

Buy us a coffee? https://www.buymeacoffee.com/dotchetter

    **********************************
    * PHYSICAL-PIN   MCU       GROUP *
    **********************************
        AREF        PA03        0
        A0/D15      PA02        0
        A1/D16      PB02        1
        A2/D17      PB03        1
        A3/D18      PA04        0
        A4/D19      PA05        0
        A5/D20      PA06        0
          D0        PA22        0
          D1        PA23        0
          D2        PA10        0
          D3        PA11        0
          D4        PB10        1
          D5        PB11        1
          D14       PB22        1
          D13       PB23        1
          D12       PA09        0
          D11       PA08        0
          D10       PA19        0
          D9        PA17        0
          D8        PA16        0
          D7        PA21        0
          D6        PA20        0
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