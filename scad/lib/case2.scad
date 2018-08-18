include <arduino.scad>
include <grove.scad>
include <hinge.scad>
include <vitamins.scad>
include <conf/config.scad>

//width
w=1.5;

x0=47;
x1=w;
y0=w+35;
y1=w;

x=x0+mega_x+x1+w*2;
y=y0+mega_y+y1+w*2;
z=40;

//gap
g=0.75;

a=0;

board=MEGA;
inset=TOUCH_DISPLAY;

grid_x=25;
grid_y=17.5;

$fn=20;

/* assembly(); */
module assembly(
  x=x,
  x0=x0,
  y0=y0,
  di=w*2,
  y=y,
  z=z,
  w=w,
  g=g,
  a=a
) {
  yh=di/2+g+w*2;
  t=w/2;
  th=4;
  font="Liberation Sans:style=Bold";
  translate([w*2, yh+w*2, w])
  rotate(90)
   {
    linear_extrude(t) {
      text(str(board,"/",inset,"/",MAT), size=th, font=font, valign="top");
      translate([0, -th*2, 0]) {
        text(str(SRC," ",VER), size=th, font=font, valign="top");
      }
    }
  }
  hinge(
    h=z/2,
    x=x,
    w=w,
    x1=w*2,
    g=g,
    di=di,
    a=a
  );
  translate([0, yh, 0]) {
    union() {
      if (board==MEGA) {
        box_mega(
          x=x,
          y=y,
          z=(z-w)/2,
          w=w,
          di=di
        );
      }
      if (board==UNO) {
        box_uno(
          x=x,
          y=y,
          z=(z-w)/2,
          w=w,
          di=di
        );
      }
    }
    translate([x/10, yh+y, w*2+g]) {
      latch(x=x/10,di=w*2,w=w,g=g,a=a/2);
    }
    translate([x*0.9, yh+y, w*2+g]) {
      latch(x=x/10,di=w*2,w=w,g=g,a=a/2);
    }
   }
  translate([0,0,z/2]){
    rotate([a-180, 0, 0]) {
      translate([0,-yh-y,-z/2]){
        if (inset==OLED_JOY) {
          box_oled_joy(
            x=x,
            y=y,
            z=(z-w)/2,
            w=w,
            di=di
          );
        }
        if (inset==TOUCH_DISPLAY) {
          box_touch_display(
            x=x,
            y=y,
            z=(z-w)/2,
            w=w,
            di=di
          );
        }
      }
      translate([w, -yh-y, w-z/2]) {
        if (inset==OLED_JOY) {
          inset_oled_joy(x=x,y=y,z=z-w,x0=x0,y0=y0);
        }
        if (inset==TOUCH_DISPLAY) {
          inset_touch_display(x=x,y=y,z=z-w,x0=x0,y0=y0);
        }
      }
    }
  }
  translate([w, yh, w]) {
    if (board==MEGA) {
      inset_mega(x=x,y=y,z=z-w,x0=x0,y0=y0);
    }
    if (board==UNO) {
      inset_uno(x=x,y=y,z=z-w,x0=x0,y0=y0);
    }
  }
  hooks(x=x,y=y+yh,w=w);
  translate([0, yh, 0]) {
    %seal();
  }
}

module seal(
  x=x,
  x0=x0,
  y=y,
  y0=y0,
  z=z,
  w=w,
  g=g
) {
  di=w*2;
  difference() {
    translate([-w/2, -w/2, z/2-w*2]) {
      difference() {
        cube(size=[x+w, y+w, w*4]);
        translate([w*2, w*2, -w]) {
          cube(size=[x-w*3, y-w*3, w*6]);
        }
        rounded_border();
      }
    }
    box_mega(
      x=x,
      x0=x0,
      y=y,
      y0=y0,
      z=z/2,
      w=w,
      g=g,
      di=di
    );
    translate([w, 0, w]) {
      if (board==MEGA) {
        inset_mega(x=x,y=y,z=z-w,x0=x0,y0=y0);
      }
      if (board==UNO) {
        inset_uno(x=x,y=y,z=z-w,x0=x0,y0=y0);
      }
    }
  }
}

