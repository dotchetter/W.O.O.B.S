 void deepsleep(){
  SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;           // Disable SysTick interrupts
  __DSB();                                              // Complete outstanding memory operations - not required for SAMD21 ARM Cortex M0+
  __WFI();                                              // Put the SAMD21 into deep sleep, Zzzzzzzz... 
  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;            // Enable SysTick interrupts
  }
