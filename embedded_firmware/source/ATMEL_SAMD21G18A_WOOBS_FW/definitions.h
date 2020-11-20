#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

/*
 * File: definitions.h
 * Author: Simon Olofsson
 * Program: Source file for driver module
 * Processor: SAMD21G18A @ 48MHz, 3.3v
 * Compiler: ARM-GCC 
 * MCU: Arduino MKR 1010 WiFi
 * Program Description: This file contains definitions
                        used in the firmware.

 * Sensor description:  Operating voltage       3.3V/5V
                        Range                   0-14PH
                        Resolution              ±0.15PH（STP）
                        Response time           ＜1min
                        Probe Interface         BNC
                        Measure temperature     0-60℃
                        Internal resistance     ≤250MΩ（25℃）
                        Alkali error            0.2PH（1mol/L）Na+，PH14)（25℃）
 *
 * Written on 2020-11-10, Simon Olofsson
 */

#define REF_VOLTAGE          3.3f
#define ADC_MAX_VAL_REF      1024ul
#define PH_REF_1             4.0f
#define PH_REF_2             9.18
#define PH_SENSOR_PIN        A1
#define PH_SENSOR_CHANNEL    10u

#define TEMP_PORT_GROUP      0
#define TEMP_PINMASK         PORT_PA16
#define WIFI_RECONNECT_WAIT  3000
#define API_URL              "woobsapi.herokuapp.com"
#define API_PATH             "/reading/"

#define SSID                 "devices"
#define PASS                 "00000000"
#define TSL_PORT             443
#define DEVICE_ID            "w.o.o.b.s-acd342-5j39sh32"
#define STDBY_TIME_MS        5000

#endif // DEFINITIONS_H_