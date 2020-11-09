

// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 

OneWire oneWire(WATERSENSOR);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

void Tempsensor_init()
{
     sensors.begin(); 
}

void RequestTemperature()
{
  // Serial.print(" Requesting temperatures..."); 
 sensors.requestTemperatures(); // Send the command to get temperature readings 
}
float readTemperature()
{
 return sensors.getTempCByIndex(0); // Why "byIndex"?  
   // You can have more than one DS18B20 on the same bus.  
   // 0 refers to the first IC on the wire  
}
