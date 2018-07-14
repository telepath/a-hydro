#include "main.h"

MenuRenderer menu_renderer;
MenuSystem ms(menu_renderer);
Menu mu_pump("Pump");

void pump_controller_onTrue(int idx, int v, int up){
  // display.setInverseDisplay();
  menu_renderer.invert_display();
  // display.clearDisplay();
  pump_relais.on();
}

void pump_controller_onFalse(int idx, int v, int up){
  // display.setNormalDisplay();
  menu_renderer.normal_display();
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
//
// void drawIntLabel(unsigned char row, const char *label, int value = 0, bool indicator=false){
//   unsigned char text[6] = "";
//   if (value!=0) {
//     sprintf(text, "%3d ", value);
//   }
//
//   if (indicator) {
//     display.setTextXY(row,0);
//     display.putChar(menuIndicator);
//   }
//   display.setTextXY(row, 1);
//   display.putString(label);
//   display.setTextXY(row, 10);
//   display.putString(text);
// }
//
// void drawDisplay(){
//   // PumpOn Timer
//   drawIntLabel(0, "PumpOn:", pumpOn_timer.left() / 1000, true);
//
//   // PumpOff Timer
//   drawIntLabel(1, "PumpOff:", pumpOff_timer.left() / 1000);
// }

void display_onTimer(int idx, int v, int up){
  // drawDisplay();
  char string[15];
  if (pump_bit.state() == 1) {
    sprintf(string, "%-9s%5d", "PumpOff:", pumpOff_timer.left() / 1000);
    mu_pump.set_name(string);
  } else {
    sprintf(string, "%-9s%5d", "PumpOn:", pumpOn_timer.left() / 1000);
    mu_pump.set_name(string);
  }
  ms.display();
}

// void joystick_onUp(/* arguments */) {
//   Serial.println("joystick_onUp");
//   upBtn_button.event(upBtn_button.EVT_PRESS);
// }
//
// void upBtn_onPress( int idx, int v, int up ) {
//   ms.prev(true);
// }

void joystick_onUp(/* arguments */) {
  Serial.println("joystick_onUp");
  ms.prev(false);
}
void joystick_onDown(/* arguments */) {
  Serial.println("joystick_onDown");
  ms.next(false);
}
void joystick_onLeft(/* arguments */) {
  Serial.println("joystick_onLeft");
  ms.back();
}
void joystick_onRight(/* arguments */) {
  Serial.println("joystick_onRight");
  ms.select();
}
void joystick_onPush(/* arguments */) {
  Serial.println("joystick_onPush");
  // ms.select();
}
void joystick_reset(/* arguments */) {
  // upBtn_button.event(upBtn_button.EVT_RELEASE);
}
void joystick_onChange( int idx, int v, int up ) {
  if (idx == (int)'x' && v == 0 && up == false) {
    joystick_onLeft();
  }
  else if (idx == (int)'x' && v == 1 && up == true) {
    joystick_onRight();
  }
  else if (idx == (int)'x' && v == 2 && up == true) {
    joystick_onPush();
  }
  else if (idx == (int)'y' && v == 0 && up == false) {
    joystick_onDown();
  }
  else if (idx == (int)'y' && v == 1 && up == true) {
    joystick_onUp();
  }
  else if (v=0 && up == false){
    joystick_reset();
  }
}

void mu_pumpOn_onSelect(NumericMenuItem* p_menu_component){
  pumpOnSeconds = p_menu_component->get_value();

}
void mu_pumpOff_onSelect(NumericMenuItem* p_menu_component){
  pumpOffSeconds = p_menu_component->get_value();

}
// void mu_pump_reset_onSelect(MenuComponent* p_menu_component){
//
// }
// void mu_pump_test_onSelect(MenuComponent* p_menu_component){
//
// }
void mu_water_enable_onSelect(MenuComponent* p_menu_component){

}
void mu_water_simulate_onSelect(MenuComponent* p_menu_component){

}

void setup() {
  Wire.begin();

  //Setup Serial for debugging
  Serial.begin(9600);

  // //setup display
  // display.init();
  // display.clearDisplay();
  // display.setNormalDisplay();
  // display.setPageMode();
  // drawDisplay();
  // setup menu
  menu_renderer.setup_display();

  Menu mu_water("Water Sensor");
  ms.get_root_menu().add_menu(&mu_pump);
  ms.get_root_menu().add_menu(&mu_water);
  NumericMenuItem nmi_pumpOn("ON timer", &mu_pumpOn_onSelect, (float)pumpOnSeconds, 60.0, 604800.0, 30.0);
  mu_pump.add_item(&nmi_pumpOn);
  NumericMenuItem nmi_pumpOff("OFF timer", &mu_pumpOff_onSelect, (float)pumpOffSeconds, 10.0, 3600.0, 5.0);
  mu_pump.add_item(&nmi_pumpOff);
  // ms.display();

  //setup pump relay
  pump_relais.begin(pumpPin);

  //setup pump bit
  pump_bit.begin();

  //setup pump start timer
  pumpOn_timer.begin()
    .interval_seconds(pumpOnSeconds)
    .repeat(-1)
    .onTimer(pumpOn_onTimer)
    // .onChange(pumpOn_onChange)
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

  //setup pump safety
  pump_controller.begin()
    .IF(pump_bit)
    // .AND(water_sensor)
    .onChange(true, pump_controller_onTrue)
    .onChange(false, pump_controller_onFalse);

  //setup joystick
  joyX_comp.begin(joyXPin, 50)
    // .trace(Serial)
    .threshold(joy_threshold_list, sizeof(joy_threshold_list) )
    .onChange(true, joystick_onChange, (int)'x' )
    .onChange(false, joystick_onChange, (int)'x' );
  joyY_comp.begin(joyYPin, 50)
    // .trace(Serial)
    .threshold(joy_threshold_list, sizeof(joy_threshold_list) )
    .onChange(true, joystick_onChange, (int)'y' )
    .onChange(false, joystick_onChange, (int)'y' );
}

void loop() {
  automaton.run();
}
