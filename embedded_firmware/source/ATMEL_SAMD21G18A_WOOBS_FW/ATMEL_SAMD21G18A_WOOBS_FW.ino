/*
    W.O.O.B.S main firmware file

    Hardware configuration:
        MCU:                    Arduino MKR 1010 WiFi (SAMD21)
        PH SENSOR:              GROVE E201C-BLUE    (Connected to D8)
        TEMP SENSOR:            DSB18B20 ONEWIRE    (Connected to A1)
*/

#include <ArduinoHttpClient.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include "DS18B20.h"
#include "E201CBlue.h"
#include "SAMD21_ADC.h"
#include "definitions.h"
#include <StateMachine.h>
#include <ArduinoJson.h>


// Heap allocated globally accessible instances (Singletons)
E201C *phsensor = new E201C(REF_VOLTAGE, ADC_MAX_VAL_REF, PH_REF_1, PH_REF_2, PH_SENSOR_CHANNEL);
DS18B20 *tempSensor = new DS18B20(TEMP_PORT_GROUP, TEMP_PINMASK);
WiFiSSLClient *wifi = new WiFiSSLClient();
HttpClient *client = new HttpClient(*wifi, API_URL, TSL_PORT);

int status = WL_IDLE_STATUS;
String response;
int statusCode = 0;


void SendTelemetryData() 
{
    DynamicJsonDocument doc(1024);
    doc["ph"] = phsensor->GetSensorPH();
    doc["temp"] = tempSensor->GetTemperature('C');
    doc["device_id"] = DEVICE_ID;
    
    char JSONmessageBuffer[300];

    serializeJson(doc, JSONmessageBuffer);

    while (status != WL_CONNECTED) 
    {
        status = WiFi.begin(SSID, PASS);
    }

    Serial.println("making POST request");
    Serial.println(JSONmessageBuffer);

    client->post("/reading/", "application/json", JSONmessageBuffer);

    statusCode = client->responseStatusCode();
    response = client->responseBody();

    Serial.print("Status code: ");
    Serial.println(statusCode);
    Serial.print("Response: ");
    Serial.println(response);

}


void setup() 
{
    Serial.begin(115200);
    init_adc();
}


void loop() 
{
    static uint64_t last_iter;

    if (millis() - last_iter > STDBY_TIME_MS)
    {
        SendTelemetryData();
        last_iter = millis();
    }
}
