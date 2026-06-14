# mybase_esp32_OTA_webserial

Библиотека для ESP32 (включая ESP32-C3) с поддержкой OTA-обновлений и WebSerial.

## Установка

1. Установите зависимости:
   - [ESPAsyncWebServer](https://github.com/ESP32Async/ESPAsyncWebServer)
   - [AsyncWebSerial](https://github.com/circuitcode/AsyncWebSerial)

2. Скопируйте папку библиотеки в директорию `libraries` вашего Arduino IDE или PlatformIO проекта.

## Возможности

- Подключение к Wi-Fi сети
- OTA-обновление прошивки по воздуху
- WebSerial интерфейс для отладки и управления через браузер (`http://<IP>/webserial`)
- Пример управления светодиодом

## Использование

```cpp
#include <mybase_esp32_OTA_webserial.h>

const char* ssid = "your_ssid";
const char* password = "your_password";

void setup() {
  Serial.begin(115200);
  
  // Настройка Wi-Fi
  setupWiFi(ssid, password);
  
  // Настройка OTA (hostname, пароль)
  setupOTA("esp32c3-my-project1", "1234"); //mDNS
  // также будет доступен WebSerial по адресу http://esp32c3-my-project1/webserial
  
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  webSerial.print("Hello, World!");
}

void loop() {
  ArduinoOTA.handle();  // Обязательно для работы OTA
  // handleBlink();
  webSerial.loop();     // Обработка WebSerial

  //  Ваш код...
}
```

## WebSerial

После подключения откройте в браузере: `http://<IP-адрес>/webserial`

Примеры команд:
- `LED_ON` — включить светодиод
- `LED_OFF` — выключить светодиод
