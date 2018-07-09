
d1=5;
d2=10;

$fn=16;
rotate([180,0,0])
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
