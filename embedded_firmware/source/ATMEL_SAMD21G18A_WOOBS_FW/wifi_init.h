
int status = WL_IDLE_STATUS;

void wifi_init(){ 
  if (WiFi.status() == WL_NO_MODULE) {     // check for the WiFi module:
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    WiFi.lowPowerMode();  // ENABLE WiFi Low Power Mode
    delay(5000);
  }

   Serial.print("Connected to wifi: ");
   Serial.println(ssid);
}
