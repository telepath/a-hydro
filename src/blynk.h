#ifndef BLYNK_H
#define BLYNK_H
#ifdef BLYNK
#include "config.h"
#include <BlynkSimpleEsp8266.h>
#include "BlynkParamPlus.h"

// Params for each pin are stored here and can be accessed via e.g.:
// value = pinParams[pin].asInt();
BlynkParamPlus pinParams[PIN_NUM];
#endif

#endif