module rounded_border() {
  translate([w, 0, w*4]) {
    rotate([-90, 0, 0]) {
      clip_border(w=w,l=y,d=w*2.5);
    }
  }
  translate([0, w, w*4]) {
    rotate([0, 90, 0]) {
      rotate(90) {
        clip_border(w=w,l=x,d=w*2.5);
      }
    }
  }
  translate([x, y+w, w*4]) {
    rotate([90, 0, 0]) {
      rotate(180) {
        clip_border(w=w,l=y,d=w*2.5);
      }
    }
  }
  translate([x+w, y, w*4]) {
    rotate([0, -90, 0]) {
      rotate(270) {
        clip_border(w=w,l=x,d=w*2.5);
      }
    }
  }
}

module clip_border(
  w=w,
  d=w*2.5,
  l
) {
  difference() {
    cylinder(d=w*2.5, h=l+w);
    translate([-w, 0, 0]) {
      rotate([0, 45, 0]) {
        translate([0, -w*2.5, -w*5]) {
          cube(size=[w*10, w*10, w*10]);
        }
      }
    }
    translate([-w*1.25, 0, l+w*1.25]) {
      rotate([0, -45, 0]) {
        translate([0, -w*2.5, -w*5]) {
          cube(size=[w*10, w*10, w*10]);
        }
      }
    }
  }
}

module latch(
  x=x/10,
  di=w*2,
  w=w,
  g=g,
  a=a/2
) {
  b=di+w+g;
  c=x+(w+g)*2;
  do=di+(g+w)*2;
  e=do+w+di+w;

  //latch hinge
  rotate([0, 90, 0]) {
    cylinder(d=di, h=c, center=true);
  }
  difference() {
    union() {
      translate([0, -b/2, 0]) {
        cube(size=[c, b, do], center=true);
      }
        rotate([0, 90, 0]) {
          cylinder(d=do, h=c, center=true);
        }
    }
    translate([0, 0, 0]) {
      cube(size=[x+g*2, do*2, do+w], center=true);
    }
  }

  // latch
  /* rotate([-a*0.95, 0, 0]) */
  rotate([-a*0.08, 0, 0])
  intersection() {
    difference() {
      union() {
        rotate([0, 90, 0]) {
          cylinder(d=do, h=x, center=true);
        }
        translate([-x/2, -do/2, 0]) {
          cube(size=[x, do+w, z-w]);
        }
        translate([-x/2, -e+do/2, z-do/2+g]) {
          cube(size=[x, e, do]);
        }
        latch_catch(
          di=di,
          x=x,
          y=-e+do/2+w,
          z=z-do/2+w-g/2
        );
      }
      rotate([0, 90, 0]) {
        cylinder(d=di+g*2, h=c, center=true);
      }
      //rounding
      translate([0, -do/2-w, z/2]) {
        resize([x+g, do+di+w, z-do+di]) {
          rotate([0, 90, 0]) {
            cylinder(r=10, h=x+g, center=true, $fn=64);
          }
        }
      }
    }
    translate([0, -do+w, z/2-do]) {
      resize([x+g, do*3, z+do*2]) {
        rotate([0, 90, 0]) {
          cylinder(r=10, h=x+g, center=true, $fn=64);
        }
      }
    }
  }
}

module latch_catch(
  di=w*2,
  x=x,
  y,//=-e+do/2+w,
  z,//=z-do/2+w-g/2
) {
  translate([0, y, z]) {
    rotate([0, 90, 0]) {
      cylinder(d=di, h=x, center=true);
    }
  }
}

