#include <ESP8266WiFi.h>
#include <OneWire.h>

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>
#include <Arduino.h>

#include <DallasTemperature.h>

#include "config.h"
#include "tempsensor_init.h"
#include "time_init.h"
#include "wifi_init.h"

void setup() {
 Serial.begin(9600); 

 Tempsensor_init();
 Time_init();
 Wifi_init();
}

void loop() {

 RequestTemperature();
 Serial.print("Temperature is: "); 
 Serial.println(readTemperature()); // Why "byIndex"?  

   delay(1000); 
}
