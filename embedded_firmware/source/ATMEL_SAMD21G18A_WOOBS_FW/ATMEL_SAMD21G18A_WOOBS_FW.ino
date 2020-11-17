
#include "JsonConverter.h"

#define MESSAGE_MAX_LEN 256
#define DEVICE_ID  "W.O.O.B.S"
String JsonMessage;

void setup() {

  Serial.begin(9600);

static int messageCount = 1;

void loop() {

 JsonMessage = ConvertToJson(messageCount);

  Serial.println(JsonMessage);
  messageCount++;        
}
