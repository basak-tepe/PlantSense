#include <Arduino.h>
#include <DHT.h>
#include "DHTSensor.h"

#define DHT_PIN 3
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

void initDHT() {
    dht.begin();
}

float readTemperature() {
    return dht.readTemperature();
}

float readHumidity() {
    return dht.readHumidity();
}
