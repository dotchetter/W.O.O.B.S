
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/dtostrf.h>.

#define DEVICE_ID  "W.O.O.B.S"

void ConvertToJson(int messageId, char* buffer)
{
    char  deviceID[200] = DEVICE_ID; 
    float tempValue = 23.23;
    float phValue = 7.23;

    char temp[6];
    char ph[6];
   

   dtostrf(tempValue, 4, 2, temp);
   dtostrf(phValue, 4, 2, ph);


    sprintf (buffer, "[{\"DeviceId\": %s },{\"MessageId\": %d },{\"PH\": %s },{\"temp\" : %s}]", deviceID, messageId, temp, ph);


}

