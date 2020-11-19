#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/dtostrf.h>.

#define DEVICE_ID "devtest"

void ConvertToJson(char* buffer, float tempValue, float phValue)
/*
* Formats the incoming values in to a valid
* flat JSON string.
*/
{
    char device_id[200] = DEVICE_ID;
    char temp[6];
    char ph[6];
   
    dtostrf(tempValue, 4, 2, temp); // floatValue copied into temp[] because sprintf doesnt support float
    dtostrf(phValue, 4, 2, ph);
    sprintf(buffer, "{\"device_id\": %s, \"ph\": %s ,\"temp\" : %s}", device_id, temp, ph);
}