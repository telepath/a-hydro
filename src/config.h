#ifndef CONFIG_H
#define CONFIG_H

// #define BOARD_UNOBLYNK
// #define BOARD_UNO
// #define BOARD_MEGA

#define APP_DEBUG        // Comment this out to disable debug prints

#ifdef BOARD_NODEMCU
#define BLYNK
#define USE_NODE_MCU_BOARD
#define ENABLE_SONIC
#define ENABLE_SUNLIGHT
// #define BOARD_CHAINABLE_LED
#define BOARD_LED_BUTTON
#define ENABLE_OTA
#define SERIAL_DEBUG
#define BLYNK_PRINT Serial
#define DEBUG(ARG) Serial.print(ARG)
#define DEBUGLN(ARG) Serial.println(ARG)
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "38d6513c2ef64575af49b3f193697c6e"; //NodeMCU
#endif

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
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "3af3209925b846b1a5e405e5a7817bca"; //Uno
#endif //BOARD_UNO

#ifdef BOARD_MEGA
#define BLYNK
#define JOY_OLED
#define ENABLE_SONIC
#define ENABLE_SUNLIGHT
#define SERIAL_DEBUG
#define DEBUG(ARG) Serial.print(ARG)
#define DEBUGLN(ARG) Serial.println(ARG)
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "3a4c587bcb6646bc93644f262eb1de20"; //Mega
#endif //BOARD_MEGA

// digital pins
#define pumpPin D3
// int waterPin = 2;
// int upBtnPin = 8;
#define sonicPin D8

#define joyXPin A0
#define joyYPin joyXPin+1
bool joyInvert = false;

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
