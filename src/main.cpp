#include <Arduino.h>

#define OUTPUT_PIN A5            
#define SOIL_SENSOR_ANALOG_PIN A0 

void setup() {
  pinMode(OUTPUT_PIN, OUTPUT); 
  Serial.begin(9600);          // Initialize serial communication at 9600 baud
}

void loop() {
  int analogValue = analogRead(SOIL_SENSOR_ANALOG_PIN);

  Serial.print("Analog Value: ");
  Serial.println(analogValue);

  // Control the output pin based on soil moisture level
  if (analogValue > 500) { 
    digitalWrite(OUTPUT_PIN, HIGH);
    Serial.println("Soil is dry! Water is needed.");
  } else {
    digitalWrite(OUTPUT_PIN, LOW);
    Serial.println("Soil is moist. No watering needed.");
  }

  delay(5000); // 5s
}
