#ifdef BLYNK
int sonicVPin = V0;
int pumpOnVPin = V1;

int pumpVPin = V2;

int sonicSecondsVPin = V10;
int blynkMillisVPin = V11;

int pumpOnMinutesVPin = V12;
int pumpOffSecondsVPin = V13;

int tankEmptyVPin = V14;
int tankFullVPin = V15;

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial // Defines the object that is used for printing
#define BLYNK_DEBUG        // Optional, this enables more detailed prints
// #define BLYNK_NO_BUILTIN   // Disable built-in analog & digital pin operations
// #define BLYNK_NO_FLOAT     // Disable float operations

// Hardware Serial on Mega, Leonardo, Micro...
#define EspSerial Serial1

// or Software Serial on Uno, Nano...
// #include <SoftwareSerial.h>
// SoftwareSerial EspSerial(2, 3); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

#define BOARD_TEMPLATE_ID "TMPL10092"

#define BLYNK_GREEN     "#23C48E"
#define BLYNK_BLUE      "#04C0F8"
#define BLYNK_YELLOW    "#ED9D00"
#define BLYNK_RED       "#D3435C"
#define BLYNK_DARK_BLUE "#5F7CD8"
#endif
