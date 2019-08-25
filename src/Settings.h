/*
 * General options
 */
#ifndef SETTINGS_H
#define SETTINGS_H

#define BLYNK_PORT                    80

#define BOARD_FIRMWARE_VERSION        "1.0.1"
#define BOARD_HARDWARE_VERSION        "1.0.0"

// TODO: This sucks.
#define OTA_FINGERPRINT               "CC:AA:48:48:66:46:0E:91:53:2C:9C:7C:23:2A:B1:74:4D:29:9D:33"
#define OTA_VERSION_URL               "https://raw.githubusercontent.com/telepath/a-hydro/master/ver.txt"
#define OTA_BIN_URL                   "https://github.com/telepath/a-hydro/releases/download"
#define OTA_FILE_NAME                 "firmware.bin"

#define BOARD_NAME                    "Tribal Tides"        // Name of your product. Should match App Export request info.
#define BOARD_VENDOR                  "Tribeshouse UG"        // Name of your company. Should match App Export request info.
#define BOARD_TEMPLATE_ID             "TMPL10092"

#define PRODUCT_WIFI_SSID             "Tribal Farm"         // Name of the device, to be displayed during configuration. Should match export request info.
#define BOARD_CONFIG_AP_URL           "tribal.farm"      // Config page will be available in a browser at 'http://our-product.cc/'

/*
 * Board configuration (see examples below).
 */

#if defined(BOARD_UNOBLYNK)

  // Custom board configuration
  #define BOARD_BUTTON_PIN            0                     // Pin where user button is attached
  #define BOARD_BUTTON_ACTIVE_LOW     true                  // true if button is "active-low"

  #define BOARD_LED_PIN               3                     // Set LED pin - if you have a single-color LED attached
  //#define BOARD_LED_PIN_R           15                    // Set R,G,B pins - if your LED is PWM RGB
  //#define BOARD_LED_PIN_G           12
  //#define BOARD_LED_PIN_B           13
  //#define BOARD_LED_PIN_WS2812      4                     // Set if your LED is WS2812 RGB
  #define BOARD_LED_INVERSE           false                 // true if LED is common anode, false if common cathode
  #define BOARD_LED_BRIGHTNESS        32                    // 0..255 brightness control

#elif defined(USE_CUSTOM_BOARD)

  // Custom board configuration
  #define BOARD_BUTTON_PIN            0                     // Pin where user button is attached
  #define BOARD_BUTTON_ACTIVE_LOW     true                  // true if button is "active-low"

  #define BOARD_LED_PIN               2                     // Set LED pin - if you have a single-color LED attached
  //#define BOARD_LED_PIN_R           15                    // Set R,G,B pins - if your LED is PWM RGB
  //#define BOARD_LED_PIN_G           12
  //#define BOARD_LED_PIN_B           13
  //#define BOARD_LED_PIN_WS2812      4                     // Set if your LED is WS2812 RGB
  #define BOARD_LED_INVERSE           false                 // true if LED is common anode, false if common cathode
  #define BOARD_LED_BRIGHTNESS        32                    // 0..255 brightness control

#elif defined(USE_NODE_MCU_BOARD)

  #warning "NodeMCU board selected"

  // Example configuration for NodeMCU v1.0 Board
  #define BOARD_BUTTON_ACTIVE_LOW     true

#if defined(BOARD_CHAINABLE_LED)
  #warning "Chainable LED configured"
  #define BOARD_LED_SER_PIN1          D7
  #define BOARD_LED_SER_PIN2          D8
  #define BOARD_NUM_LEDS              1
  #define BOARD_BUTTON_PIN            D3
#elif defined(BOARD_LED_BUTTON)
  #warning "LED button configured"
  #define BOARD_LED_PIN               D5                     // Set LED pin - if you have a single-color LED attached
  #define BOARD_BUTTON_PIN            D6
#else //LED
  #warning "LED and button configured"
  // #define BOARD_LED_PIN               D7                     // Set LED pin - if you have a single-color LED attached
  #define BOARD_BUTTON_PIN            0
  // #define BOARD_BUTTON_PIN            D3
  #define BOARD_LED_PIN_R             D8
  #define BOARD_LED_PIN_G             D7
  #define BOARD_LED_PIN_B             D9
#endif //LED
#define BOARD_LED_INVERSE           false
#define BOARD_LED_BRIGHTNESS        8

#else //BOARD
  #error "No board selected"
#endif //BOARD

#define BLYNK_GREEN     "#23C48E"
#define BLYNK_BLUE      "#04C0F8"
#define BLYNK_YELLOW    "#ED9D00"
#define BLYNK_RED       "#D3435C"
#define BLYNK_DARK_BLUE "#5F7CD8"
#define BLYNK_WHITE     "#FFFFFF"

/*
 * Advanced options
 */

#define BUTTON_HOLD_TIME_INDICATION   3000
#define BUTTON_HOLD_TIME_ACTION       10000

#define BOARD_PWM_MAX                 1023

#define WIFI_NET_CONNECT_TIMEOUT      30000
#define WIFI_CLOUD_CONNECT_TIMEOUT    15000
#define WIFI_AP_CONFIG_PORT           80
#define WIFI_AP_IP                    IPAddress(192, 168, 4, 1)
#define WIFI_AP_Subnet                IPAddress(255, 255, 255, 0)
//#define WIFI_CAPTIVE_PORTAL_ENABLE

#define USE_TICKER
//#define USE_TIMER_ONE
//#define USE_TIMER_THREE

#if defined(APP_DEBUG)
  #define DEBUG_PRINT(...) BLYNK_LOG1(__VA_ARGS__)
#else
  #define DEBUG_PRINT(...)
#endif

#endif
