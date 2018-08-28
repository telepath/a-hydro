#include "main.h"

Ultrasonic ultrasonic(sonicPin);
MenuRenderer menu_renderer;
MenuSystem ms(menu_renderer);
Menu mu_pump("Pump");

void pump_test_bit_onChange(int idx, int v, int up) {
  if (pump_test_bit.state()) {
    pumpOn_timer.trigger(pumpOn_timer.EVT_STOP);
  } else {
    pumpOn_timer.trigger(pumpOn_timer.EVT_START);
  }
}

void pump_controller_onTrue(int idx, int v, int up){
  Serial.println("pump_controller_onTrue");
  // display.setInverseDisplay();
  menu_renderer.invert_display();
  // display.clearDisplay();
  pump_relais.on();
}

void pump_controller_onFalse(int idx, int v, int up){
  Serial.println("pump_controller_onFalse");
  // display.setNormalDisplay();
  menu_renderer.normal_display();
  pump_relais.off();
}

void pumpOn_onTimer(int idx, int v, int up){
  Serial.println("pumpOn_onTimer");
  // pump_relais.on();
  pump_bit.on();
  pumpOff_timer.start();
}

void pumpOff_onTimer(int idx, int v, int up){
  Serial.println("pumpOff_onTimer");
  // pump_relais.on();
  pump_bit.off();
void sonic_onTimer(int idx, int v, int up){
  int cm = ultrasonic.MeasureInCentimeters();
  Serial.println("sonic_onTimer");
  Serial.print("measured ");
  Serial.print(cm);
  Serial.print(" cm");
  Serial.println("");
  Serial.print("Tank ");
  Serial.print(tankEmpty);
  Serial.print("/");
  Serial.print(tankFull);
  Serial.println("");
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
  char left[7];
  if (pump_bit.state() == 1) {
    sprintf(string, "%-9s%5s ", "PumpOff:", dtostrf(pumpOff_timer.left() / 1000.0, 5, 0, left));
    mu_pump.set_name(string);
  } else {
    sprintf(string, "%-9s%5sh", "PumpOn:", dtostrf(pumpOn_timer.left() / 1000.0 / 60.0 / 60.0, 3, 2, left));
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
  ms.select();
}
void joystick_reset(/* arguments */) {
  // upBtn_button.event(upBtn_button.EVT_RELEASE);
}
void joystick_onChange( int idx, int v, int up ) {
  if (idx == (int)'x' && v == 0 && up == false) {
    if (joyInvert) {
      joystick_onRight();
    }
    else {
      joystick_onLeft();
    }
  }
  else if (idx == (int)'x' && v == 1 && up == true) {
    if (joyInvert) {
      joystick_onLeft();
    } else {
      joystick_onRight();
    }
  }
  else if (idx == (int)'x' && v == 2 && up == true) {
    joystick_onPush();
  }
  else if (idx == (int)'y' && v == 0 && up == false) {
    if (joyInvert) {
      joystick_onUp();
    } else {
      joystick_onDown();
    }
  }
  else if (idx == (int)'y' && v == 1 && up == true) {
    if (joyInvert) {
      joystick_onDown();
    } else {
      joystick_onUp();
    }
  }
  else if (v == 0 && up == false){
    joystick_onPush();
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
void mi_pumpTest_onSelect(MenuComponent* p_menu_component){
  pump_test_bit.toggle();
  if (pump_test_bit.state()) {
    p_menu_component->set_name("Test (ON)");
  } else {
    p_menu_component->set_name("Test (OFF)");
  }
}
void mu_water_enable_onSelect(MenuComponent* p_menu_component){

}
void mu_water_simulate_onSelect(MenuComponent* p_menu_component){

}

String nmi_pumpOn_format(float value) {
  char string[15];
  char string2[15];
  sprintf(string, "%5sh", dtostrf(value/60.0/60.0, 0, 1, string2));
  return String(string);
}
String nmi_pumpOff_format(float value) {
  char string[15];
  char string2[15];
  sprintf(string, "%5ss", dtostrf(value, 0, 1, string2));
  return String(string);
}

void setup() {
  Wire.begin();

  //Setup Serial for debugging
  Serial.begin(9600);
  Serial.println("Setup Serial");

  // //setup display
  // display.init();
  // display.clearDisplay();
  // display.setNormalDisplay();
  // display.setPageMode();
  // drawDisplay();
  // setup menu
  Serial.println("menu_renderer.setup_display");
  menu_renderer.setup_display();

  Menu mu_water("Water Sensor");
  ms.get_root_menu().add_menu(&mu_pump);
  ms.get_root_menu().add_menu(&mu_water);
  // NumericMenuItem(const char *name, SelectFnPtr select_fn, float value, float min_value, float max_value, optional float increment, optional FormatValueFnPtr format_value_fn)
  NumericMenuItem nmi_pumpOn("ON timer", &mu_pumpOn_onSelect, pumpOnSeconds, 60.0, 604800.0, -15.0*60.0, &nmi_pumpOn_format);
  mu_pump.add_item(&nmi_pumpOn);
  NumericMenuItem nmi_pumpOff("OFF timer", &mu_pumpOff_onSelect, pumpOffSeconds, 10.0, 3600.0, -5.0, &nmi_pumpOff_format);
  mu_pump.add_item(&nmi_pumpOff);
  MenuItem mi_pumpTest("Test", &mi_pumpTest_onSelect);
  mu_pump.add_item(&mi_pumpTest);
  // ms.display();

  //setup pump relay
  Serial.println("pump_relais.begin");
  pump_relais.begin(pumpPin);

  //setup pump bit
  Serial.println("pump_bit.begin");
  pump_bit.begin();

  Serial.println("pump_test_bit.begin");
  pump_test_bit.begin()
  .onChange(pump_test_bit_onChange);

  //setup pump start timer
  Serial.println("pumpOn_timer.begin");
  pumpOn_timer.begin()
    .interval_seconds((uint32_t)pumpOnSeconds)
    .repeat(-1)
    .onTimer(pumpOn_onTimer)
    // .onChange(pumpOn_onChange)
    .start();

  //setup pump stop timer
  Serial.println("pumpOff_timer.begin");
  pumpOff_timer.begin()
    .interval_seconds((uint32_t)pumpOffSeconds)
    .onTimer(pumpOff_onTimer);

  Serial.println("sonic_timer.begin");
  sonic_timer.begin()
    .interval_seconds((uint32_t)sonicSeconds)
    .repeat(-1)
    .onTimer(sonic_onTimer)
    .start();

  Serial.println("display_timer.begin");
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
  Serial.println("pump_controller.begin");
  pump_controller.begin()
    .IF(pump_bit)
    // .AND(water_sensor)
    .OR(pump_test_bit)
    .onChange(true, pump_controller_onTrue)
    .onChange(false, pump_controller_onFalse);

  //setup joystick
  Serial.println("joyX_comp.begin");
  joyX_comp.begin(joyXPin, 50)
    // .trace(Serial)
    .threshold(joy_threshold_list, sizeof(joy_threshold_list) )
    .onChange(true, joystick_onChange, (int)'x' )
    .onChange(false, joystick_onChange, (int)'x' );
  Serial.println("joyY_comp.begin");
  joyY_comp.begin(joyYPin, 50)
    // .trace(Serial)
    .threshold(joy_threshold_list, sizeof(joy_threshold_list) )
    .onChange(true, joystick_onChange, (int)'y' )
    .onChange(false, joystick_onChange, (int)'y' );

  // upBtn_button.begin(upBtnPin)
  //   .onPress(upBtn_onPress)
  //   .trace(Serial)
  //   .repeat();
  Serial.println("Setup done.");
  Serial.println("");
}

void loop() {
  automaton.run();
}
