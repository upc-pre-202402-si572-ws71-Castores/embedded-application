// Device.cpp

#include "Device.h"
#include "time.h"

// Ajuste de la zona horaria
#define GMT_OFFSET_SEC -18000  // Offset de UTC -5 horas (Perú)
#define DAYLIGHT_OFFSET_SEC 0   // Sin horario de verano


Device::Device(int dhtPin, int cellPin, int sckPin, float calibration, const String& id, const String& ssid, const String& password, const String& tempUrl, const String& weightUrl, uint8_t lcdAddr) :
    pinDHT(dhtPin), ld_cell(cellPin), ld_sck(sckPin), calibration_factor(calibration),
    deviceID(id), wifiSSID(ssid), wifiPassword(password), tempEndpoint(tempUrl), weightEndpoint(weightUrl),
    lcd(lcdAddr, 16, 2)
{
}

void Device::init() {
    Serial.begin(115200);
    
    // LCD startup
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Connecting to ");
    lcd.setCursor(0, 1);
    lcd.print("WiFi ");

    // Initialize DHT sensor
    dht.setup(pinDHT, DHTesp::DHT22);

    // Initialize scale
    scale.begin(ld_cell, ld_sck);
    if (scale.is_ready()) {
        Serial.println("Calibrating... Remove all weights...");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.println("Calibrating...");
        delay(5000);
        scale.tare();
        scale.set_scale(calibration_factor);
        lcd.clear();
        lcd.println("Calibration done.");
    } else {
        lcd.clear();
        lcd.print("Error HX711");
    }

    // WiFi setup
    WiFi.begin(wifiSSID.c_str(), wifiPassword.c_str());

    Serial.println("Connected to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    }
    lcd.clear();
    lcd.println("WiFi connected");
    
    // Configure time
    configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, "pool.ntp.org");
}

String Device::getTime() {
    time_t now;
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return "N/A";
    }
    char buffer[80];
    strftime(buffer, 80, "%d/%m/%Y %H:%M", &timeinfo);
    return String(buffer);
}

void Device::readTemperature() {
    TempAndHumidity data = dht.getTempAndHumidity();
    displayTemperature(data.temperature);
    apiClient.sendTemperatureToAPI(tempEndpoint, deviceID, data.temperature, getTime());
}

void Device::readWeight() {
    if (scale.is_ready()) {
        long weight = scale.get_units(10);
        displayWeight(weight);
        apiClient.sendWeightToAPI(weightEndpoint, deviceID, weight, getTime());
    } else {
        lcd.setCursor(0, 1);
        lcd.print("Weight Error");
    }
}

void Device::displayTemperature(float temperature) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(String(temperature, 2));
    lcd.print(" C");
}

void Device::displayWeight(float weight) {
    lcd.setCursor(0, 1);
    lcd.print("Weight: ");
    lcd.print(weight);
    lcd.print(" Kg");
}
