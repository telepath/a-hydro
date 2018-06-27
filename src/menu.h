#ifndef MENU_H
#define MENU_H

#include <MenuSystem.h>
#include <SeeedOLED.h>

class MenuRenderer : public MenuComponentRenderer {
    void render(Menu const& menu) const;

    void render_menu_item(MenuItem const& menu_item) const;

    void render_back_menu_item(BackMenuItem const& menu_item) const;

    void render_numeric_menu_item(NumericMenuItem const& menu_item) const;

    void render_menu(Menu const& menu) const;

  public:
    void invert_display();

    void normal_display();

    void setup_display();
};

#endif
