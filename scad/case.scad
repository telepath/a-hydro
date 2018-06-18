w=1.5;
x=102;
x1=30;
y=90;
y1=55;
z1=15;
z2=20;

z=z1+z2;

uno_x=68;
uno_y=53.5;
uno_z=30;

/* %uno();
%shield(); */

demo(a=45);

/* box();
lid1(); */
/* box2();
box3(); */

/* grove_module(x=2,flat=1); */
/* display_display(); */
/* %grove_module(x=2);
grove_module_holder(x=2); */

/* !joystick_setup(); */

module demo(a=0) {
  translate([0, y-y1-2+w/2, -z1+w]) {
    %uno();
    %shield();
    box();
  }
  rotate([a, 0, 0]) {
    translate([0, y-y1-2+w/2, -z1+w]) {
      lid1();
    }
  }
}

module lid1() {
  box2();
  box3();
}

module hinge1() {
  difference() {
    hinge();
    translate([((x+x1)/2+w)/2-x1-w, -y1, 0]) {
      cube(size=[(x+x1)/2+w, y*2, z*2]);
    }
  }
}

module hinge2() {
  intersection() {
    hinge();
    translate([((x+x1)/2-w)/2-x1+w/2, -y1, 0]) {
      cube(size=[(x+x1)/2, y*2, z*2]);
    }
  }
}

module hinge(d=2) {
  $fn=16;
  translate([-x1-w, y1-y+w, z1-w]) {
    rotate([0, 90, 0]) {
      difference() {
        cylinder(d=d*2, h=x+x1);
        cylinder(d=d, h=x+x1+2);
      }
    }
  }
}

module hinge_inner(d=2) {
  $fn=16;
  translate([-x1-w-1, y1-y+w, z1-w]) {
    rotate([0, 90, 0]) {
      cylinder(d=d, h=x+x1+2);
    }
  }
}

module box3() {
  difference() {
    translate([-x1-w, 0, z1-w]) {
      cube(size=[x+x1, y1, z2]);
    }
    translate([-x1, -w, z1-w*2]) {
      cube(size=[x+x1-w*2, y1, z2]);
    }
    uno_usb();
    uno_power();
  }
}

module box2() {
  difference() {
    union() {
      difference() {
        block2();
        translate([w, w, -w]) {
          block2(x=x-w*2);
        }
        hinge();
      }
      display_setup();
    }
    translate([15, -23, 24]) {
      rotate([180+45, 0, 0]) {
        display_display(z=10);
      }
    }
    translate([80, -23, 24]) {
      rotate([-45, 0, 180]) {
        translate([10, 0, 3+7.5-20]) {
          cylinder(d=15, h=30);
          cylinder(d=19, h=9);
        }
      }
    }
    hinge_inner();
  }
  joystick_setup();
  hinge2();
}

module block2(x=x,y=y-y1,z=z2) {
  translate([-x1-w, -y, 12+w]) {
    difference() {
      cube(size=[x+x1, y, z]);
      translate([-w, 0, 0]) {
        rotate([45, 0, 0]) {
          cube(size=[x+x1+w*2, y, y]);
        }
      }
    }
  }
}

module connector() {
  rotate([0, 90, 0]) {
    translate([0, 0, -2]) {
      cylinder(r=3.5, h=10);
    }
    cylinder(r=5, h=10);
    hull() {
      translate([-5, -5.5, 10]) {
        cube(size=[10, 11, 17]);
      }
      translate([-12/2, -17/2, 22]) {
        cube(size=[12, 17, 9]);
      }
    }
    translate([-6, -5, 31]) {
      cube(size=[10, 10, 5]);
    }
  }
}

