//http://maker.ifttt.com/trigger/FIRE!/with/key/iBc3LmmQtGjrhQ30M-zOat-wc7fZUS4lwUcMQN8BhsU (This is the IFTTT webhook server name)
// C02, IR sensor, alerting process integration

#include <Adafruit_SCD30.h>
#include <WiFi.h>
#include <HTTPClient.h>

Adafruit_SCD30  scd30;
WiFiClient client;
HTTPClient http;

uint16_t calibrationValue = 415;

const char* ssid = "SLEEFAMLEE"; //this is my home internet variable - will be replaced with whichever internet is being plugged in at the time
const char* password = "Purduesucks2022!"; //internet password variable
const char* serverName = "http://maker.ifttt.com/trigger/FIRE!!/with/key/iBc3LmmQtGjrhQ30M-zOat-wc7fZUS4lwUcMQN8BhsU";
unsigned long lastTime = 0;
unsigned long timerDelay = 15000;

int isFlamePin = 25;  // This is our input pin
int isFlame = HIGH;  // HIGH MEANS NO FLAME

void alert() { //the alert function is when the ESP32 triggers the IFTTT applet to send an email (or whichever form of communication) to the user
  if(status != WL_CONNECTED){
    Serial.println("Connection dropped, attempting to reestablish connection.");
    while(status != WL_CONNECTED){  
      Serial.println(ssid);
      status = WiFi.begin(ssid, password);
      delay(3000);
    }
    Serial.println("Reestablished connection.");
  }
  http.begin(client, serverName); //HTTP request - sending a HTTP Post request
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  //GPS Coordinates: (random25 is x coor) ...
  String httpRequestData = "value1=" + String(random(25)) + "&value2=" + String(random(25)); //This is the data parameters being sent to the user - will be GPS coordinates
  int httpResponseCode = http.POST(httpRequestData); //POST REQUEST
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);
  Serial.println("successfully connected to host");
  http.end();
  lastTime = millis();
  for(;;){
    ;
  }
  
}

void setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until the serial console opens

  if (!scd30.begin()) {
    Serial.println("Failed to find SCD30 chip");
    while (1) { delay(10); }
  }
  Serial.println("SCD30 Found!");
  // if (!scd30.setMeasurementInterval(10)){
  //   Serial.println("Failed to set measurement interval");
  //   while(1){ delay(10);}
  // }
//  scd30.forceRecalibrationWithReference(calibrationValue); // Michael, when you leave Ranya, put this command in the setup loop and then burn it into the code.
  Serial.print("Measurement Interval: "); 
  Serial.print(scd30.getMeasurementInterval()); 
  Serial.println(" seconds");
  
  pinMode(isFlamePin, INPUT); //flame sensor should be input as it is giving data

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi.");
  Serial.println("Loading");
  while(WiFi.status() != WL_CONNECTED) {
    delay(2000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  delay(3000);
}

void loop() {
  
  if (scd30.dataReady()){
    Serial.println("Data available!");
    if (!scd30.read()){ Serial.println("Error reading sensor data"); return; }
//    printf("Calibrating SCD30 sensor at %d PPM\n", calibrationValue);
    printf("Calibration value is %d PPM\n", scd30.getForcedCalibrationReference());
    Serial.print("Temperature: ");
    Serial.print(scd30.temperature);
    Serial.println(" degrees C");
    
    Serial.print("Relative Humidity: ");
    Serial.print(scd30.relative_humidity);
    Serial.println(" %");
    
    Serial.print("CO2: ");
    Serial.print(scd30.CO2, 3);
    float c02 = scd30.CO2;
    Serial.println(" ppm");
    Serial.println("");
    isFlame = digitalRead(isFlamePin);//Readd the data gien by the flame sensor
    if((1050 < c02) || (isFlame == LOW)){
      Serial.println("FIRE DETECTED ... Alerting User"); // This is where it goes into the routine to alert the use
      alert(); // This is where you alert the user, Julia and Daniel
      }
  }
  delay(200);
}

