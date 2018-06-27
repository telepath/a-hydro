
d1=5;
d2=10;

$fn=16;

difference() {
  hull() {
    translate([0, 0, d1]) {
      sphere(d=d2);
    }
    translate([0, 0, d2]) {
      sphere(d=d1);
    }
  }
  cube(size=[2.5, 1.5, 12], center=true);
  cube(size=[d2,d2,4], center=true);
}
