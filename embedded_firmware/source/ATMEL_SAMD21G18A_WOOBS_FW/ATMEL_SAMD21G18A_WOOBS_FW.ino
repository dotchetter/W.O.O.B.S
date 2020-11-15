#include "include/port.h"


void setup() 
{
    Serial.begin(9600);
    // Uncomment this function if you wish to attach function dummy when RTC wakes up the chip
    // LowPower.attachInterruptWakeup(RTC_ALARM_WAKEUP, dummy, CHANGE);
    //wifi_init();
}


void loop() 
{
    Serial.println(REG_PORT_DIR0);
    delay(3000);  
}
