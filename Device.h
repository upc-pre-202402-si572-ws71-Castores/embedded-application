// Device.h

#ifndef DEVICE_H
#define DEVICE_H

#include "DHTesp.h"
#include <HX711.h>
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
#include "ApiClient.h"

class Device {
private:
    DHTesp dht;
    HX711 scale;
    LiquidCrystal_I2C lcd;
    ApiClient apiClient;

    int pinDHT;
    int ld_cell;
    int ld_sck;
    float calibration_factor;
    String deviceID;
    
    String wifiSSID;
    String wifiPassword;
    String tempEndpoint;
    String weightEndpoint;

public:
    Device(int dhtPin, int cellPin, int sckPin, float calibration, const String& id, const String& ssid, const String& password, const String& tempUrl, const String& weightUrl, uint8_t lcdAddr);

    void init();
    String getTime();
    void readTemperature();
    void readWeight();
    void displayTemperature(float temperature);
    void displayWeight(float weight);
};

#endif
