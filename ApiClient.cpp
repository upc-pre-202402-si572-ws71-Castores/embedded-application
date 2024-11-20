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
void ApiClient::sendDataToAPI(const String& endpoint, int requestId, float temperature, float weight) {
    String fullEndpoint = endpoint + String(requestId); // Construir URL con requestId
    httpClient.begin(fullEndpoint);

    // Agregar encabezados
    httpClient.addHeader("Content-Type", "application/json");
    httpClient.addHeader("Authorization", "Bearer eyJhbGciOiJIUzM4NCJ9.eyJzdWIiOiJyb2RAeW9wbWFpbC5jb20iLCJpYXQiOjE3MzIwNjk3NDMsImV4cCI6MTczMjY3NDU0M30.ssivqWxk-ML19CZCbm9SVZGPV86ZqEdffJr_jQ5mTEgdFwli3z4c7lU6OKgaQAIP"); // Reemplaza con tu token

    // Crear objeto JSON
    StaticJsonDocument<200> dataRecord;
    dataRecord["requestId"] = requestId;
    dataRecord["updatedTemperature"] = temperature;
    dataRecord["updatedWeight"] = weight;

    // Serializar y enviar datos
    String payload;
    serializeJson(dataRecord, payload);
    int httpResponseCode = httpClient.PUT(payload);

    // Manejar la respuesta HTTP
    if (httpResponseCode > 0) {
        Serial.print("HTTP Response Code: ");
        Serial.println(httpResponseCode);

        // Leer el cuerpo de la respuesta
        String responseBody = httpClient.getString();
        Serial.println("Response Body:");
        Serial.println(responseBody);
    } else {
        Serial.print("Error sending data: ");
        Serial.println(httpResponseCode);
        Serial.println(httpClient.errorToString(httpResponseCode));
    }

    httpClient.end();
}