
#include "app.h"
#include "clock.h"

#define F_CPU 48000000UL
#include "delay.h"

#include "sleep.h"
#include "sam.h"


void setup() {
    Serial.begin(9600);

    // Set the drive strength to strong
    PORT->Group[LED0_PORT].PINCFG[LED0_PIN_NUMBER].bit.DRVSTR = 1;
        
    // Turn the LED on PA17 ON
    REG_PORT_OUTSET0 = LED0_PIN_MASK;
        
    // Errata: Make sure that the Flash does not power all the way down when in sleep mode. 
    NVMCTRL->CTRLB.bit.SLEEPPRM = NVMCTRL_CTRLB_SLEEPPRM_DISABLED_Val;
    
    // Wait 5 seconds
    delay_ms(5000);
    
    // Sleep
    StandbySleep();
    
  
}


void loop() { 
    Serial.begin(9600);
    Serial.println("vaknade precis loop");
    // Due to a hardware bug on the SAMD21, the SysTick interrupts become active before the flash has powered up from sleep, causing a hard fault

 
}
