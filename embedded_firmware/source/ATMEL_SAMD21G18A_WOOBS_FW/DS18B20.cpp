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


void DS18B20::BusWrite(uint8_t mode)
/*
* Write a 1 (HIGH) or 0 (LOW)to the bus 
* where the device is connected.
*/
{
    switch (mode)
    {
        case 0:
            switch(this->portGroup)
            {
                case 0: REG_PORT_OUTCLR0 = this->pinMask; break;
                case 1: REG_PORT_OUTSET0 = this->pinMask; break;
            }
        case 1:
            switch(this->portGroup)
            {
                case 0: REG_PORT_OUTCLR1 = this->pinMask; break;
                case 1: REG_PORT_OUTSET1 = this->pinMask; break;
            }
    }
}


uint32_t DS18B20::BusRead()
/*
* Read from the bus where the device
* is connected.
*/
{
    switch(this->portGroup)
    {
        case 0: return REG_PORT_IN0 & this->pinMask; break;
        case 1: return REG_PORT_IN1 & this->pinMask; break;
    }
}


void DS18B20::InitCommand()
/*
* Selecting the pin as output and writing a LOW
* will let the sensor know there is an upcoming
* transition of command(s).
*/
{
    this->SetAsOutput();
    this->BusWrite(0);
}


void DS18B20::SuspendMicroSeconds(uint32_t microSeconds)
/*
* Allows the caller to return n cycles to sleep for
* desired amount of microseconds.
*/
{
    for (uint64_t i = 0; i < this->_us_to_cycles(microSeconds); i++) {asm("nop");}
}


void DS18B20::SendResetCommand()
/*
* Resets the sensor device by sensing the initial
* command, then switching on the line as input
*/
{
    this->InitCommand();
    this->SuspendMicroSeconds(RESET_US);
    this->SetAsInput();    
    this->SuspendMicroSeconds(RESET_US);
}


void DS18B20::SendByteCommand(uint8_t command)
/*
* Send a command to the sensor. 
* The commands for the DS18B20 are bytes
* where each bit is part of an instruction.
* This method sends one bit at a time, where
* inbetween, the application must be suspended for
* a defined amount of microseconds for the sensor
* to process the command.
*/
{
    /* Iterate over the byte-sized command and send instruction */
    for (int i = 0; i < BITS_IN_BYTE; i++)
    {
        this->InitCommand();
        /* The bit is 1 - go HIGH and wait for the time slot of 60us */
        if  ((command >> i) & 1U)
        {
            /* The current part of command is 1 - engage pull-up resistor and await */
            this->SuspendMicroSeconds(WRITE_0_LOW_US);
            this->SetAsInput();
            this->SuspendMicroSeconds(WRITE_1_LOW_US);
        }
        /* The bit is 0 - go LOW and wait for the time slot of 60us */
        else
        {
            this->SuspendMicroSeconds(WRITE_1_LOW_US);
            this->SetAsInput();
            this->SuspendMicroSeconds(WRITE_0_LOW_US);
        }
    }    
}


uint8_t DS18B20::ReadScratchPad()
/*
* Read one byte of data from the sensor.
* The size of a byte is iterated over, and
* ultimately concatenates a byte from the 
* sensor received over one wire.
*/
{
    uint8_t result;

    for (int i = 0; i < BITS_IN_BYTE; i++)
    {
        this->InitCommand();
        this->SetAsInput();
        this->SuspendMicroSeconds(PRECEDENCE_DETECT_HIGH_US);

        /* If the received bit is 1, it is set in the result, otherwise cleared.*/
        if (this->BusRead())
        {
            result |= (1 << i);
        }
        else
        {
            result &= ~(1 << i);
        }

        /* The time slot for this transition must exhaust - suspend execution. */
        this->SuspendMicroSeconds(TIME_SLOT_US);
    }
    return result;
}
