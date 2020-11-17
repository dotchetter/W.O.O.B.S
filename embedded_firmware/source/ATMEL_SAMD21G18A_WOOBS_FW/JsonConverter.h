
#include <ArduinoJson.h>


#define MESSAGE_MAX_LEN 256
#define DEVICE_ID  "W.O.O.B.S"

String ConvertToJson(int messageId)
{
   

    float temperature = 32.4;//readTemperature();
    float PHValue = 8.2; //readPH();



    StaticJsonDocument<MESSAGE_MAX_LEN> doc;

   
    
     doc["deviceId"] = DEVICE_ID;
     doc["messageId"] = messageId;

    // NAN is not the valid json, change it to NULL

     doc["temperature"] = temperature;
    
    

     doc["PHValue"] = PHValue;

     String output;

      //serializeJson(doc, output);
     serializeJsonPretty(doc,  output);

      return output;

}
