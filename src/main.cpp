#include <Arduino.h>
#include <LowPower.h>

#define SENSOR_POWER_PIN 7
#define SOIL_SENSOR_ANALOG_PIN A0
#define OUTPUT_PIN A5

void setup() {
    pinMode(SENSOR_POWER_PIN, OUTPUT); 
    pinMode(OUTPUT_PIN, OUTPUT);      
    Serial.begin(9600);                
}

void loop() {
    // Power on the soil sensor
    digitalWrite(SENSOR_POWER_PIN, HIGH);
    delay(10); // Allow sensor to stabilize

   
    int soilMoisture = analogRead(SOIL_SENSOR_ANALOG_PIN);

    // Power off sensor
    digitalWrite(SENSOR_POWER_PIN, LOW);


    Serial.print("Soil Moisture: ");
    Serial.println(soilMoisture);

    // Take action based on moisture level
    if (soilMoisture > 500) {
        digitalWrite(OUTPUT_PIN, HIGH); 
        Serial.println("Soil is dry! Water is needed.");
    } else {
        digitalWrite(OUTPUT_PIN, LOW); 
        Serial.println("Soil is moist. No watering needed.");
    }

    // Sleep for 8 seconds
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
}
