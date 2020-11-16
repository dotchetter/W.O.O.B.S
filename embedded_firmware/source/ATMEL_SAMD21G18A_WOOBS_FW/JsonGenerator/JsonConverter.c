#include <ArduinoJson.h>

#define MESSAGE_MAX_LEN 256

 ConvertToJson(int messageId, char *payload)
{
    float temperature = readTemperature();
    //float PHValue = readPH();
   
    
    StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    
    root["deviceId"] = DEVICE_ID;
    root["messageId"] = messageId;

    // NAN is not the valid json, change it to NULL
    if (std::isnan(temperature))
    {
        root["temperature"] = NULL;
    }
    else
    {
        root["temperature"] = temperature;
    
    }

    if (std::isnan(PHValue))
    {
        root["PHValue"] = NULL;
    }
    else
    {
        root["PHValue"] = PHValue;
    }

    root.printTo(payload, MESSAGE_MAX_LEN);

}