# TransportApp Embedded Application

## Summary
TransportApp Embedded System is an IoT application designed to monitor in real time critical data such as temperature, weight and location of vehicles in a transportation system. This embedded application, implemented in the Wokwi simulator, uses various sensors to capture and transmit information, facilitating efficient transportation management and tracking of moving assets.

## Components
- DHT22: Temperature and humidity sensor, in charge of monitoring the environmental conditions inside the vehicle.
- HX711: Load sensor with weigh cell, used to measure the weight of the load in real time.
- GPS NEO-6M: Global positioning sensor, which allows tracking the location and speed of the vehicle.

## Key Functionalities
- Real-time monitoring: Captures and sends temperature, weight and location data to defined endpoints for analysis and storage.
- User interface: Uses an LCD screen to display relevant data from each sensor.
- Wi-Fi connectivity: Connects to Wi-Fi networks to transmit data to the cloud or a remote monitoring platform.

# Libraries
- DHT sensor library for ESPx
- Time
- ArduinoJson
- LiquidCrystal I2C
- WiFi
- WiFiWire
- HttpClient
- HX711
- HX711 Arduino Library
- TinyGPSPlus
