/*
 * File:   E201C-Blue_DRV.cpp
 * Author: Simon Olofsson
 * Program: Source file for driver module
 * Compiler: ARM-GCC 
 * Program Version 1.0
 * Program Description: This file contains source code
                        for the driver for the E201C-Blue
                        PH sensor. It provides a user interface
                        for developers that work with this device.
 *
 * Written on 2020-11-10, Simon Olofsson
 */


E201C::E201C(float deviationOffset, float referenceVoltage, 
             float sensorMaxValue, float phRef1, float phRef2)
{
    this->deviationOffset = deviationOffset;
    this->referenceVoltage = referenceVoltage;
    this->sensorMaxValue = sensorMaxValue;
    this->phRef1 = phRef1;
    this->phRef2 = phRef2;
    this->kValue = this->GetKValue();
}
