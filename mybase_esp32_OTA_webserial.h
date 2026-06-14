// mybase_esp32_OTA_webserial.h
#ifndef MYBASE_H_mybase_esp32_OTA_webserial
#define MYBASE_H_mybase_esp32_OTA_webserial

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <AsyncWebSerial.h> //https://github.com/circuitcode/AsyncWebSerial
//install https://github.com/ESP32Async/ESPAsyncWebServer

extern AsyncWebServer server;  // extern означает "определено в другом месте"
extern AsyncWebSerial webSerial;
extern const int ledPin;

void setupWiFi(const char* ssid, const char* password);
void setupOTA(const char* hostname, const char* password);
void handleBlink();
void onMessage(const String& msg);

#endif