module box(x=x,y=y,z=z1) {
  $fn=16;
  difference() {
    union() {
      translate([-x1-w, -y+y1, -w]) {
        difference() {
          cube(size=[x+x1, y, z]);
          translate([w, w, w]) {
            cube(size=[x+x1-w*2, y-w*2, z]);
          }
        }
      }
      translate([0, -35, 0]) {
        cube(size=[35, 34.5, 6]);
      }
    }
    uno_usb();
    uno_power();
    translate([0, -8, 6]) {
      connector();
    }
    translate([0, -25, 6]) {
      connector();
    }
    hinge();
    hinge_inner();
  }
  /* hull() {
    translate([60, -4, 0]) {
      cylinder(r=2, h=17);
    }
    translate([80, -4, 0]) {
      cylinder(r=2, h=17);
    }
    translate([60, -18, 0]) {
      cylinder(r=2, h=2.9);
    }
    translate([80, -18, 0]) {
      cylinder(r=2, h=2.9);
    }
    translate([50, -11, 0]) {
      cylinder(r=2, h=9.7);
    }
    translate([90, -11, 0]) {
      cylinder(r=2, h=9.7);
    }
  } */
  relais();
  translate([0, -8, 6]) {
    %connector();
  }
  translate([0, -25, 6]) {
    %connector();
  }
  uno_holder(x=uno_x,y=uno_y,z=uno_z,z1=z1-w);
  hinge1();
}

module relais() {
  translate([85, 40, 0]) {
    rotate(-90) {
      %grove_module(x=2);
      grove_module_holder(x=2);
    }
  }
}

module display_display(z=2) {
  translate([11/2+10, 4/2, 2/2]) {
    cube(size=[25, 15, z],center=true);
  }
}

module display_setup() {
  translate([15, -23, 24]) {
    rotate([180+45, 0, 0]) {
      %grove_module(x=2,flat=1); //display
      grove_module_holder(x=2,flat=1);
      color("black") {
        %display_display();
      }
    }
  }
}

module joystick_setup() {
  translate([15, -23, 24]) {
    translate([65, 0, 0]) {
      rotate([-45, 0, 180]) {
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
          }
          %translate([10, 0, 3+7.5]) {
            /* cylinder(d=17, h=30); */
            cube(size=[15, 15, 15], center=true);
            translate([0, 0, 23/2-7.5]) {
              cube(size=[2, 2, 22], center=true);
            }
          }
        }
      }
    }
  }
}

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
      cube(size=[20*(x-1), 10*y, 3*h], center=true);
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
        cylinder(d=1, h=5, center=true);
      }
    }
  }
  translate([0, -10, -h+3]) {
    difference() {
      cylinder(r=2.5, h=h);
      translate([0, 0, h-2]) {
        cylinder(d=1, h=5, center=true);
      }
    }
  }
}

module grove_module(
          x=1,
          y=1,/* no effect yet */
          flat=0
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

    translate([20*x-10-4-flat*x*20+flat*5, 10*y/2-5, flat*4]) {
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

module uno() {
  translate([0, 0, 3]) {
    rotate([90,0,0]) {
      scale(10) {
        import("Final.stl");
      }
    }
  }
}

module shield() {
  translate([34, 26, 13]) {
    rotate([90,0,90+180]) {
      scale(1) {
        import("Grove_shield_Uno.stl");
      }
    }
  }
}

module uno_holder(
  x=68,
  y=53.5,
  z=30,
  z1=0
) {
  pin1=[14,2.5,0];
  pin2=[15,51,0];
  pin3=[66,7.5,0];
  pin4=[66,35.5,0];
  r=1.25;
  h=20;

  translate(pin1) {
    cylinder(r=r, h=h/2);
  }
  translate(pin2) {
    cylinder(r=r, h=h);
  }
  translate(pin3) {
    cylinder(r=r, h=h);
  }
  translate(pin4) {
    cylinder(r=r, h=h);
  }
  difference() {
    translate([-w, -w, -w]) {
      cube(size=[w, y+w*2, z1+w]);
    }
    uno_usb();
    uno_power();
  }
}

/* #uno_usb(); */
module uno_usb() {
  translate([-5, 31.5, 4.5]) {
    cube(size=[15, 13, 12]);
  }
}

/* #uno_power(); */
module uno_power() {
  translate([-2, 3.5, 4.5]) {
    cube(size=[15, 10, 12]);
  }
}
