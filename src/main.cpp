#include "main.h"
#include <BlynkSimpleEsp8266.h>
// #include <BlynkSimpleEsp8266_SSL.h>

void vWrite(int pin, int value) {
  #ifdef BLYNK
  if (value != -1) {
    DEBUG(F("Write "));
    DEBUG(value);
    DEBUG(F(" to pin "));
    DEBUG(pin);
    DEBUGLN(F(""));
    Blynk.virtualWrite(pin, value);
  } else {
    DEBUG(F("Value "));
    DEBUG(value);
    DEBUG(F(" for pin "));
    DEBUG(pin);
    DEBUGLN(F(" is discarded"));
  }
  #endif
}

void vWrite(int pin, double value) {
  #ifdef BLYNK
  if (value != -1.0) {
    DEBUG(F("Write "));
    DEBUG(value);
    DEBUG(F(" to pin "));
    DEBUG(pin);
    DEBUGLN(F(""));
    Blynk.virtualWrite(pin, value);
  } else {
    DEBUG(F("Value "));
    DEBUG(value);
    DEBUG(F(" for pin "));
    DEBUG(pin);
    DEBUGLN(F(" is discarded"));
  }
  #endif
}

void vWrite(int pin, const char* value) {
  #ifdef BLYNK
  if (*value != -1) {
    DEBUG(F("Write "));
    DEBUG(value);
    DEBUG(F(" to pin "));
    DEBUG(pin);
    DEBUGLN(F(""));
    Blynk.virtualWrite(pin, value);
  } else {
    DEBUG(F("Value "));
    DEBUG(value);
    DEBUG(F(" for pin "));
    DEBUG(pin);
    DEBUGLN(F(" is discarded"));
  }
  #endif
}

void vWrite(int pin, BlynkParam &param) {
  DEBUG(F("Write "));
  DEBUG(param.asString());
  DEBUG(F(" to pin "));
  DEBUG(pin);
  DEBUGLN(F(""));
  Blynk.virtualWrite(pin, param);
}

#ifdef BLYNK
#ifndef BOARD_NODEMCU
ESP8266 wifi(&EspSerial);
#endif

BLYNK_READ_DEFAULT()
{
  int pin = request.pin;      // Which pin is handled?
  int value = -1;
  if (pin==SONIC) {
    write_tankLevel();
  }
  else if (pin==PUMP_TIME) {
    if (pump_bit.state()) {
      value = pumpOff_timer.left()/1000;
    } else {
      value = pumpOn_timer.left()/1000;
    }
  }
  else if (pin==SETTINGS_TANK_FULL) {
    value = tankFull;
  }
  else if (pin==SETTINGS_TANK_EMPTY) {
    value = tankEmpty;
  }
  else if (pin==SETTINGS_BLYNK_MILLIS) {
    value = blynkMillis;
  }
  else if (pin==SETTINGS_PUMP_ON_MIN) {
    value = pumpOnSeconds / 60;
  }
  else if (pin==SETTINGS_SONIC_SECONDS) {
    value = sonicSeconds;
  }
  else if (pin==SETTINGS_PUMP_OFF_SEC) {
    value = pumpOffSeconds;
  }
  else if (pin==PUMP_STATE) {
    value = pump_relais.state();
  }
  #ifdef ENABLE_SUNLIGHT
  else if (pin==LIGHT_IR) {
    sunlight_readIR();
  }
  else if (pin==LIGHT_VS) {
    sunlight_readVisible();
  }
  else if (pin==LIGHT_UV) {
    sunlight_readUV();
  }
  #endif //ENABLE_SUNLIGHT
  #ifdef ENABLE_MOISTURE
  else if (pin==MOISTURE) {
    value = analogRead(moisturePin);
  }
  #endif //ENABLE_MOISTURE
  if (value != -1)
    vWrite(pin, value);
}

