void StandbySleep(void)
{
	// Disable interrupts
	__disable_irq();
	__DMB();
	
	// Select STANDBY sleep mode
	SCB->SCR |=  SCB_SCR_SLEEPDEEP_Msk;
	
	// Wait for Interrupt
	__DSB();
	__WFI();
	
	// Enable interrupts
	__DMB();
	__enable_irq();
}
