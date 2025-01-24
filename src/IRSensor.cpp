#include <Arduino.h>
#include "IRSensor.h"

#define IR_LED_PIN 2      
#define PHOTODIODE_PIN A2      
#define DETECTION_THRESHOLD 1000 

void initPlantDetector() {
    pinMode(IR_LED_PIN, OUTPUT); // Set IR LED pin as output
}

bool isPlantDetected() {
    digitalWrite(IR_LED_PIN, HIGH);
    delay(10);

    // Read the photodiode
    int reflection = analogRead(PHOTODIODE_PIN);
    Serial.print("reflection is");
    Serial.println(reflection);
    digitalWrite(IR_LED_PIN, LOW);

    return (reflection > DETECTION_THRESHOLD);
}
