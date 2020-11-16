void interruptsInit(int timeToSleep){
                                           
  RTC->MODE1.CTRL.bit.ENABLE = 0;                       // Disable the RTC
  while (RTC->MODE1.STATUS.bit.SYNCBUSY);               // Wait for synchronization

  RTC->MODE1.CTRL.bit.SWRST = 1;                       // Software reset the RTC
  while (RTC->MODE1.STATUS.bit.SYNCBUSY);              // Wait for synchronization
 
  RTC->MODE1.CTRL.reg |= RTC_MODE1_CTRL_PRESCALER_DIV1024 |     // Set prescaler to 1024
                         RTC_MODE1_CTRL_MODE_COUNT16;           // Set RTC to mode 1, 16-bit timer                         
 
  RTC->MODE1.PER.reg = RTC_MODE1_PER_PER(timeToSleep);                   // Interrupt time s: 1Hz/(59 + 1)
  while (RTC->MODE1.STATUS.bit.SYNCBUSY);                       // Wait for synchronization
  
  RTC->MODE1.INTENSET.reg = RTC_MODE1_INTENSET_OVF;             // Enable RTC overflow interrupts

  NVIC_SetPriority(RTC_IRQn, 0);    // Set the Nested Vector Interrupt Controller (NVIC) priority for RTC
  NVIC_EnableIRQ(RTC_IRQn);         // Connect RTC to Nested Vector Interrupt Controller (NVIC)

  // Enable RTC--------------------------------------------------------------
  RTC->MODE1.CTRL.bit.ENABLE = 1;                       // Enable the RTC
  while (RTC->MODE1.STATUS.bit.SYNCBUSY);               // Wait for synchronization
}
