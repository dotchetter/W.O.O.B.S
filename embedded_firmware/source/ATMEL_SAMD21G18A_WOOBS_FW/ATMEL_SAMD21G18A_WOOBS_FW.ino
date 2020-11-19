float voltage;
float perc;
int value;


void setup()
{
	Serial.begin(9600);
	pinMode(7, OUTPUT); 
}

void loop() 
{
	digitalWrite(7, HIGH);
	value = analogRead(ADC_BATTERY); //* 3.3f / 1023.0f/1.2f * (1.2f+ 0.33f);
	voltage = value * (3.3/1023.0f);
	perc = map(voltage, 3.0, 3.7, 100, 0);
	Serial.print("Voltage= ");
	Serial.println(voltage);
	Serial.print("Battery level= ");
	Serial.print(perc);
	Serial.println(" %");
	delay(500);

	if (voltage < 3.20)
	{
		digitalWrite(7, LOW);
		delay(1000);
		digitalWrite(7, HIGH);
		delay(1000);
	}
	
	if (voltage < 3.0)
	{
	    digitalWrite(7, LOW);
	    delay(500);
	    digitalWrite(7, HIGH);
	    delay(500);
	}
	Serial.println(perc);
}

