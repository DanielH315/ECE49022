//Author: Daniel Hong
//http://maker.ifttt.com/trigger/FIRE!/with/key/iBc3LmmQtGjrhQ30M-zOat-wc7fZUS4lwUcMQN8BhsU (This is the IFTTT webhook server name)

#include <WiFi.h>
#include <HTTPClient.h>
const char* ssid = "SLEEFAMLEE"; //this is my home internet variable - will be replaced with whichever internet is being plugged in at the time
const char* password = "Purduesucks2022!"; //internet password variable
const char* serverName = "http://maker.ifttt.com/trigger/FIRE!!/with/key/iBc3LmmQtGjrhQ30M-zOat-wc7fZUS4lwUcMQN8BhsU";
unsigned long lastTime = 0;
unsigned long timerDelay = 15000;
void setup() //the setup function is having the ESP32 connect to the internet
  {
    Serial.begin(115200); //baud raet is 115200
    WiFi.begin(ssid, password);
    Serial.println("Connecting");
    while(WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
    //randomSeed(hallRead());
  }

void loop() { //check for fire in this loop function
  delay(60000); 

  alert(); //this line is currently looping - this will be changed so that IF the fire is detected THEN the function will call the alert() function
}

void alert() { //the alert function is when the ESP32 triggers the IFTTT applet to send an email (or whichever form of communication) to the user
  if(WiFi.status()== WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, serverName); //HTTP request - sending a HTTP Post request
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    //GPS Coordinates: (random25 is x coor) ...
    String httpRequestData = "value1=" + String(random(25)) + "&value2=" + String(random(25)); //This is the data parameters being sent to the user - will be GPS coordinates
    int httpResponseCode = http.POST(httpRequestData); //POST REQUEST
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    Serial.println("successfully conected to host");
    http.end();
  }
  else  {
    Serial.println("WiFi Disconnected");
  }
  lastTime = millis();
}