BLYNK_WRITE_DEFAULT()
{
  int pin = request.pin;      // Which pin is handled?
  DEBUG(F("Received "));
  DEBUG(param.asString());
  DEBUG(F(" on pin "));
  DEBUG(pin);
  DEBUGLN(F(""));

  if (pin==SETTINGS_TANK_FULL) {
    tankFull = param.asInt();
    Blynk.setProperty(SONIC, "max", tankFull);
  }
  else if (pin==SETTINGS_TANK_EMPTY) {
    tankEmpty = param.asInt();
    write_tankLevel();
    Blynk.setProperty(SONIC, "min", tankEmpty);
  }
  else if (pin==SETTINGS_BLYNK_MILLIS) {
    blynkMillis = param.asInt();
    write_tankLevel();
    #ifdef BLYNK
    // blynk_timer.interval_seconds((uint32_t)blynkMillis);
    #endif
  }
  else if (pin==SETTINGS_PUMP_ON_MIN) {
    pumpOnSeconds = param.asInt() * 60.0;
    if (pumpOnSeconds <=0 ) {
      pumpOn_timer.stop();
    } else {
      pumpOn_timer.interval_seconds(pumpOnSeconds);
      if (pumpOn_timer.state() == pumpOn_timer.IDLE) {
        pumpOn_timer.start();
      }
    }
  }
  else if (pin==SETTINGS_SONIC_SECONDS) {
    sonicSeconds = param.asInt();
    #ifdef ENABLE_SONIC
    sonic_timer.interval_seconds(sonicSeconds);
    #endif
  }
  else if (pin==SETTINGS_PUMP_OFF_SEC) {
    pumpOffSeconds = param.asDouble();
    if (pumpOffSeconds <= 0 ) {
      pumpOff_timer.stop();
    } else {
      pumpOff_timer.interval_seconds(pumpOffSeconds);
      if (pumpOff_timer.state() == pumpOff_timer.IDLE) {
        pumpOff_timer.start();
      }
    }
  }
  else if (pin==PUMP_STATE) {
    if (param.asInt()==0) {
      pump_test_bit.off();
    } else {
      pump_test_bit.on();
    }
  }
  else if (pin==SETTINGS_OTA_VERSION) {
    checkUpdate();
  }
}

void disableUpdateButton(){
  Blynk.setProperty(SETTINGS_OTA_UPDATE, "color", BLYNK_WHITE);
  Blynk.setProperty(SETTINGS_OTA_UPDATE, "onBackColor", BLYNK_WHITE);
  Blynk.setProperty(SETTINGS_OTA_UPDATE, "offBackColor", BLYNK_WHITE);
}

void enableUpdateButton(){
  Blynk.setProperty(SETTINGS_OTA_UPDATE, "color", BLYNK_WHITE);
  Blynk.setProperty(SETTINGS_OTA_UPDATE, "onBackColor", BLYNK_GREEN);
  Blynk.setProperty(SETTINGS_OTA_UPDATE, "offBackColor", BLYNK_GREEN);
}

bool checkUpdate() {
  DEBUGLN(F("Checking for update"));
  HTTPClient http;
  http.begin(OTA_VERSION_URL);
  int r = http.GET();
  if ((r > 0) && (http.getString().length() > 0)) {
    pinParams[SETTINGS_OTA_VERSION] = http.getString().c_str();
    DEBUG(F("Version found: "));
    DEBUGLN(http.getString().c_str());
    // DEBUGLN(pinParams[SETTINGS_OTA_VERSION].asStr());
    // vWrite(SETTINGS_OTA_VERSION, pinParams[SETTINGS_OTA_VERSION]);
    // if (pinParams[SETTINGS_OTA_VERSION].asStr() > BOARD_FIRMWARE_VERSION ) {
    //   DEBUG(pinParams[SETTINGS_OTA_VERSION].asStr());
    //   DEBUG(F(" is newer than installed "));
    //   DEBUGLN(F(BOARD_FIRMWARE_VERSION));
    //   enableUpdateButton();
    //   return true;
    // } else {
    //   DEBUG(pinParams[SETTINGS_OTA_VERSION].asStr());
    //   DEBUG(F(" is not newer than installed "));
    //   DEBUGLN(F(BOARD_FIRMWARE_VERSION));
    //   disableUpdateButton();
    // }
  } else {
    DEBUG(F("Error checking for new version: "));
    DEBUGLN(r);
    Blynk.setProperty(SETTINGS_OTA_VERSION, "color", BLYNK_RED);
    disableUpdateButton();
  }
  return false;
}

BLYNK_WRITE(SETTINGS_OTA_UPDATE) {
  if (param.asInt() != 0 && checkUpdate()) {
    overTheAirURL = OTA_BIN_URL;
    overTheAirURL.concat("/");
    overTheAirURL.concat(pinParams[SETTINGS_OTA_VERSION].asStr());
    overTheAirURL.concat("/");
    overTheAirURL.concat(OTA_FILE_NAME);
    DEBUGLN(F("Starting OTA update from "));
    DEBUGLN(overTheAirURL);
    Blynk.setProperty(SETTINGS_OTA_UPDATE, "offBackColor", BLYNK_BLUE);

    // Disconnect, not to interfere with OTA process
    // Blynk.disconnect();

    // Start OTA
    // BlynkState::set(MODE_OTA_UPGRADE);
    DEBUGLN(F("Update would have started!"));
    delay(500);
  } else {
    Blynk.setProperty(SETTINGS_OTA_UPDATE, "offBackColor", BLYNK_RED);
  }

}

void blynk_writeConfig() {
  vWrite(SETTINGS_SONIC_SECONDS, sonicSeconds);
  vWrite(SETTINGS_BLYNK_MILLIS, blynkMillis);
  vWrite(SETTINGS_PUMP_ON_MIN, pumpOnSeconds / 60);
  vWrite(SETTINGS_PUMP_OFF_SEC, pumpOffSeconds);
  vWrite(SETTINGS_TANK_EMPTY, tankEmpty);
  vWrite(SETTINGS_TANK_FULL, tankFull);
  vWrite(PUMP_STATE, 0);
  vWrite(VERSION, BOARD_FIRMWARE_VERSION);
  vWrite(SETTINGS_OTA_VERSION, "");
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
  vWrite(PUMP_STATE,pump_relais.state());
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
  vWrite(PUMP_STATE,pump_relais.state());
  #endif
  write_tankLevel();
}

