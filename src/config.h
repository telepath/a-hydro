#ifndef CONFIG_H
#define CONFIG_H

#ifdef BOARD_NODEMCU
#include <Arduino.h>
#include <BlynkSimpleEsp8266.h>
// #include <BlynkSimpleEsp8266_SSL.h>

#define BLYNK
#define USE_NODE_MCU_BOARD
#define ENABLE_SONIC
#define ENABLE_SUNLIGHT
#define ENABLE_MOISTURE
// #define BOARD_LED_BUTTON
#define BOARD_CHAINABLE_LED
#define ENABLE_OTA
#define SERIAL_DEBUG
#define APP_DEBUG
// #define BLYNK_PRINT Serial
// #define DEBUG(ARG) Serial.print(ARG)
// #define DEBUGLN(ARG) Serial.println(ARG)
#define BLYNK_PRINT terminal
#define DEBUG(ARG) terminal.print(ARG)
#define DEBUGLN(ARG) terminal.println(ARG)
#include <Arduino.h>
#include "Settings.h" // Custom BlynkProvisioning settings

#endif //BOARD_NODEMCU

#ifdef BOARD_UNO
#define SERIAL_DEBUG
#define DEBUG(ARG) Serial.print(ARG)
#define DEBUGLN(ARG) Serial.println(ARG)
#define ENABLE_SONIC
#define JOY_OLED
#endif //BOARD_UNO

#ifdef BOARD_UNOBLYNK
#define DEBUG(ARG)
#define DEBUGLN(ARG)
#define ENABLE_SONIC
#define BLYNK
#define BLYNK_NO_BUILTIN   // Disable built-in analog & digital pin operations
#define BLYNK_NO_FLOAT     // Disable float operations
#endif //BOARD_UNO

#ifdef BOARD_MEGA
#define BLYNK
#define JOY_OLED
#define ENABLE_SONIC
#define ENABLE_SUNLIGHT
#define SERIAL_DEBUG
#define DEBUG(ARG) Serial.print(ARG)
#define DEBUGLN(ARG) Serial.println(ARG)
#endif //BOARD_MEGA

// Hardware Serial on Mega, Leonardo, Micro...
#ifdef BOARD_MEGA
#define EspSerial Serial1
#endif
#ifdef BOARD_UNOBLYNK
#define EspSerial Serial
#endif
// or Software Serial on Uno, Nano...
// #include <SoftwareSerial.h>
// SoftwareSerial EspSerial(2, 3); // RX, TX

// Your ESP8266 baud rate:
#ifndef BOARD_NODEMCU
#define ESP8266_BAUD 115200
#endif

#ifndef SERIAL_DEBUG

  #define DEBUG
  #define DEBUGLN
#endif

#ifdef BLYNK
  enum pins {
    SONIC,          //vPin 0
    PUMP_TIME,      //vPin 1
    PUMP_STATE,     //vPin 2
    LIGHT_IR,       //vPin 3
    LIGHT_VS,       //vPin 4
    LIGHT_UV,       //vPin 5
    VERSION,        //vPin 6
    MOISTURE,       //vPin 7
    EMPTY3,         //vPin 8
    TERMINAL,       //vPin 9
    SETTINGS_SONIC_SECONDS, //vPin 10
    SETTINGS_BLYNK_MILLIS,  //vPin 11
    SETTINGS_PUMP_ON_MIN,   //vPin 12
    SETTINGS_PUMP_OFF_SEC,  //vPin 13
    SETTINGS_TANK_EMPTY,    //vPin 14
    SETTINGS_TANK_FULL,     //vPin 15
    SETTINGS_OTA_VERSION,   //vPin 16
    SETTINGS_OTA_UPDATE,    //vPin 17
    PIN_NUM         //last item, number of pins
  };
#endif

WidgetTerminal terminal(TERMINAL);  // Comment this out if you won't use the terminal widget

// digital pins
#define pumpPin D6
// int waterPin = 2;
// int upBtnPin = 8;
#define sonicPin D5

#ifdef JOY_OLED
  #define joyXPin A0
  #define joyYPin joyXPin+1
  bool joyInvert = false;
#elifdef ENABLE_MOISTURE
  #define moisturePin A0
#endif //JOY_OLED

int sonicSeconds = 30;
int sonicSecondsFast = 10;

int blynkMillis = 1000;
int sunlightSeconds = 60;

int tankFull = 5;
int tankEmpty = 50;

int pumpOffSeconds = 30;
int pumpOnSeconds = 0.25 * 60.0 * 60;

int displayUpdate = 250; //ms

#endif
