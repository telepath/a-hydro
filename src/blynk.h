#ifndef BLYNK_H
#define BLYNK_H
#ifdef BLYNK
#include "config.h"
#include <BlynkSimpleEsp8266.h>
// #include <BlynkSimpleEsp8266_SSL.h>
#include "BlynkParamPlus.h"
// #define BLYNK_DEFAULT_CONFIG
#include "BlynkProvisioning.h"

// Params for each pin are stored here and can be accessed via e.g.:
// value = pinParams[pin].asInt();
BlynkParamPlus pinParams[PIN_NUM];
//
// const ConfigStore configDefault = {
//   0x626C6E6C,
//   BOARD_FIRMWARE_VERSION,
//   0, 0, 0,
//
//   "",
//   "",
//
//   "invalid token",
//   "blynk-cloud.com", BLYNK_PORT,
//   0
// };

#endif

#endif
