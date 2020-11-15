
void setup() {
    Serial.begin(9600);

    delay(7000); //delay so we can see normal current draw

  
    delay(1000); 
  
}


void loop() { 
    Serial.begin(9600);
    Serial.println("vaknade precis loop");
    // Due to a hardware bug on the SAMD21, the SysTick interrupts become active before the flash has powered up from sleep, causing a hard fault
    // To prevent this the SysTick interrupts are disabled before entering sleep mode           
    SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;// Disable SysTick interrupts
    // __WFI();                                              // Put the SAMD21 into deep sleep, Zzzzzzzz... 
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
 
}

void RTC_Handler(void)
{
    if (RTC->MODE1.INTFLAG.bit.OVF && RTC->MODE1.INTENSET.bit.OVF) {  // Check if an overflow caused the interrupt

     PORT->Group[PORTA].OUTTGL.reg = PORT_PA21;   

     RTC->MODE1.INTFLAG.bit.OVF = 1;                                  // Reset the overflow interrupt flag
    }
}
