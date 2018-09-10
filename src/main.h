#ifndef MAIN_H
#define MAIN_H

#include <Wire.h>
#include <Automaton.h>
#include "config.h"
#ifdef ENABLE_SONIC
#include <Ultrasonic.h>
#endif
#ifdef BLYNK
#ifndef BOARD_NODEMCU
// #include <BlynkSimpleShieldEsp8266.h>
#endif
#ifdef BOARD_NODEMCU
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#endif //BOARD_NODEMCU
#include "BlynkProvisioning.h"
#include "blynk.h"
#endif //BLYNK
#ifdef JOY_OLED
#include <MenuSystem.h>
#include "menu.h"
#endif

Atm_bit pump_relais;
Atm_bit pump_bit;
Atm_bit pump_test_bit;
Atm_controller pump_controller;
Atm_timer pumpOn_timer;
Atm_timer pumpOff_timer;
#ifdef JOY_OLED
Atm_timer display_timer;
#endif
#ifdef ENABLE_SONIC
Atm_timer sonic_timer;
#endif
// #ifdef BLYNK
// Atm_timer blynk_timer;
// #endif
#ifdef JOY_OLED
Atm_comparator joyX_comp;
Atm_comparator joyY_comp;
#endif

void sonicWrite();

void pump_controller_onTrue(int idx, int v, int up);

void pump_controller_onFalse(int idx, int v, int up);

void pumpOn_onTimer(int idx, int v, int up);

void pumpOff_onTimer(int idx, int v, int up);

void drawIntLabel(unsigned char row, const char *label, int value = 0, bool indicator=false);

void drawDisplay();

#ifdef JOY_OLED
void display_onTimer(int idx, int v, int up);
#endif
void sonic_onTimer(int idx, int v, int up);

void write_tankLevel();

static uint16_t joy_threshold_list[] =
  { 400, 600, 900 };

#ifdef JOY_OLED
void joystick_onUp(/* arguments */);
void joystick_onDown(/* arguments */);
void joystick_onLeft(/* arguments */);
void joystick_onRight(/* arguments */);
void joystick_onPush(/* arguments */);
void joystick_onChange( int idx, int v, int up );

void setup_menu();

void mu_pumpOn_onSelect(NumericMenuItem* p_menu_component);
void mu_pumpOff_onSelect(NumericMenuItem* p_menu_component);
void mu_pump_reset_onSelect(MenuComponent* p_menu_component);
void mu_pump_test_onSelect(MenuComponent* p_menu_component);
void mu_water_enable_onSelect(MenuComponent* p_menu_component);
void mu_water_simulate_onSelect(MenuComponent* p_menu_component);
#endif

void setup();

void loop();

#endif