void pumpOn_onTimer(int idx, int v, int up){
  DEBUGLN(F("pumpOn_onTimer"));
  pump_bit.on();
  pumpOff_timer.start();
  #ifdef ENABLE_SONIC
  sonic_timer.interval_seconds(sonicSecondsFast);
  #endif
  #ifdef BLYNK
  Blynk.setProperty(PUMP_TIME, "label", "PumpOff");
  Blynk.setProperty(PUMP_TIME, "color", BLYNK_DARK_BLUE);
  vWrite(PUMP_TIME,pumpOffSeconds);
  #endif
}

void pumpOff_onTimer(int idx, int v, int up){
  DEBUGLN(F("pumpOff_onTimer"));
  pump_bit.off();
  #ifdef ENABLE_SONIC
  sonic_timer.interval_seconds(sonicSeconds);
  #endif
  #ifdef BLYNK
  Blynk.setProperty(PUMP_TIME, "label", "PumpOn");
  Blynk.setProperty(PUMP_TIME, "color", BLYNK_GREEN);
  vWrite(PUMP_TIME, pumpOnSeconds);
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
  vWrite(SONIC, ((double)tankEmpty - (double)cm - (double)tankFull) / ((double)tankEmpty-(double)tankFull) * 100);
  #endif
  #endif
}

void blynk_sendPump() {
  if (pumpOff_timer.state() == pumpOff_timer.IDLE) {
    DEBUG(F("pumpOn_timer.left = "));
    DEBUG(pumpOn_timer.left());
    DEBUGLN(F(""));
    #ifdef BLYNK
    Blynk.virtualWrite(PUMP_TIME, pumpOn_timer.left()/1000);
    #endif
  } else {
    DEBUG(F("pumpOff_timer.left = "));
    DEBUG(pumpOff_timer.left());
    #ifdef BLYNK
    Blynk.virtualWrite(PUMP_TIME, pumpOff_timer.left()/1000);
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
#ifdef ENABLE_SUNLIGHT
void sunlight_init_onTimer(int idx, int v, int up){
  DEBUGLN(F("sunlight_init_onTimer"));
  DEBUGLN(F("Sunlight.Begin()"));
  if (SunSensor.Begin()) {
    DEBUGLN(F("Sunlight sensor setup successful"));
    sunlight_init_timer.stop();
    sunlight_timer.start();
  }
  else {
    DEBUGLN(F("Sunlight sensor setup unsuccessful. Wait for retry."));
  }
}

void sunlight_readIR(){
  DEBUGLN(F("sunlight_readIR"));
  int value = -1;
  if (value = SunSensor.ReadIR()) {
    if (value < sunlightIRMax) {
      vWrite(LIGHT_IR, value);
    }
  } else {
    if (sunlight_init_timer.state() == sunlight_init_timer.IDLE) {
      DEBUGLN(F("reinitialize sunlight sensor"));
      sunlight_init_timer.start();
    }
  }

}
void sunlight_readVisible(){
  DEBUGLN(F("sunlight_readVisible"));
  int value = SunSensor.ReadVisible();
  if (value < sunlightVisibleMax) {
    vWrite(LIGHT_VS, value);
  }

}
void sunlight_readUV(){
  DEBUGLN(F("sunlight_readUV"));
  double value = SunSensor.ReadUV() / 100.0;
  if (value < sunlightUVMax) {
    vWrite(LIGHT_UV, value);
  }
}

void sunlight_onTimer(int idx, int v, int up){
  DEBUGLN(F("sunlight_onTimer"));
  sunlight_readIR();
  sunlight_readVisible();
  sunlight_readUV();
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
    .repeat(ATM_COUNTER_OFF)
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
    .repeat(ATM_COUNTER_OFF)
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

  #ifdef ENABLE_SUNLIGHT
  DEBUGLN(F("sunlight_init_timer.begin"));
  sunlight_init_timer.begin()
    .interval_millis(60000)
    .repeat(ATM_COUNTER_OFF)
    .onTimer(sunlight_init_onTimer)
    .start();
  sunlight_timer.begin()
    .interval_seconds(sunlightSeconds)
    .repeat(ATM_COUNTER_OFF)
    .onTimer(sunlight_onTimer);
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

  Blynk.setProperty(PUMP_TIME, "label", "PumpOn");
  Blynk.setProperty(PUMP_TIME, "color", BLYNK_GREEN);
  #endif

  // DEBUGLN(F("EasyOta.setup"));
  // EasyOta.setup();

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
