# W.O.O.B.S
Water Oberservation Omtizing Boyant System

#### What is it?
This is a product in a college collag designed to collect data about a
swimming pool, and send it to a server over HTTP. 

#### Why? 
It started out as an idea for my old man who's constantly getting down
to check the temperature in the pool. "There's an app for that". And if
there weren't already, we like to think that this is the solution to the problem. 

#### Cool. What hardware? 
We use the E201C-Blue PH sensor to monitor the PH of the water. 
For temperature, we use the DS18B20 onewire sensor. Both drivers are
developed 100% in house without 3rd party software (exception for Microhip port defines for the MCU).
.. Hh, that brings me to the MCU. We chose the stellar champ SAMD21 MCU, a power
beast that provides us with great flexibility in memory and headroom with processing
capabilities. It's all tied up nicely with the ESP32 module for connectivity on
the Arduino MKR 1010 WiFi board.
