#include <ArduinoLowPower.h>
#include <WiFiNINA.h>

#include "config.h"
//#include "wifi_init.h"
#include "dS18B20_init.h"

char buffer[100];

/*A more radical way to reduce the consumption of the NINA module is to use WiFi.end() that turns off the radio part of the module. 
 * The microcontroller inside the module is still using some power, but this is the lowest level of consumption possible. 
 * This function in your sketch closes any active connection and requires a full restart of the initialisation process: 
 
 WiFi.begin() or WiFi.beginAP() are required to restore the connections.*/

void setup() {
  Serial.begin(9600);
    // Uncomment this function if you wish to attach function dummy when RTC wakes up the chip
  // LowPower.attachInterruptWakeup(RTC_ALARM_WAKEUP, dummy, CHANGE);
  //wifi_init();
  
}


void loop() {
  // put your main code here, to run repeatedly:
  
  therm_read_temperature(buffer);
  delay(3000);
  
 //LowPower.sleep(8000);
}


void dummy() {
  // This function will be called once on device wakeup
  // You can do some little operations here (like changing variables which will be used in the loop)
  // Remember to avoid calling delay() and long running functions since this functions executes in interrupt context
}
