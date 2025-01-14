#include <Arduino.h>
#include "SoilSensor.h"

#define SOIL_SENSOR_ANALOG_PIN A0
#define SENSOR_POWER_PIN 7

void initSoilSensor() {
    pinMode(SENSOR_POWER_PIN, OUTPUT);
}

int readSoilMoisture() {
    digitalWrite(SENSOR_POWER_PIN, HIGH);
    delay(10); // stabilize

    int soilMoisture = analogRead(SOIL_SENSOR_ANALOG_PIN);

    digitalWrite(SENSOR_POWER_PIN, LOW);

    return soilMoisture;
}
