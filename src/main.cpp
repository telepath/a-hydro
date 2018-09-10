#include "main.h"

#ifdef ENABLE_SONIC
Ultrasonic ultrasonic(sonicPin);
#endif

void vWrite(int pin, int value) {
  #ifdef BLYNK
  DEBUG(F("Write "));
  DEBUG(value);
  DEBUG(F(" to pin "));
  DEBUG(pin);
  DEBUGLN(F(""));
  Blynk.virtualWrite(pin, value);
  #endif
}

#ifdef BLYNK
#ifndef BOARD_NODEMCU
ESP8266 wifi(&EspSerial);
#endif

BLYNK_READ_DEFAULT()
{
  int pin = request.pin;      // Which exactly pin is handled?
  int value = 0;
  if (pin==sonicVPin) {
    write_tankLevel();
  } else if (pin==pumpOnVPin) {
    if (pump_bit.state()) {
      value = pumpOff_timer.left()/1000;
    } else {
      value = pumpOn_timer.left()/1000;
    }
  } else if (pin==tankFullVPin) {
    value = tankFull;
  } else if (pin==tankEmptyVPin) {
    value = tankEmpty;
  } else if (pin==blynkMillisVPin) {
    value = blynkMillis;
  } else if (pin==pumpOnMinutesVPin) {
    value = pumpOnSeconds / 60;
  } else if (pin==sonicSecondsVPin) {
    value = sonicSeconds;
  } else if (pin==pumpOffSecondsVPin) {
    value = pumpOffSeconds;
  } else if (pin==pumpVPin) {
    value = pump_relais.state();
  }
  vWrite(pin, value);
}

BLYNK_WRITE_DEFAULT()
{
  int pin = request.pin;      // Which exactly pin is handled?
  DEBUG(F("Received "));
  DEBUG(param.asString());
  DEBUG(F(" on pin "));
  DEBUG(pin);
  DEBUGLN(F(""));

  if (pin==tankFullVPin) {
    tankFull = param.asInt();
    Blynk.setProperty(sonicVPin, "max", tankFull);
  } else if (pin==tankEmptyVPin) {
    tankEmpty = param.asInt();
    write_tankLevel();
    Blynk.setProperty(sonicVPin, "min", tankEmpty);
  } else if (pin==blynkMillisVPin) {
    blynkMillis = param.asInt();
    write_tankLevel();
    #ifdef BLYNK
    // blynk_timer.interval_seconds((uint32_t)blynkMillis);
    #endif
  } else if (pin==pumpOnMinutesVPin) {
    pumpOnSeconds = param.asInt() * 60.0;
    pumpOn_timer.interval_seconds(pumpOnSeconds);
  } else if (pin==sonicSecondsVPin) {
    sonicSeconds = param.asInt();
    #ifdef ENABLE_SONIC
    sonic_timer.interval_seconds(sonicSeconds);
    #endif
  } else if (pin==pumpOffSecondsVPin) {
    pumpOffSeconds = param.asDouble();
    pumpOff_timer.interval_seconds(pumpOffSeconds);
  } else if (pin==pumpVPin) {
    if (param.asInt()==0) {
      pump_test_bit.off();
    } else {
      pump_test_bit.on();
    }
  }
}

void blynk_writeConfig() {
  vWrite(sonicSecondsVPin, sonicSeconds);
  vWrite(blynkMillisVPin, blynkMillis);
  vWrite(pumpOnMinutesVPin, pumpOnSeconds / 60);
  vWrite(pumpOffSecondsVPin, pumpOffSeconds);
  vWrite(tankEmptyVPin, tankEmpty);
  vWrite(tankFullVPin, tankFull);
}

BLYNK_CONNECTED() {
    Blynk.syncAll();
    blynk_writeConfig();
}
#endif

#ifdef JOY_OLED
MenuRenderer menu_renderer;
MenuSystem ms(menu_renderer);
Menu mu_pump("Pump");
#endif

void pump_test_bit_onChange(int idx, int v, int up) {
  if (pump_test_bit.state()) {
    pumpOn_timer.trigger(pumpOn_timer.EVT_STOP);
  } else {
    pumpOn_timer.trigger(pumpOn_timer.EVT_START);
  }
}

void pump_controller_onTrue(int idx, int v, int up){
  DEBUGLN(F("pump_controller_onTrue"));
  // display.setInverseDisplay();
  #ifdef JOY_OLED
  menu_renderer.invert_display();
  #endif
  // display.clearDisplay();
  pump_relais.on();
  #ifdef BLYNK
  vWrite(pumpVPin,pump_relais.state());
  #endif
  write_tankLevel();
}

