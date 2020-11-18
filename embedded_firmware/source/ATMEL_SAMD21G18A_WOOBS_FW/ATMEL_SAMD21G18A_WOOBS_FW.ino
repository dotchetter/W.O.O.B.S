
#include "JsonConverter.h"

#define MESSAGE_MAX_LEN 256
#define DEVICE_ID  "W.O.O.B.S"
char JsonMessage[200];
static int messageCount = 1;

void setup() {

  Serial.begin(9600);
}
void loop() {

  ConvertToJson(messageCount, JsonMessage);

  Serial.println(JsonMessage);
  messageCount++;        
}
