// SCD30 Working!
#include <Adafruit_SCD30.h>

Adafruit_SCD30  scd30;

uint16_t calibrationValue = 415;

int isFlamePin = 25;  // This is our input pin
int isFlame = HIGH;  // HIGH MEANS NO FLAME

void setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit SCD30 test!");

  // Try to initialize!
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
      Serial.print("FIRE DETECTED ... Alerting User"); // This is where it goes into the routine to alert the use
      for(;;){
        alertSystem(); // This is where you alert the user, Julia and Daniel
      }
    }
  } else {
    //Serial.println("No data");
  }

  delay(100);
}
