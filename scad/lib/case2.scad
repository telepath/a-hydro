include <arduino.scad>
include <grove.scad>
include <hinge.scad>
include <vitamins.scad>

//width
w=1.5;

x0=50;
x1=w;
y0=w+33.5;
y1=w;

x=x0+mega_x+x1+w*2;
y=y0+mega_y+y1+w*2;
z=40;

//gap
g=0.75;

a=180;

$fn=20;

assembly();
module assembly(
  x=x,
  x0=x0,
  y0=y0,
  di=w*2,
  y=y,
  z=z,
  w=w,
  g=g
) {
  yh=di/2+g+w*2;
  hinge(
    h=z/2,
    x=x,
    w=w,
    x1=w*2,
    g=g,
    di=di
  );
  translate([0, yh, 0]) {
    box_mega(
      x=x,
      y=y,
      z=z/2,
      w=w,
      di=di
    );
  }
  translate([0,-yh-y,0]){
    box_oled_joy(
      x=x,
      y=y,
      z=z/2,
      w=w,
      di=di
    );
  }
  translate([w, yh, w]) {
    inset_uno(x0=x0,y0=y0);
  }
  translate([w, -yh-y, w]) {
    inset_oled_joy(x0=x0,y0=y0);
  }
  translate([15, y+yh, 0]) {
    hook();
  }
  translate([x-15, y+yh, 0]) {
    hook();
  }
}

module hook() {
  translate([-5, 0, 0]) {
    difference() {
      hull() {
        cube(size=[10, 5, w]);
        translate([5, 5, 0]) {
          cylinder(d=10, h=w);
        }
      }
      translate([5, 5, 0]) {
        cylinder(d=5, h=w*3, center=true);
      }
    }
  }
}

module inset_mega(
  x=x,
  y=y,
  z=z,
  w=w,
  x0=x0,
  y0=y0
) {
  translate([x0, y0, 0]) {
    /* %mega(); */
    mega_holder_screw(
      w=w
    );
  }
  difference() {
    union() {
      translate([x0, 0, 0]) {
        cube(size=[w, y, z/2-w]);
      }
      translate([x0, 0, 0]) {
        cube(size=[34,y0, 7]);
      }
    }
    translate([x0, y0, 0]) {
      uno_usb();
      uno_power();
    }
    translate([x0, y0, z/4]) {
      uno_usb();
      uno_power();
    }
    translate([x0-w, 10, 5]) {
      connector();
    }
    translate([x0-w, 27, 5]) {
      connector();
    }
  }
  translate([x0+65, 15, 0]) {
    grove_module_holder(x=2);
  }
}

module inset_uno(
  x=x,
  y=y,
  z=z,
  w=w,
  x0=x0,
  y0=y0
) {
  translate([x0, y0, 0]) {
    /* %mega(); */
    uno_holder_screw(
      w=w
    );
  }
  difference() {
    union() {
      translate([x0, 0, 0]) {
        cube(size=[w, y, z/2-w]);
      }
      translate([x0, 0, 0]) {
        cube(size=[34,y0, 7]);
      }
    }
    translate([x0, y0, 0]) {
      uno_usb();
      uno_power();
    }
    translate([x0, y0, z/4]) {
      uno_usb();
      uno_power();
    }
    translate([x0-w, 10, 5]) {
      connector();
    }
    translate([x0-w, 27, 5]) {
      connector();
    }
  }
  translate([x0+65, 15, 0]) {
    grove_module_holder(x=2);
  }
  translate([x0+90, 50, 0]) {
    rotate([0, 0, 90]) {
      grove_module_holder(x=2);
    }
  }
}

module inset_touch(
  x=x,
  y=y,
  z=z,
  w=w,
  x0=x0,
  y0=y0
) {
  translate([x0+15, y-y0+15, 0]) {
    grove_module_holder(x=2);
  }
  translate([x0+65, y-y0+15, 0]) {
    grove_module_holder(x=2);
  }
  translate([x0, 0, 0]) {
    cube(size=[w, y-w, z/2-w]);
  }
}


module inset_oled_joy(
  x=x,
  y=y,
  z=z,
  w=w,
  x0=x0,
  y0=y0
) {
  translate([x0+15, y-y0+15, 0]) {
    difference() {
      /* grove_module_holder(x=2); */
      display_setup();
      /* translate([0, 0, -w-2]) {
        display_display(z=5);
      } */
    }
  }
  translate([x0+65, y-y0+15, 0]) {
    rotate([180, 0, 0]) {
      joystick_setup();
    }
  }
  translate([x0, 0, 0]) {
    cube(size=[w, y-w, z/2-w]);
  }
}

module box_mega() {
  box();
}

module box_touch_display() {
  box();
}

module box_oled_joy(
  x=x,
  x0=x0,
  y=y,
  y0=y0,
  z=z/2,
  w=w,
  g=g,
  di=w*2,
) {
  difference() {
    box(
      x=x,
      y=y,
      z=z,
      w=w,
      g=g,
      di=di
    );
    translate([x0+75+w, y-y0+15, 0]) {
      cylinder(d=12.5, h=10, center=true);
    }
    translate([x0+15+w, y-y0+15, 0]) {
      display_display(z=5);
    }
  }
}

module box(
  x=x,
  y=y,
  z=z/2,
  w=w,
  g=g,
  di=w*2
) {
    difference() {
      cube(size=[x, y, z]);
      translate([w, w, w]) {
        cube(size=[x-w*2, y-w*2, z]);
      }
    }
}
