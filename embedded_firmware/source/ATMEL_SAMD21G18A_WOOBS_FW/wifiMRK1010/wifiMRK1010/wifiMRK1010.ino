#include <ArduinoJson.h>
#include <ArduinoHttpClient.h>
#include "config.h"
#include "wifi.h"

char server[] = ""; 
char path[] = "";  
String message = "hejhej";
String json;

DynamicJsonDocument doc(2048);
int port = 80;

WiFiClient client;

HttpClient httpClient = HttpClient(client, server, port);

void HTTPpost(){

    httpClient.beginRequest();
    httpClient.post(path);
    httpClient.sendHeader("Content-Type", "application/json");
    httpClient.sendHeader("Content-Length", message.length());
    httpClient.beginBody();
    httpClient.print(json);
    httpClient.endRequest();
    client.flush(); 
    
  }


void setup() {
   Serial.begin(9600);
   wifiInit();
  
}

void loop() {
  if (client.connect(server, port)) {

  HTTPpost();
  int statusCode = httpClient.responseStatusCode();
  String response = httpClient.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
  } 
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
   delay(3000); // Wait for 3 seconds to post again
}
