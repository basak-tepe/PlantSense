#include <Arduino.h>
#include <LowPower.h>
#include "IRSensor.h"
#include "DHTSensor.h"
#include "SoilSensor.h"

#define LED_OUT_PIN A5
#define BUZZER_OUT_PIN 6

void setup() {
    pinMode(LED_OUT_PIN, OUTPUT);  
    pinMode(BUZZER_OUT_PIN, OUTPUT);  
    digitalWrite(BUZZER_OUT_PIN, LOW); 
    
    // Initialize all modules
    initPlantDetector();
    initDHT();
    initSoilSensor();
    Serial.begin(9600);
}

void loop() {
    // Check for plant presence using the IR sensor
    if (isPlantDetected()) {
        digitalWrite(LED_OUT_PIN, HIGH); 
        
        // Read temperature and humidity
        float temperature = readTemperature();
        float humidity = readHumidity();
        
        // Prepare JSON data
        String jsonData = "{";
        
        if (!isnan(temperature) && !isnan(humidity)) {
            jsonData += "\"temperature\": " + String(temperature) + ",";
            jsonData += "\"humidity\": " + String(humidity) + ",";
        } else {
            jsonData += "\"temperature\": null,";
            jsonData += "\"humidity\": null,";
        }

        // Read soil moisture
        int soilMoisture = readSoilMoisture();
        jsonData += "\"soilMoisture\": " + String(soilMoisture) + ",";

        // Action based on soil moisture
        if (soilMoisture > 500) {
            jsonData += "\"action\": \"Water Needed\"";
            digitalWrite(BUZZER_OUT_PIN, HIGH); // Turn buzzer on
            delay(5000); // Keep buzzer on for 5 seconds
            digitalWrite(BUZZER_OUT_PIN, LOW); // Turn buzzer off
        } else {
            jsonData += "\"action\": \"No Watering Needed\"";
        }
        
        jsonData += "}";  // End JSON
        
        // Send JSON over Serial
        Serial.println(jsonData);

        delay(1000); // Delay before checking again
    } else {
        // If no plant detected
        digitalWrite(LED_OUT_PIN, LOW);
        Serial.println("{\"status\": \"No plant detected! System in standby.\"}");
    }

    // Enter low-power mode for 2 seconds
    LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
}
