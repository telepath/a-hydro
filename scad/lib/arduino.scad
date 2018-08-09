include <MCAD/nuts_and_bolts.scad>

mega_x=101.52;
mega_y=53.3;
mega_z=15;
uno_x=68;
uno_y=53.5;


module mega() {
  x=101.52;
  y=53.3;
  translate([x/2, y/2, 3]) {
    import("FreeCAD-library/Electrical Parts/boards/arduino-mega.stl");
  }
}

module uno() {
  translate([0, 0, 3]) {
    import("FreeCAD-library/Electrical Parts/boards/freaduino-uno.stl");
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

module uno_holder_screw(
  w=w
) {
  holes = [
    [13.8,2.5,0],
    [15,51,0],
    [66,7.65,0],
    [66,35.65,0]
  ];
  holder_screw(w=w,holes=holes);
}

module mega_holder_screw(
  w=w
) {
  holes = [
    [13.8,2.5,0],
    [15,51,0],
    [66,7.65,0],
    [66,35.65,0],
    [90.5,51,0],
    [96.6,2.5,0]
  ];
  holder_screw(w=w,holes=holes);
}

module holder_screw(
  w=w,
  holes = [
    [13.8,2.5,0],
    [15,51,0],
    [66,7.65,0],
    [66,35.65,0],
    [90.5,51,0],
    [96.6,2.5,0]
  ]
) {
  size=3;
  for (i = holes) {
    translate(i) {
      difference() {
        nutHole(size=size);
        cylinder(d=2.5, h=10, center=true);
        /* boltHole(size=size,length=10); */
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
    cube(size=[15, 15, 12]);
  }
}

/* #uno_power(); */
module uno_power() {
  translate([-2, 3.5, 4.5]) {
    cube(size=[15, 12, 12]);
  }
}
