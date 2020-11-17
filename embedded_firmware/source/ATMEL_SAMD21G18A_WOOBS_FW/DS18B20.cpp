#include "DS18B20.h"

/*
 * File: DS18B20.cpp
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


DS18B20::DS18B20(uint8_t portGroup, uint32_t pinMask)
{
    this->pinMask = pinMask;
    this->portGroup = portGroup;
}


DS18B20::~DS18B20(){}


uint64_t DS18B20::_us_to_cycles(uint32_t us)
/*
* Convert microseconds to cpu cycles
*/
{
    uint64_t cycles_per_us = F_CPU / 10000000;
    return (uint64_t)(us) * cycles_per_us;
}


void DS18B20::SetAsInput()
/*
* Configure the pin where the sensor is
* plugged in as input - a part of the
* means of communication over onewire.
*/
{
    switch(this->portGroup)
    {
        case 0: REG_PORT_DIRCLR0 = this->pinMask; break;
        case 1: REG_PORT_DIRCLR1 = this->pinMask; break;
    }
}


void DS18B20::SetAsOutput()
/*
* Configure the pin where the sensor is
* plugged in as output - a part of the
* means of communication over onewire.
*/
{
    switch(this->portGroup)
    {
        case 0: REG_PORT_DIR0 = this->pinMask; break;
        case 1: REG_PORT_DIR1 = this->pinMask; break;
    }
}

* Write a 1 (HIGH) or 0 (LOW)to the bus 
* where the device is connected.