void pump_controller_onFalse(int idx, int v, int up){
  DEBUGLN(F("pump_controller_onFalse"));
  // display.setNormalDisplay();
  #ifdef JOY_OLED
  menu_renderer.normal_display();
  #endif
  pump_relais.off();
  #ifdef BLYNK
  vWrite(pumpVPin,pump_relais.state());
  #endif
  write_tankLevel();
}

void pumpOn_onTimer(int idx, int v, int up){
  DEBUGLN(F("pumpOn_onTimer"));
  pump_bit.on();
  pumpOff_timer.start();
  #ifdef BLYNK
  Blynk.setProperty(pumpOnVPin, "label", "PumpOff");
  Blynk.setProperty(pumpOnVPin, "color", BLYNK_DARK_BLUE);
  vWrite(pumpOnVPin,pumpOffSeconds);
  #endif
}

void pumpOff_onTimer(int idx, int v, int up){
  DEBUGLN(F("pumpOff_onTimer"));
  pump_bit.off();
  #ifdef BLYNK
  Blynk.setProperty(pumpOnVPin, "label", "PumpOn");
  Blynk.setProperty(pumpOnVPin, "color", BLYNK_GREEN);
  vWrite(pumpOnVPin, pumpOnSeconds);
  #endif
}
#ifdef ENABLE_SONIC
void sonic_onTimer(int idx, int v, int up){
  DEBUGLN(F("sonic_onTimer"));
  write_tankLevel();
}
#endif

void write_tankLevel() {
  #ifdef BLYNK
  #ifdef ENABLE_SONIC
  int cm = ultrasonic.MeasureInCentimeters();
  DEBUG(F("measured "));
  DEBUG(cm);
  DEBUG(F(" cm"));
  DEBUGLN(F(""));
  DEBUG(F("Tank "));
  DEBUG(tankEmpty);
  DEBUG(F("/"));
  DEBUG(tankFull);
  DEBUGLN(F(""));
  vWrite(sonicVPin, ((double)tankEmpty - (double)cm - (double)tankFull) / ((double)tankEmpty-(double)tankFull) * 100);
  #endif
  #endif
}

void blynk_sendPump() {
  if (pumpOff_timer.state() == pumpOff_timer.IDLE) {
    DEBUG(F("pumpOn_timer.left = "));
    DEBUG(pumpOn_timer.left());
    DEBUGLN(F(""));
    #ifdef BLYNK
    Blynk.virtualWrite(pumpOnVPin, pumpOn_timer.left()/1000);
    #endif
  } else {
    DEBUG(F("pumpOff_timer.left = "));
    DEBUG(pumpOff_timer.left());
    #ifdef BLYNK
    Blynk.virtualWrite(pumpOnVPin, pumpOff_timer.left()/1000);
    #endif
  }
}

// #ifdef BLYNK
// void blynk_onTimer(int idx, int v, int up){
//   DEBUGLN(F("blynk_onTimer"));
// }
// #endif

#ifdef JOY_OLED
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
#endif

// void joystick_onUp(/* arguments */) {
//   DEBUGLN(F("joystick_onUp"));
//   upBtn_button.event(upBtn_button.EVT_PRESS);
// }
//
// void upBtn_onPress( int idx, int v, int up ) {
//   ms.prev(true);
// }

