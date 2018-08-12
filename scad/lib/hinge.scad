
module hinge(
  h=z/2,
  x=x,
  z=z,
  x1=w*2,
  w=w,
  g=g,
  di=w*2,
  a=a
) {
  x11=(x1+g);
  x2=x11*2;
  n=floor(x/x2)-2;
  xn=(n+1)*x2+x1;
  /* intersection() {
    translate([0, -(di/2+g+w*3), 0]) {
      cube(size=[x, di+g*2+w*6, h+di+w+g]);
    } */
    translate([(x-xn)/2, 0, h]) {
      rotate([0, 90, 0]) rotate(-45) {
        for (i=[0:n]) {
          translate([0, 0, x2*i]) {
            hinge_element(x=x1,z=z,di=w*2,w=w,g=g,a=a);
          }
        }
        translate([0, 0, (n+1)*x2]) {
          hinge_element3(x=x1,z=z,di=w*2,w=w,g=g);
        }
      }
    }
  /* } */
}

/* hinge_element1(); */
module hinge_element1(
  x=w*2,
  z=z,
  di=w*2,
  w=w,
  g=g
) {
  xo=di+w*6+g*2;
  intersection() {
    rotate(45) cube(size=[z, xo, di*2], center=true);
    union() {
      cylinder(d=di+g*2+w*2, h=x);
      cube(size=[di/2+g+w, di*5, x]);
      cylinder(d=di, h=x*2+g*2);
    }
  }
}

module hinge_filter(z=z,xo=xo,di=di) {
  intersection() {
    rotate(45) cube(size=[z, xo, di*2], center=true);
    union() {
      children();
    }
  }
}

/* translate([0,0,x+g]) */
  /* !hinge_element2(); */
module hinge_element2(
  x=w*2,
  z=z,
  di=w*2,
  w=w,
  g=g,
  a=a
) {
  xo=di+w*6+g*2;
  rotate([0, 0, a+90]) {
    intersection() {
      rotate(-45) cube(size=[z, xo, di*2], center=true);
      union() {
        difference() {
          cylinder(d=di+g*2+w*2, h=x);
          cylinder(d=di+g*2, h=x*2, center=true);
        }
        translate([-(di/2+g+w), 0, 0]) {
          cube(size=[di/2+g+w, di*5, x]);
        }
      }
    }
  }
}

module hinge_leg(
  x=di/2+g+w,
  x1=x1
) {
  translate([-x, 0, 0]) {
    cube(size=[x, x1*5, x1]);
  }
}

module hinge_element3(
  x=w*2,
  z=z,
  di=w*2,
  w=w,
  g=g
) {
  xo=di+w*6+g*2;
  intersection() {
    rotate(45) cube(size=[z, xo, di*2], center=true);
    union() {
      cylinder(d=di+g*2+w*2, h=x);
      translate([0, 0, 0]) {
        cube(size=[di/2+g+w, di*4, x]);
      }
    }
  }
}
/* hinge_element(); */
module hinge_element(
  x=w*2,
  z=z,
  di=w*2,
  w=w,
  g=g,
  a=a
) {
  hinge_element1(x=x,di=di,w=w,g=g);
  translate([0, 0, x+g]) {
    hinge_element2(x=x,di=di,w=w,g=g,a=a);
  }
}
