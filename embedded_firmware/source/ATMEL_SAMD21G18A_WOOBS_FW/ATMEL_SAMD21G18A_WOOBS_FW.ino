#include "include/adc.h" 
#include <StateMachine.h>


void init_adc()
/*
* Initialize the analog-digital converter
*/
{
    // Enable ADC
    ADC->CTRLA.reg = ADC_CTRLA_ENABLE;

    // Set the ADC as 10 bit resolution register (0 -> 1023)
    ADC->CTRLB.bit.RESSEL = ADC_CTRLB_RESSEL_10BIT_Val;
}







void setup() {
    // put your setup code here, to run once:

}

void loop() {
    // put your main code here, to run repeatedly:

}
