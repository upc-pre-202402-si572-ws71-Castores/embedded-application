// ApiClient.h

#ifndef APICLIENT_H
#define APICLIENT_H

#include <ArduinoJson.h>
#include <HTTPClient.h>

class ApiClient {
private:
    HTTPClient httpClient;

public:
    ApiClient();
    void sendTemperatureToAPI(const String& endpoint, const String& deviceID, float temperature, const String& currentTime);
    void sendWeightToAPI(const String& endpoint, const String& deviceID, float weight, const String& currentTime);
};

#endif
