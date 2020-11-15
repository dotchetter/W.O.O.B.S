#include <ArduinoLowPower.h>



void setup() {
    Serial.begin(9600);
    pinMode(9, OUTPUT);
  
    LowPower.attachInterruptWakeup(RTC_ALARM_WAKEUP, dummy, CHANGE);
}


void loop() { 


     Serial.begin(9600); 
   
   //  USBDevice.detach();

    delay(10);
    Serial.println("vaknade precis loop");
    Serial.flush();
    delay(500);
  digitalWrite(9, HIGH);
  delay(500);
  digitalWrite(9, LOW);
  delay(500);
            
  LowPower.sleep(8000);
    
//USBDevice.attach();
 delay(1000); 
 
}
void dummy() {
  
}
