void ClocksInit(){
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
}
