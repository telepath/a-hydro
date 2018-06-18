#include <Arduino.h>
#include <Wire.h>
#include <Automaton.h>
#include <SeeedOLED.h>

#include "config.h"

Atm_led pump_relais;
Atm_bit pump_bit;
// Atm_digital water_sensor;
// Atm_button water_sensor;
// Atm_analog water_sensor;
Atm_controller pump_controller;
Atm_timer pumpOn_timer;
Atm_timer pumpOff_timer;
Atm_timer display_timer;
SeeedOLED display;

void pump_controller_onTrue(int idx, int v, int up){
  display.setInverseDisplay();
  // display.clearDisplay();
  pump_relais.on();
}

void pump_controller_onFalse(int idx, int v, int up){
  display.setNormalDisplay();
  pump_relais.off();
}

void pumpOn_onTimer(int idx, int v, int up){
  // pump_relais.on();
  pump_bit.on();
  pumpOff_timer.start();
}

void pumpOff_onTimer(int idx, int v, int up){
  // pump_relais.on();
  pump_bit.off();
}

void drawIntLabel(unsigned char row, const char *label, int value, bool indicator=false){
  unsigned char text[6] = "";
  sprintf(text, "%3d ", value);

  if (indicator) {
    display.setTextXY(row,0);
    display.putChar(menuIndicator);
  }
  display.setTextXY(row, 1);
  display.putString(label);
  display.setTextXY(row, 10);
  display.putString(text);
}

void drawDisplay(){
  // PumpOn Timer
  drawIntLabel(0, "PumpOn:", pumpOn_timer.left() / 1000, true);

  // PumpOff Timer
  drawIntLabel(1, "PumpOff:", pumpOff_timer.left() / 1000);
}

void display_onTimer(int idx, int v, int up){
  drawDisplay();
}

void setup() {
  Wire.begin();

  //Setup Serial for debugging
  // Serial.begin(9600);

  //setup display
  display.init();
  display.clearDisplay();
  display.setNormalDisplay();
  display.setPageMode();
  drawDisplay();

  //setup pump relay
  pump_relais.begin(pumpPin);

  //setup pump bit
  pump_bit.begin();

  //setup pump start timer
  pumpOn_timer.begin()
    .interval_seconds(pumpOnSeconds)
    .repeat(-1)
    .onTimer(pumpOn_onTimer)
    .start();

  //setup pump stop timer
  pumpOff_timer.begin()
    .interval_seconds(pumpOffSeconds)
    .onTimer(pumpOff_onTimer);

  display_timer.begin()
    .interval_millis(displayUpdate)
    .repeat(ATM_COUNTER_OFF)
    .onTimer(display_onTimer)
    .start();

  //setup water sensor
  // water_sensor.begin(waterPin);
  // water_sensor.begin(waterPin,waterTimeout,true,true).trace(Serial);
  // water_sensor.begin(A0).trace(Serial);

  //setup pump safety controller
  pump_controller.begin()
    .IF(pump_bit)
    // .AND(water_sensor)
    .onChange(true, pump_controller_onTrue)
    .onChange(false, pump_controller_onFalse);

}

void loop() {
  automaton.run();
}
