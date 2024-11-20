#include "DHT22Sensor.h"

void DHT22Sensor::init() {
    dht.setup(pinDHT, DHTesp::DHT22);
}

float DHT22Sensor::readTemperature() {
    TempAndHumidity data = dht.getTempAndHumidity();
    return data.temperature;
}

float DHT22Sensor::readHumidity() {
    TempAndHumidity data = dht.getTempAndHumidity();
    return data.humidity;
}
