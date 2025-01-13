#include <Arduino.h>

#define OUTPUT_PIN A5

void setup() {
  pinMode(OUTPUT_PIN, OUTPUT);
}

void loop() {
  digitalWrite(OUTPUT_PIN, HIGH);
  delay(1000); 

  // Set the pin LOW
  digitalWrite(OUTPUT_PIN, LOW);
  delay(1000);
}
