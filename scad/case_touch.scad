include <lib/case2.scad>

board=MEGA;
inset=TOUCH_DISPLAY;

translate([y+20,0,0])
rotate(90)
  assembly();
