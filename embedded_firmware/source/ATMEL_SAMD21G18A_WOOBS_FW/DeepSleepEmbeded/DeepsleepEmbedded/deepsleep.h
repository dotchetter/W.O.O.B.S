void deepsleepInit(){
  // Enable Deep Sleep Mode--------------------------------------------------------------
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;// | SCB_SCR_SLEEPONEXIT_Msk;  // Put the SAMD21 in deep sleep upon executing the __WFI() function
  NVMCTRL->CTRLB.reg |= NVMCTRL_CTRLB_SLEEPPRM_DISABLED;        // Disable auto power reduction during sleep
  }
void deepsleep(){
  SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;           // Disable SysTick interrupts
  __WFI();                                              // Put the SAMD21 into deep sleep
  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;            // Enable SysTick interrupts
  }