module hooks(x=x,y=y,w=w) {
  translate([x*0.2, y, 0]) {
    hook(w=w);
  }
  translate([x*0.8, y, 0]) {
    hook(w=w);
  }
}
module hook(w=w) {
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

module inset_A(
  x=x,
  y=y,
  z=z,
  w=w,
  x0=x0,
  y0=y0
) {
  difference() {
    union() {
      inset_grid(
        x=x,
        y=y,
        z=z,
        w=w,
        x0=x0,
        y0=y0
      );
      translate([x0, 0, 0]) {
        cube(size=[w, y, z/2-w]);
      }
      translate([x0, 0, 0]) {
        cube(size=[34.5,34.5, 7]);
      }
    }
    translate([x0+w, floor(y0)-1, 0]) {
      cube(size=[uno_x, ceil(uno_y)+1, z]);
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
      translate([0, -5, 0]) {
        cube(size=[w*3, 10, z/2]);
      }
    }
    translate([x0-w, 27, 5]) {
      connector();
      translate([0, -5, 0]) {
        cube(size=[w*3, 10, z/2]);
      }
    }
  }
}

module inset_grid(
  x=x,
  y=y,
  z=z,
  w=w,
  x0=x0,
  y0=y0
) {
  translate([x0+grid_x, grid_y, 0]) {
    grove_module_holder(x=4,y=4);
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
  inset_A(
    x=x,
    y=y,
    z=z,
    w=w,
    x0=x0,
    y0=y0
  );
  translate([x0+3, y0, 0]) {
    /* %mega(); */
    mega_holder_screw(
      w=w,
      h=3
    );
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
  inset_A(
    x=x,
    y=y,
    z=z,
    w=w,
    x0=x0,
    y0=y0
  );
  translate([x0+3, y0, 0]) {
    %uno();
    %uno_usb();
    uno_holder_screw(
      w=w
    );
  }
  translate([x0+90, 50, 0]) {
    rotate([0, 0, 90]) {
      grove_module_holder(x=2);
    }
  }
}

module inset_touch_display(
  x=x,
  y=y,
  z=z,
  w=w,
  x0=x0,
  y0=y0
) {
  inset_grid(
    x=x,
    y=y,
    z=z,
    w=w,
    x0=x0,
    y0=y0
  );
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
  difference() {
    union() {
      difference() {
        union() {
          inset_grid(
            x=x,
            y=y,
            z=z,
            w=w,
            x0=x0,
            y0=y0
          );
        }
        translate([x0+grid_x+50, grid_y+60, 0]) {
          joystick_cutout();
        }
      }
      translate([x0+grid_x+50+10, grid_y+60, -w]) {
        rotate([180, 0, 0]) {
          rotate([0, 0, 180]) {
            joystick_setup();
          }
        }
      }
    }
    translate([x0+grid_x, grid_y+60, 0]) {
      display_display(z=5);
    }
  }
  translate([x0+grid_x, grid_y+60, 0]) {
    display_setup();
  }
  translate([x0, 0, 0]) {
    cube(size=[w, y-w, z/2-w]);
  }
}

module box_mega(
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
      di=di,
      latch=0
    );
    cutout(y=y/2,z=z,w=w);
  }
}

module box_uno(
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
      di=di,
      latch=0
    );
    cutout(y=y/2,z=z,w=w);
  }
}

module box_touch_display(
  x=x,
  x0=x0,
  y=y,
  y0=y0,
  z=z/2,
  w=w,
  g=g,
  di=w*2
) {
  box(
    x=x,
    y=y,
    z=z,
    w=w,
    g=g,
    di=di,
    latch=1
  );
}

module box_oled_joy(
  x=x,
  x0=x0,
  y=y,
  y0=y0,
  z=z/2,
  w=w,
  g=g,
  di=w*2
) {
  difference() {
    box(
      x=x,
      y=y,
      z=z,
      w=w,
      g=g,
      di=di,
      latch=1
    );
    translate([x0+grid_x+50+w, grid_y+60, 0]) {
      joystick_cutout();
    }
    translate([x0+grid_x+w, grid_y+60, 0]) {
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
  di=w*2,
  latch=0
) {
  difference() {
    cube(size=[x, y, z]);
    translate([w, w, w]) {
      cube(size=[x-w*2, y-w*2, z]);
    }
    if (latch>0) {
      translate([x*0.1, 0, 0]) {
        latch_catch(
          di=w*2,
          x=x/10+w,
          y=w*2,//=-e+do/2+w,
          z=-w+g//=z-do/2+w-g/2
        );
      }
      translate([x*0.9, 0, 0]) {
        latch_catch(
          di=w*2,
          x=x/10+w,
          y=w*2,//=-e+do/2+w,
          z=-w+g//=z-do/2+w-g/2
        );
      }
    }
  }
}

module cutout(
  w=w,
  y=y/2,
  z=z
) {
  translate([-w, w, w*3]) {
    cube(size=[w*3, y, z]);
  }
}
