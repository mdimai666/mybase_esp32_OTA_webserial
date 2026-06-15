// mybase_esp32_OTA_webserial.cpp
#include "mybase_esp32_OTA_webserial.h"

#ifndef ESP8266
// Определение глобальных объектов
AsyncWebServer server(80); //http://192.168.3.89/webserial
AsyncWebSerial webSerial;
#endif
const int ledPin = LED_BUILTIN;

// Переменные для мигания
unsigned long previousMillis = 0;
const long interval = 1000;
bool ledState = HIGH;

void setupWiFi(const char* ssid, const char* password) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  
  #ifndef ESP8266
  webSerial.begin(&server);
  server.begin();
  webSerial.onMessage(onMessage);
  #endif
}

void setupOTA(const char* hostname, const char* password) {
  ArduinoOTA.setHostname(hostname);
  ArduinoOTA.setPassword(password);
  
  ArduinoOTA.onStart([]() {
    digitalWrite(ledPin, LOW);
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) type = "sketch";
    else type = "filesystem";
    Serial.println("Start updating " + type);
  });
  
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  
  ArduinoOTA.begin();
}

void handleBlink() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }
}

#ifndef ESP8266
void onMessage(const String& msg) {
  webSerial.print("Получено сообщение: ");
  webSerial.print(msg);
  
  if (msg == "LED_ON") {
    digitalWrite(ledPin, LOW);
    webSerial.print("Светодиод ВКЛ");
  } else if (msg == "LED_OFF") {
    digitalWrite(ledPin, HIGH);
    webSerial.print("Светодиод ВЫКЛ");
  }
}
#endif