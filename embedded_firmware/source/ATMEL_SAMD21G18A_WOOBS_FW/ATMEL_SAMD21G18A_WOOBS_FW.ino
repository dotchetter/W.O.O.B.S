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
  deepsleep(); // Put it into sleepmode
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
