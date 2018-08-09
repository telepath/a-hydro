module grove_module_holder(x=1,y=1,flat=0,h=3) {
  difference() {
    for (i=[0:x-1]) {
      translate([20*i, 0, 0]) {
        rotate(90*i) {
          grove_module_base_holder(h=h);
        }
      }
    }
    translate([10, 0, -h]) {
      cube(size=[20*(x-1), 10*y, 3*h+20], center=true);
    }
  }
}

module grove_module_base_holder(h=3) {
  $fn=16;
  translate([-10, 0, -h+3]) {
    cylinder(r=2.25, h=h+2);
  }
  translate([10, 0, -h+3]) {
    cylinder(r=2.25, h=h+2);
  }
  translate([0, 10, -h+3]) {
    difference() {
      cylinder(r=2.5, h=h);
      translate([0, 0, h-2]) {
        cylinder(d=1.6, h=h*2, center=true);
        /* boltHole(size=2,length=h); */
      }
    }
  }
  translate([0, -10, -h+3]) {
    difference() {
      cylinder(r=2.5, h=h);
      translate([0, 0, h-2]) {
        /* cylinder(d=2, h=5, center=true); */
        boltHole(size=2,length=h);
      }
    }
  }
}

module grove_module(
          x=1,
          y=1,/* no effect yet */
          flat=0,
          pos=1
) {
  translate([0, 0, 3]) {
    for (i=[0:x-1]) {
      translate([20*i, 0, 0]) {
        rotate(90*i) {
          color("blue",0.3) {
            grove_module_base();
          }
        }
      }
    }

    translate([(20*x-10)*pos-4-flat*x*20+flat*5, 10*y/2-5, flat*4]) {
      rotate([0, 90*flat, 0]) {
        color("white",0.6) grove_con();
      }
    }
    translate([10*x/2, 10*y/2-5, 2]) {
      color("green",0.3) cube(size=[10*x, 10*y, 10], center=true);
    }
  }
}

module grove_con() {
  translate([0, 0, 4]) {
    cube(size=[5, 10, 10], center=true);
  }
}

module grove_module_base() {
  $fn=16;
  translate([-10, -10, 0]) {
    difference() {
      union() {
        cube(size=[20, 20, 1.5]);
        translate([10, 0, 0]) {
          cylinder(r=2.5, h=1.5);
        }
        translate([10, 20, 0]) {
          cylinder(r=2.5, h=1.5);
        }
      }
      translate([0, 10, 0]) {
        cylinder(r=2.5, h=10, center=true);
      }
      translate([20, 10, 0]) {
        cylinder(r=2.5, h=10, center=true);
      }
      translate([10, 0, 0]) {
        cylinder(r=1, h=10, center=true);
      }
      translate([10, 20, 0]) {
        cylinder(r=1, h=10, center=true);
      }
    }
  }
}

module joystick_cap() {
  /* translate([80, -23, 24]) {
    rotate([-45, 0, 180]) {
      translate([10, 0, 3+7.5-20]) { */
        difference() {
          union() {
            translate([0, 0, 12.5]) {
              sphere(d=12.5);
            }
            cylinder(d=12.5, h=12.5);
            cylinder(d=19, h=9);
          }
          translate([0, 0, 12.5]) {
            sphere(d=10);
          }
          cylinder(d=10, h=12.5);
          cylinder(d=20, h=8);
        }
      /* }
    }
  } */
}

module relais() {
  translate([85, 20, 0]) {
    rotate(90) {
      %grove_module(x=2,pos=0);
      grove_module_holder(x=2);
    }
  }
}

module display_display(z=2) {
  translate([11/2+10, 4/2, 2/2]) {
    cube(size=[25, 15, z],center=true);
    translate([-0.5, -4/2, 5]) {
      cube(size=[28, 20, z],center=true);
    }
  }
}

module display_setup() {
  /* translate([15, -23, 24]) {
    rotate([180+45, 0, 0]) { */
      %grove_module(x=2,flat=1); //display
      grove_module_holder(x=2,flat=1);
      color("black") {
        %display_display();
      }
    /* }
  } */
}

module joystick_setup() {
  /* translate([15, -23, 24]) {
    translate([65, 0, 0]) {
      rotate([-45, 0, 180]) { */
        translate([0, 0, -20]) {
          %grove_module(x=2,flat=0); //joystick
          translate([0, 0, 7.5]) {
            rotate([180, 0, 0]) {
              difference() {
                grove_module_holder(x=2,flat=1,h=15);
                translate([23.5, 0, 0]) {
                  cube(size=[10, 10, 30], center=true);
                }
              }
            }
            translate([10, 0, 3]) {
              %joystick_cap();
            }
          }
          %translate([10, 0, 3+7.5]) {
            /* cylinder(d=17, h=30); */
            cube(size=[15, 15, 15], center=true);
            translate([0, 0, 23/2-7.5]) {
              cube(size=[2, 2, 22], center=true);
              translate([0, 0, 2]) {
                include <../knob.scad>;
              }
            }
          }
        }
      /* }
    }
  } */
}
