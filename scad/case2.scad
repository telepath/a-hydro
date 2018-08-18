include <lib/case2.scad>

board=UNI;
inset=OLED_JOY;

a=180;

translate([y+20,0,0])
rotate(90)
  assembly();
