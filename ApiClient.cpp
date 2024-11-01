// ApiClient.cpp

#include "ApiClient.h"

ApiClient::ApiClient() {
}

void ApiClient::sendTemperatureToAPI(const String& endpoint, const String& deviceID, float temperature, const String& currentTime) {
    httpClient.begin(endpoint);
    httpClient.addHeader("Content-Type", "application/json");

    // Create JSON object
    StaticJsonDocument<200> dataRecord;
    dataRecord["idsensor"] = deviceID;
    dataRecord["temperature"] = temperature;
    dataRecord["time"] = currentTime;

    // Serialize and send data
    String payload;
    serializeJson(dataRecord, payload);
    int httpResponseCode = httpClient.POST(payload);

    // Check HTTP response
    if (httpResponseCode > 0) {
        Serial.println("Temperature data sent");
    } else {
        Serial.print("Error sending temperature: ");
        Serial.println(httpResponseCode);
    }

    httpClient.end();
}

void ApiClient::sendWeightToAPI(const String& endpoint, const String& deviceID, float weight, const String& currentTime) {
    httpClient.begin(endpoint);
    httpClient.addHeader("Content-Type", "application/json");

    // Create JSON object
    StaticJsonDocument<200> dataRecord;
    dataRecord["idsensor"] = deviceID;
    dataRecord["weight"] = weight;
    dataRecord["time"] = currentTime;

    // Serialize and send data
    String payload;
    serializeJson(dataRecord, payload);
    int httpResponseCode = httpClient.POST(payload);

    // Check HTTP response
    if (httpResponseCode > 0) {
        Serial.println("Weight data sent");
    } else {
        Serial.print("Error sending weight: ");
        Serial.println(httpResponseCode);
    }

    httpClient.end();
}
