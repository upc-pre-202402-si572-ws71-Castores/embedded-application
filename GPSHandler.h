// GPSHandler.h

#ifndef GPSHANDLER_H
#define GPSHANDLER_H

#include <TinyGPS++.h>

class GPSHandler {
public:
    GPSHandler(int rxPin, int txPin, int baudRate);
    void init();
    void readGPS();

private:
    TinyGPSPlus gps;
    int rxPin;
    int txPin;
    int baudRate;
};

#endif