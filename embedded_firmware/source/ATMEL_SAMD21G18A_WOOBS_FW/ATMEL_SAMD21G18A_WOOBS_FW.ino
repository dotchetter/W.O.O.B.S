//#include "include/adc.h" 
#include "E201CBlue.h"
#include "SAMD21_ADC.h"
#include "definitions.h"
#include <StateMachine.h>


// Heap allocated globally accessible instances (Singletons)
E201C *phsensor = new E201C(REF_VOLTAGE, ADC_MAX_VAL_REF, PH_REF_1, PH_REF_2, PH_SENSOR_CHANNEL);


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
    delay(1000);
}