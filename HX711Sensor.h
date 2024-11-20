#ifndef HX711SENSOR_H
#define HX711SENSOR_H

#include <HX711.h>

class HX711Sensor {
private:
    HX711 scale;
    int pinDT;
    int pinSCK;
    float calibrationFactor;

public:
    HX711Sensor(int dtPin, int sckPin, float calibration)
        : pinDT(dtPin), pinSCK(sckPin), calibrationFactor(calibration) {}

    void init();
    float readWeight();
};

#endif
