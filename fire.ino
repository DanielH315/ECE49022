//http://maker.ifttt.com/trigger/FIRE!/with/key/iBc3LmmQtGjrhQ30M-zOat-wc7fZUS4lwUcMQN8BhsU

#include <WiFi.h>
#include <HTTPClient.h>
const char* ssid = "SLEEFAMLEE";
const char* password = "Purduesucks2022!";
const char* serverName = "http://maker.ifttt.com/trigger/FIRE!!/with/key/iBc3LmmQtGjrhQ30M-zOat-wc7fZUS4lwUcMQN8BhsU";
unsigned long lastTime = 0;
unsigned long timerDelay = 15000;
void setup()
  {
    Serial.begin(115200);
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

  //i call alert once I do with an if statement
  alert();
}

void alert() {
  if(WiFi.status()== WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    //GPS Coordinates: (random25 is x coor) ...
    String httpRequestData = "value1=" + String(random(25)) + "&value2=" + String(random(25));
    int httpResponseCode = http.POST(httpRequestData);
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
