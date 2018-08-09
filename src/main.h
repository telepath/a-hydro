#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <Wire.h>
#include <Automaton.h>
#include <MenuSystem.h>

#include "atm_vbutton.h"
#include "menu.h"
#include "config.h"

Atm_led pump_relais;
Atm_bit pump_bit;
Atm_bit pump_test_bit;
// Atm_digital water_sensor;
// Atm_button water_sensor;
// Atm_analog water_sensor;
Atm_controller pump_controller;
Atm_timer pumpOn_timer;
Atm_timer pumpOff_timer;
Atm_timer display_timer;
Atm_comparator joyX_comp;
Atm_comparator joyY_comp;
// Atm_button upBtn_button;

void pump_controller_onTrue(int idx, int v, int up);

void pump_controller_onFalse(int idx, int v, int up);

void pumpOn_onTimer(int idx, int v, int up);

void pumpOff_onTimer(int idx, int v, int up);

void drawIntLabel(unsigned char row, const char *label, int value = 0, bool indicator=false);

void drawDisplay();

void display_onTimer(int idx, int v, int up);

static uint16_t joy_threshold_list[] =
  { 400, 600, 900 };

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

void setup();

void loop();

#endif
