#include "DHTesp.h"
#include<HX711.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include "time.h"
#include <LiquidCrystal_I2C.h>

// Declare the variable that stores the pin for connecting the DHT11 sensor
int pinDHT = 15;
// Instantiate the DHT sensor
DHTesp dht;

// HX711
const int ld_cell=2;
const int ld_sck=4;

HX711 scale;
float calibration_factor = 419.8;  // Factor de calibración inicial, puede variar


// WiFi Credentials
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""


// Time zone adjustment
#define GMT_OFFSET_SEC -18000  // Offset de UTC -5 horas (Perú)
#define DAYLIGHT_OFFSET_SEC 0   // Sin horario de verano

// LCD setup
LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 16, 2);


// Function to get the current date and time
String getTime() {
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

void setup() {
  Serial.begin(115200);

  // LCD Startup
  LCD.init();
  LCD.backlight();
  LCD.setCursor(0, 0);
  LCD.print("Hi");
  LCD.setCursor(0, 1);
  LCD.print("WiFi ");


  // Initialize the DHT sensor
  dht.setup(pinDHT, DHTesp::DHT22);

  scale.begin(ld_cell,ld_sck);
  // WiFi setup
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected: ");
  Serial.println(WiFi.localIP());
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.println("Online");
  delay(500);

  if(scale.is_ready())
  {
    Serial.println("Calibrating... Remove all weights...");
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.println("Calibrating...");
    LCD.setCursor(0, 1);
    LCD.println("Remove all weights...");
    delay(5000);


    scale.tare();
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.println("Tare done.");
    LCD.setCursor(0, 1);
    LCD.println("Add known weight.");
    Serial.println("Tare done. Place a known weight.");
    delay(5000);

    long reading = scale.get_units(10);  // Obtener lectura promediada
    Serial.print("Raw reading: ");
    Serial.println(reading);

    long known_weight = 50.0;
    calibration_factor = reading / known_weight;
    scale.set_scale(calibration_factor);

    Serial.print("Calibration factor set to: ");
    Serial.println(calibration_factor);

  } else{
    Serial.println("Error: HX711 not found.");
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print("Error HX711");
  }

  // Time configuration
  configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, "pool.ntp.org");  // Ajuste con servidor NTP

}
void loop() {
  //Obtenemos el arreglo de datos (humedad y temperatura)
  TempAndHumidity data = dht.getTempAndHumidity();
  //Mostramos los datos de la temperatura y humedad
  Serial.println("Temperatura: " + String(data.temperature, 2) + "°C");

  // Mostrar temperatura en LCD
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("Temp: ");
  LCD.print(String(data.temperature, 2));
  LCD.print(" C");

  delay(500);
}


