// mybase_esp32_OTA_webserial.h
#ifndef MYBASE_H_mybase_esp32_OTA_webserial
#define MYBASE_H_mybase_esp32_OTA_webserial

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#else
#include <WiFi.h>
#include <ESPmDNS.h>
#endif

#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#ifndef ESP8266
#include <AsyncWebSerial.h> //https://github.com/circuitcode/AsyncWebSerial
//install https://github.com/ESP32Async/ESPAsyncWebServer
//AsyncWebSerial - в ESP8266 ее использовать невозможно
#endif

extern const int ledPin;

void setupWiFi(const char* ssid, const char* password);
void setupOTA(const char* hostname, const char* password);
void handleBlink();

#ifndef ESP8266
extern AsyncWebServer server;  // extern означает "определено в другом месте"
extern AsyncWebSerial webSerial;
// void onMessage(const String& msg);
typedef void (*WebSerialHandler)(const String& msg);

void setWebSerialHandler(WebSerialHandler handler);
void defaultWebSerialHandler(const String& msg);

#endif

#endif
