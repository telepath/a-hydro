include <conf/config.scad>
use <lib/Write.scad/Write.scad>

d1=5;
d2=10;

$fn=16;
rotate([0,180,0]){
  difference() {
    knob(d1=d1,d2=d2);
    difference() {
      writesphere(text=MAT,where=[0,0,d2],radius=d2/2-0.5);
      translate([0, 0, +1]) {
        knob(d1=d1-1,d2=d2-1);
      }
    }
  }
}

module knob(
  d1=5,
  d2=10
) {
  difference() {
    hull() {
      translate([0, 0, d1]) {
        sphere(d=d1);
      }
      translate([0, 0, d2]) {
        sphere(d=d2);
      }
    }
    cube(size=[2, 1.25, d1+d2], center=true);
    cube(size=[d2,d2,4], center=true);
  }
}
