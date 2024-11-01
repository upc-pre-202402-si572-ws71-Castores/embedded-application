// GPSHandler.cpp

#include "GPSHandler.h"
#include <HardwareSerial.h>

GPSHandler::GPSHandler(int rxPin, int txPin, int baudRate)
    : rxPin(rxPin), txPin(txPin), baudRate(baudRate) {}

void GPSHandler::init() {
    Serial.begin(9600);
    Serial.println(F("NEO6M GPS Module Simulation on ESP32"));
    Serial2.begin(baudRate, SERIAL_8N1, rxPin, txPin);
}

void GPSHandler::readGPS() {
    if (Serial2.available() > 0) {
        if (gps.encode(Serial2.read())) {
            Serial.print(F("Location:\t("));
            if (gps.location.isValid()) {
                Serial.print(F("Latitude: ")); Serial.print(gps.location.lat(), 6); Serial.print(F(", "));
                Serial.print(F("Longitude: ")); Serial.print(gps.location.lng(), 6); Serial.print(F(", "));
                Serial.print(F("Altitude: "));
                if (gps.altitude.isValid()) Serial.print(gps.altitude.meters());
                else Serial.print(F("INVALID"));
            } else {
                Serial.print(F("INVALID"));
            }
            Serial.println(F(")"));

            Serial.print(F("Speed:\t\t"));
            if (gps.speed.isValid()) {
                Serial.print(gps.speed.kmph()); Serial.println(F(" km/h"));
            } else {
                Serial.println(F("INVALID"));
            }

            Serial.print(F("GPS Date&Time:\t"));
            if (gps.date.isValid() && gps.time.isValid()) {
                Serial.print(gps.date.year()); Serial.print(F("-"));
                Serial.print(gps.date.month()); Serial.print(F("-"));
                Serial.print(gps.date.day()); Serial.print(F(" "));
                Serial.print(gps.time.hour()); Serial.print(F(":"));
                Serial.print(gps.time.minute()); Serial.print(F(":"));
                Serial.print(gps.time.second());
            } else {
                Serial.println(F("INVALID"));
            }
            Serial.println();
        }
    }

    // No GPS Data Exception
    if (millis() > 10000 && gps.charsProcessed() < 10) {
        Serial.println(F("No GPS data received: check your wiring"));
    }
}
