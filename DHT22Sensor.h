#ifndef DHT22SENSOR_H
#define DHT22SENSOR_H

#include "DHTesp.h"

class DHT22Sensor {
private:
    DHTesp dht;
    int pinDHT;

public:
    DHT22Sensor(int dhtPin) : pinDHT(dhtPin) {}

    void init();
    float readTemperature();
    float readHumidity();
};

#endif
