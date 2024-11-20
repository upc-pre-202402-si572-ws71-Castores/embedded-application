#include "HX711Sensor.h"

void HX711Sensor::init() {
    scale.begin(pinDT, pinSCK);
    scale.set_scale(calibrationFactor);
    scale.tare();
}

float HX711Sensor::readWeight() {
    if (scale.is_ready()) {
        return scale.get_units(10);
    } else {
        return -1; // Indica un error
    }
}
