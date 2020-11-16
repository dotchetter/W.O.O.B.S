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
