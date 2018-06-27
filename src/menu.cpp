#include "menu.h"

unsigned char menuIndicator = '>';
SeeedOLED display;

void MenuRenderer::render(Menu const& menu) const {
  // display.clearDisplay();
  for (int i = 0; i < menu.get_num_components(); ++i) {
      MenuComponent const* cp_m_comp = menu.get_menu_component(i);
      display.setTextXY(i,0);
      if (cp_m_comp->is_current()) {
        display.putChar(menuIndicator);
      }
      else {
        display.putChar(' ');
      }
      display.setTextXY(i,1);
      cp_m_comp->render(*this);
  }
};

void MenuRenderer::render_menu_item(MenuItem const& menu_item) const {
  char string[15];
  sprintf(string, "%-15s", menu_item.get_name());
  display.putString(string);
};

void MenuRenderer::render_back_menu_item(BackMenuItem const& menu_item) const {
  char string[15];
  sprintf(string, "%-15s", menu_item.get_name());
  display.putString(string);
};

void MenuRenderer::render_numeric_menu_item(NumericMenuItem const& menu_item) const {
  // Serial.print(menu_item.get_name());
  // Serial.print(": ");
  // Serial.println(menu_item.get_value());
  char string[15];
  sprintf(string, "%-9s%5d", menu_item.get_name(), (int)menu_item.get_value());
  display.putString(string);
};

void MenuRenderer::render_menu(Menu const& menu) const {
  char string[15];
  sprintf(string, "%-15s", menu.get_name());
  display.putString(string);
};

void MenuRenderer::invert_display(){
  display.setInverseDisplay();
};

void MenuRenderer::normal_display(){
  display.setNormalDisplay();
};

void MenuRenderer::setup_display(){
  //setup display
  display.init();
  display.clearDisplay();
  display.setNormalDisplay();
  display.setPageMode();
}
