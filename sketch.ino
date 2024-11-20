#include "Device.h"

// WiFi Credentials and API Endpoints
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""

#define API_ENDPOINT_URL "https://transportapp-crg0gmeuevexfscb.eastus2-01.azurewebsites.net/api/v1/request/" // Endpoint base para enviar datos

Device device("DeviceID", WIFI_SSID, WIFI_PASSWORD, API_ENDPOINT_URL, 0x27, 15, 2, 4, 419.8);


void setup() {
  device.init();
}

void loop() {
  device.readSensors();
  delay(5000);
}