#ifdef JOY_OLED
void joystick_onUp(/* arguments */) {
  DEBUGLN(F("joystick_onUp"));
  ms.prev(false);
}
void joystick_onDown(/* arguments */) {
  DEBUGLN(F("joystick_onDown"));
  ms.next(false);
}
void joystick_onLeft(/* arguments */) {
  DEBUGLN(F("joystick_onLeft"));
  ms.back();
}
void joystick_onRight(/* arguments */) {
  DEBUGLN(F("joystick_onRight"));
  ms.select();
}
void joystick_onPush(/* arguments */) {
  DEBUGLN(F("joystick_onPush"));
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
#endif

void setup() {
  Wire.begin();

  //Setup Serial for debugging
  // #ifndef BLYNK
  #ifdef SERIAL_DEBUG
  Serial.begin(115200);
  DEBUGLN(F("Setup Serial"));
  #endif
  // #endif
  #ifdef BLYNK
  #ifndef BOARD_NODEMCU
  // Set ESP8266 baud rate
  DEBUGLN(F("Setup EspSerial"));
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
  #endif

  // DEBUGLN(F("Blynk.begin"));
  // #ifndef BOARD_NODEMCU
  // Blynk.begin(auth, wifi, ssid, pass);
  // #endif //BOARD_NODEMCU
  // #ifdef BOARD_NODEMCU
  // Blynk.begin(auth, ssid, pass);
  // #endif //BOARD_NODEMCU
  #endif

  #ifdef JOY_OLED
  //setup display
  DEBUGLN(F("menu_renderer.setup_display"));
  menu_renderer.setup_display();

  ms.get_root_menu().add_menu(&mu_pump);
  #ifdef ENABLE_SONIC
  Menu mu_water("Water Sensor");
  ms.get_root_menu().add_menu(&mu_water);
  #endif
  // NumericMenuItem(const char *name, SelectFnPtr select_fn, float value, float min_value, float max_value, optional float increment, optional FormatValueFnPtr format_value_fn)
  NumericMenuItem nmi_pumpOn("ON timer", &mu_pumpOn_onSelect, pumpOnSeconds, 60.0, 604800.0, -15.0*60.0, &nmi_pumpOn_format);
  mu_pump.add_item(&nmi_pumpOn);
  NumericMenuItem nmi_pumpOff("OFF timer", &mu_pumpOff_onSelect, pumpOffSeconds, 10.0, 3600.0, -5.0, &nmi_pumpOff_format);
  mu_pump.add_item(&nmi_pumpOff);
  MenuItem mi_pumpTest("Test", &mi_pumpTest_onSelect);
  mu_pump.add_item(&mi_pumpTest);
  // ms.display();
  #endif

  //setup pump relay
  DEBUGLN(F("pump_relais.begin"));
  pump_relais.begin()
  .led(pumpPin); 

  //setup pump bit
  DEBUGLN(F("pump_bit.begin"));
  pump_bit.begin();

  DEBUGLN(F("pump_test_bit.begin"));
  pump_test_bit.begin()
  .onChange(pump_test_bit_onChange);

  //setup pump start timer
  DEBUGLN(F("pumpOn_timer.begin"));
  pumpOn_timer.begin()
    .interval_seconds((uint32_t)pumpOnSeconds)
    .repeat(-1)
    .onTimer(pumpOn_onTimer)
    // .onChange(pumpOn_onChange)
    .start();

  //setup pump stop timer
  DEBUGLN(F("pumpOff_timer.begin"));
  pumpOff_timer.begin()
    .interval_seconds((uint32_t)pumpOffSeconds)
    .onTimer(pumpOff_onTimer);
  #ifdef ENABLE_SONIC
  DEBUGLN(F("sonic_timer.begin"));
  sonic_timer.begin()
    .interval_seconds((uint32_t)sonicSeconds)
    .repeat(-1)
    .onTimer(sonic_onTimer)
    .start();
  #endif

// #ifdef BLYNK
//   DEBUGLN(F("blynk_timer.begin"));
//   blynk_timer.begin()
//     .interval_millis((uint32_t)blynkMillis)
//     .repeat(-1)
//     .onTimer(blynk_onTimer)
//     // .start()
//     ;
// #endif
  #ifdef JOY_OLED
  DEBUGLN(F("display_timer.begin"));
  display_timer.begin()
    .interval_millis(displayUpdate)
    .repeat(ATM_COUNTER_OFF)
    .onTimer(display_onTimer)
    .start();
  #endif

  //setup water sensor
  // water_sensor.begin(waterPin);
  // water_sensor.begin(waterPin,waterTimeout,true,true).trace(Serial);
  // water_sensor.begin(A0).trace(Serial);

  //setup pump safety
  DEBUGLN(F("pump_controller.begin"));
  pump_controller.begin()
    .IF(pump_bit)
    // .AND(water_sensor)
    .OR(pump_test_bit)
    .onChange(true, pump_controller_onTrue)
    .onChange(false, pump_controller_onFalse);

  #ifdef JOY_OLED
  //setup joystick
  DEBUGLN(F("joyX_comp.begin"));
  joyX_comp.begin(joyXPin, 50)
    // .trace(Serial)
    .threshold(joy_threshold_list, sizeof(joy_threshold_list) )
    .onChange(true, joystick_onChange, (int)'x' )
    .onChange(false, joystick_onChange, (int)'x' );
  DEBUGLN(F("joyY_comp.begin"));
  joyY_comp.begin(joyYPin, 50)
    // .trace(Serial)
    .threshold(joy_threshold_list, sizeof(joy_threshold_list) )
    .onChange(true, joystick_onChange, (int)'y' )
    .onChange(false, joystick_onChange, (int)'y' );
  #endif

  #ifdef BLYNK
  DEBUGLN(F("Start Blynk Provisioning"));
  BlynkProvisioning.begin();

  Blynk.setProperty(pumpOnVPin, "label", "PumpOn");
  Blynk.setProperty(pumpOnVPin, "color", BLYNK_GREEN);
  #endif

  // upBtn_button.begin(upBtnPin)
  //   .onPress(upBtn_onPress)
  //   .trace(Serial)
  //   .repeat();
  DEBUGLN(F("Setup done."));
  DEBUGLN(F(""));
}

void loop() {
  #ifdef BLYNK
  BlynkProvisioning.run();
  #endif
  automaton.run();
}
