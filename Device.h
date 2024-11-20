#ifndef DEVICE_H
#define DEVICE_H

#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
#include "ApiClient.h"
#include "HX711Sensor.h"
#include "DHT22Sensor.h"

class Device {
private:
    LiquidCrystal_I2C lcd;
    ApiClient apiClient;

    String deviceID;
    String wifiSSID;
    String wifiPassword;
    String tempEndpoint;
    String weightEndpoint;
    String apiEndpoint; // Nuevo endpoint para PUT


    HX711Sensor hx711;
    DHT22Sensor dht22;

public:
    Device(const String& id, const String& ssid, const String& password, const String& endpoint,
           uint8_t lcdAddr, int dhtPin, int hx711DT, int hx711SCK, float hx711Calibration);

    void init();
    void readSensors();
    String getTime(); // Declaración aquí

private:
    void connectWiFi();
    void displayTemperature(float temperature);
    void displayWeight(float weight);
};

#endif
