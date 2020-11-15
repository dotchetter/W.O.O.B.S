 


void deepsleep()
{

  PORT->Group[PORTA].DIRSET.reg = PORT_PA21;  // Output to D7 to check that the ISR is being called every 60 seconds

    // Configure the external crystal----------------------------------------------
    SYSCTRL->XOSC32K.reg = SYSCTRL_XOSC32K_ONDEMAND |       // Enble one demand mode
                         SYSCTRL_XOSC32K_RUNSTDBY |       // Enable run-on-standby mode
                         SYSCTRL_XOSC32K_EN32K |          // Enable the crystal oscillator IO pads
                         SYSCTRL_XOSC32K_XTALEN |         // Enable the crystal oscillator
                         SYSCTRL_XOSC32K_STARTUP(6) |     // Set the crystal start-up time
                         SYSCTRL_XOSC32K_ENABLE;          // Enable the oscillator

    // Configure clock source and clock generators (gclk.h)------------------------   
    GCLK->GENDIV.reg =  GCLK_GENDIV_ID(4) |   // Select GLCK4
                      GCLK_GENDIV_DIV(4);   // Select clock divisor to divide by 32 (2 ^ (4 + 1)) to generate 1.024kHz
    while (GCLK->STATUS.bit.SYNCBUSY);        // Wait for synchronization

    GCLK->GENCTRL.reg = GCLK_GENCTRL_ID(4) |        // Select GCLK4
                      GCLK_GENCTRL_SRC_XOSC32K |  // Select generic clock source as the external 32.768kHz crystal                     
                      GCLK_GENCTRL_IDC |          // Improve duty cycle for odd div factors
                      //GCLK_GENCTRL_RUNSTDBY |     // Enable run standby mode                 
                      GCLK_GENCTRL_DIVSEL |       // Set GLCK divisor as 2 to the power of (divisor) value
                      GCLK_GENCTRL_GENEN;         // Enable GCLK4
    while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization
     
    GCLK->CLKCTRL.reg = GCLK_CLKCTRL_GEN_GCLK4 |  // Select GCLK4
                      GCLK_CLKCTRL_ID_RTC |     // Connect to the RTC 
                      GCLK_CLKCTRL_CLKEN;       // Enable GCLK4 
    while (GCLK->STATUS.bit.SYNCBUSY);            // Wait for synchronization 

    // RTC configuration (rtc.h)--------------------------------------------------                                             
    RTC->MODE1.CTRL.bit.ENABLE = 0;                       // Disable the RTC
    while (RTC->MODE1.STATUS.bit.SYNCBUSY);               // Wait for synchronization

    RTC->MODE1.CTRL.bit.SWRST = 1;                       // Software reset the RTC
    while (RTC->MODE1.STATUS.bit.SYNCBUSY);              // Wait for synchronization

    RTC->MODE1.CTRL.reg |= RTC_MODE1_CTRL_PRESCALER_DIV1024 |     // Set prescaler to 1024
                         RTC_MODE1_CTRL_MODE_COUNT16;           // Set RTC to mode 1, 16-bit timer                         

    RTC->MODE1.PER.reg = RTC_MODE1_PER_PER(9);                   // Interrupt time 60s: 1Hz/(59 + 1)
    while (RTC->MODE1.STATUS.bit.SYNCBUSY);                       // Wait for synchronization

    // Configure RTC interrupts ------------------------------------------
    RTC->MODE1.INTENSET.reg = RTC_MODE1_INTENSET_OVF;             // Enable RTC overflow interrupts

    NVIC_SetPriority(RTC_IRQn, 0);    // Set the Nested Vector Interrupt Controller (NVIC) priority for RTC
    NVIC_EnableIRQ(RTC_IRQn);         // Connect RTC to Nested Vector Interrupt Controller (NVIC)

    // Enable Deep Sleep Mode--------------------------------------------------------------
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;// | SCB_SCR_SLEEPONEXIT_Msk;  // Put the SAMD21 in deep sleep upon executing the __WFI() function
    NVMCTRL->CTRLB.reg |= NVMCTRL_CTRLB_SLEEPPRM_DISABLED;        // Disable auto power reduction during sleep - SAMD21 Errata 1.14.2

    // Enable RTC--------------------------------------------------------------
    RTC->MODE1.CTRL.bit.ENABLE = 1;                       // Enable the RTC
    while (RTC->MODE1.STATUS.bit.SYNCBUSY);               // Wait for synchronization
}
