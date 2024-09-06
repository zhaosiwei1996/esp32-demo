#include <DHT.h>
#include "sensor.h"

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void initializeSensor() {
  dht.begin();
}

float readTemperature() {
  return dht.readTemperature();
}

float readHumidity() {
  return dht.readHumidity();
}
