include <lib/case2.scad>

board=UNO;
inset=OLED_JOY;

translate([y+20,0,0])
rotate(90)
  assembly();
