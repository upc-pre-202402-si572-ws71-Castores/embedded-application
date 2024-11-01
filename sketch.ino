#include "Device.h"
#include "GPSHandler.h"
// WiFi Credentials and API Endpoints
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
#define TEMP_ENDPOINT_URL "https://transportapp.free.beeceptor.com/api/v1/temperature"
#define WEIGHT_ENDPOINT_URL "https://transportapp.free.beeceptor.com/api/v1/weight"

Device DHT22(15, 2, 4, 419.8, "DHT22", WIFI_SSID, WIFI_PASSWORD, TEMP_ENDPOINT_URL, WEIGHT_ENDPOINT_URL, 0x27);
Device HX711(15, 2, 4, 419.8, "HX711", WIFI_SSID, WIFI_PASSWORD, TEMP_ENDPOINT_URL, WEIGHT_ENDPOINT_URL, 0x27);
GPSHandler gpsHandler(16, 17, 9600); // Pines RX y TX del GPS


void setup() {
    DHT22.init();
    HX711.init();
    gpsHandler.init();
}

void loop() {
    DHT22.readTemperature();
    HX711.readWeight();
    gpsHandler.readGPS();
    delay(5000);  // Adjust delay as needed
}

