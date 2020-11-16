#include "clocksinit.h"
#include "interrupts.h"
#include "deepsleep.h"

int TimeToSleepSec = 8;



void setup() {
  while(!SerialUSB);
  PORT->Group[PORTA].DIRSET.reg = PORT_PA21; // Pin output PIN 7 on MRK1010
  ClocksInit();
  interruptsInit(TimeToSleepSec);
  deepsleepInit();
}

void loop() {
  SerialUSB.println("SLEEPING ZZZzzzzzzZzz");
  USBDevice.detach();
  // put your main code here, to run repeatedly:
    // Due to a hardware bug on the SAMD21, the SysTick interrupts become active before the flash has powered up from sleep, causing a hard fault
  // To prevent this the SysTick interrupts are disabled before entering sleep mode
  deepsleep();
  USBDevice.attach();
  delay(1000);
  while(!SerialUSB);
  SerialUSB.println("Woke up...."); // You need to exit the terminal to read the last println
  
}

void RTC_Handler(void) // ISR OVERFLOW
{
     PORT->Group[PORTA].OUTTGL.reg = PORT_PA21;                       // Toggle digital pin D7
     RTC->MODE1.INTFLAG.bit.OVF = 1;                                  // Reset the overflow interrupt flag
}
