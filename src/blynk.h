#ifdef BLYNK

#define sonicVPin V0
#define pumpOnVPin V1

#define pumpVPin V2

#define lightIrVPin V3
#define lightVsVPin V4
#define lightUvVPin V5

#define sonicSecondsVPin V10
#define blynkMillisVPin V11

#define pumpOnMinutesVPin V12
#define pumpOffSecondsVPin V13

#define tankEmptyVPin V14
#define tankFullVPin V15

/* Comment this out to disable prints and save space */
#ifdef SERIAL_DEBUG
#define BLYNK_PRINT Serial // Defines the object that is used for printing
#define BLYNK_DEBUG        // Optional, this enables more detailed prints
#endif
#ifdef BOARD_UNO
#define BLYNK_NO_BUILTIN   // Disable built-in analog & digital pin operations
#define BLYNK_NO_FLOAT     // Disable float operations
#endif

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

#define BOARD_TEMPLATE_ID "TMPL10092"

#define BLYNK_GREEN     "#23C48E"
#define BLYNK_BLUE      "#04C0F8"
#define BLYNK_YELLOW    "#ED9D00"
#define BLYNK_RED       "#D3435C"
#define BLYNK_DARK_BLUE "#5F7CD8"
#endif
