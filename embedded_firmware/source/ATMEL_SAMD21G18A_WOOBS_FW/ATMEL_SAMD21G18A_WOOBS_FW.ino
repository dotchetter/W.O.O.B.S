#include "DS18B20.h"
#include "E201CBlue.h"
#include "SAMD21_ADC.h"
#include "definitions.h"
#include <StateMachine.h>

// Heap allocated globally accessible instances (Singletons)
E201C *phsensor = new E201C(REF_VOLTAGE, ADC_MAX_VAL_REF, PH_REF_1, PH_REF_2, PH_SENSOR_CHANNEL);
DS18B20 *tempSensor = new DS18B20(0, PORT_PA16); // (Port group, port mask)

void setup() 
{
    init_adc();
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

    delay(1000);
}