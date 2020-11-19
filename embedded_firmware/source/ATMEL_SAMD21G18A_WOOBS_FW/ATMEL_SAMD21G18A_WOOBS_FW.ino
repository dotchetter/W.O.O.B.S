
#include <ArduinoHttpClient.h>
#include "config.h"
#include "wifi.h"

#include "DS18B20.h"
#include "E201CBlue.h"
#include "SAMD21_ADC.h"
#include "definitions.h"
#include "JsonConverter.h"
#include <StateMachine.h>

char JsonMessage[200];
char server[] = ""; 
char path[] = ""; 
int port = 80;



// Heap allocated globally accessible instances (Singletons)
E201C *phsensor = new E201C(REF_VOLTAGE, ADC_MAX_VAL_REF, PH_REF_1, PH_REF_2, PH_SENSOR_CHANNEL);
DS18B20 *tempSensor = new DS18B20(0, PORT_PA16); // (Port group, port mask)
WiFiClient *wifiClient = new WiFiClient();
HttpClient *httpClient = new HttpClient(client, server, port);


void HTTPpost()
{
    httpClient.beginRequest();
    httpClient.post(path);
    httpClient.sendHeader("Content-Type", "application/json");
    httpClient.sendHeader("Content-Length", message.length());
    httpClient.beginBody();
    httpClient.print(json);
    httpClient.endRequest();
    client.flush();
}


void setup() 
{
    init_adc();
    init_wifi();
    Serial.begin(115200);
}



void loop() 
{
    Serial.print("PH: ");
    Serial.println(phsensor->GetSensorPH());

    Serial.print("Voltage: ");
    Serial.println(phsensor->GetSensorVoltage());

    Serial.print(tempSensor->GetTemperature('C'));
    Serial.print(" C\r\n");

 	ConvertToJson(JsonMessage, tempSensor->GetTemperature('C'), phsensor->GetSensorPH());

	Serial.print(JsonMessage);
	Serial.println();

    delay(1000);
}
