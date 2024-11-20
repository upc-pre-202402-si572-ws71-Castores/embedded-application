#include "Device.h"
#include "time.h"

#define GMT_OFFSET_SEC -18000  // Offset de UTC -5 horas (Perú)
#define DAYLIGHT_OFFSET_SEC 0   // Sin horario de verano

Device::Device(const String& id, const String& ssid, const String& password, const String& endpoint,
               uint8_t lcdAddr, int dhtPin, int hx711DT, int hx711SCK, float hx711Calibration)
    : deviceID(id), wifiSSID(ssid), wifiPassword(password), apiEndpoint(endpoint),
      lcd(lcdAddr, 16, 2), dht22(dhtPin), hx711(hx711DT, hx711SCK, hx711Calibration) {}

void Device::init() {
    Serial.begin(115200);

    // Initialize LCD
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Connecting to ");
    lcd.setCursor(0, 1);
    lcd.print("WiFi");

    // Connect to WiFi
    connectWiFi();
    // Configure time
    configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, "pool.ntp.org");

    dht22.init();
    hx711.init();
}

void Device::connectWiFi() {
    Serial.println("Connecting to WiFi...");
    WiFi.begin(wifiSSID.c_str(), wifiPassword.c_str());


    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
        attempts++;

    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi connected");
        lcd.clear();
        lcd.print("WiFi connected");
    } else {
        Serial.println("\nWiFi connection failed");
        lcd.clear();
        lcd.print("WiFi Error");
    }

    lcd.clear();
    lcd.print("WiFi connected");
    Serial.println("Connected to WiFi");
}

void Device::readSensors() {
    // Leer sensores
    float temperature = dht22.readTemperature();
    float weight = hx711.readWeight();

    if (weight != -1) {
        // Enviar datos al API
        int requestId = 1; // Cambiar según sea necesario
        apiClient.sendDataToAPI(apiEndpoint, requestId, temperature, weight);

        // Mostrar en LCD
        displayTemperature(temperature);
        displayWeight(weight);
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
