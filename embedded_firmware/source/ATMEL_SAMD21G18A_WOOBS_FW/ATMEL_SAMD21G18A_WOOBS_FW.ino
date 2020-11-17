#include "DS18B20.h"

DS18B20 *tempSensor = new DS18B20(0, PORT_PA16); // (Port group, port mask)

void setup() 
{
    Serial.begin(9600);
}


void loop() 
{
    Serial.print(tempSensor->GetTemperature('C'));
    Serial.print(" C\r\n");
}
