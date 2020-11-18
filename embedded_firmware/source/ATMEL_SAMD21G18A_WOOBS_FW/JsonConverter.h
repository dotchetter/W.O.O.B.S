
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEVICE_ID  "W.O.O.B.S"

String ConvertToJson(int messageId, char* buffer)
{
   
    char  deviceID[200] = DEVICE_ID; 
    float tempValue = 23.23;
    float phValue = 7.23;


    sprintf (buffer, "[{\"DeviceId\": %s },{\"MessageId\": %d },{\"PH\": %.2f },{\"temp\" : %.2f}]", deviceID,messageId, tempValue, phValue);


}
