#include <Arduino.h>
#include <LowPower.h>
#include "IRSensor.h"
#include "DHTSensor.h"
#include "SoilSensor.h"
#define LED_OUT_PIN A5
#define BUZZER_OUT_PIN 2

void setup() {
    pinMode(LED_OUT_PIN, OUTPUT);  
    // Initialize all modules
    initPlantDetector();
    initDHT();
    initSoilSensor();
    Serial.begin(9600);
}

void loop() {
    // Check for plant presence using the IR sensor
    if (isPlantDetected()) {
        delay(10); 
        Serial.println("Plant detected!");
           digitalWrite(LED_OUT_PIN, HIGH); 
         delay(10); 
        // Read temperature and humidity
        float temperature = readTemperature();
        float humidity = readHumidity();
        if (!isnan(temperature) && !isnan(humidity)) {
            Serial.print("Temperature: ");
            Serial.print(temperature);
            Serial.print(" °C | Humidity: ");
            Serial.print(humidity);
            Serial.println(" %");
            delay(10);
        } else {
            Serial.println("Failed to read from DHT sensor!");
            delay(10);
        }
        delay(10); 
        // Read soil moisture
        int soilMoisture = readSoilMoisture();
        Serial.print("Soil Moisture: ");
        Serial.println(soilMoisture);
         delay(10);
        // Take action based on soil moisture
        if (soilMoisture > 500) {
            Serial.println("Soil is dry! Water is needed.");
            digitalWrite(BUZZER_OUT_PIN, HIGH); 
             delay(10);
        } else {
            Serial.println("Soil is moist. No watering needed.");
            digitalWrite(BUZZER_OUT_PIN, LOW); 
             delay(10);
        }
    } else {
        Serial.println("No plant detected! System in standby.");
        digitalWrite(LED_OUT_PIN, LOW); 
        delay(10);
    }
    delay(10);
    // Enter low-power mode for 8 seconds
    LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
    delay(10);
}
