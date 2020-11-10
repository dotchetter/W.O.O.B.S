#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>
#include <Arduino.h>
#include <DallasTemperature.h>

#include "config.h"
#include "tempsensor_init.h"
#include "time_init.h"
#include "wifi_init.h"
#include "deepsleep_init.h"

void setup() {
 Serial.begin(9600); 
 Wifi_init();
 Time_init();
 Tempsensor_init();
 RequestTemperature();
 while(!Serial) { }

 Serial.print("Temperature is: "); 
 Serial.println(readTemperature()); // Why "byIndex"?  
 delay(1000); 
 
 deepsleep_init();  // sleeping 10 sec
}

void loop() {

}
