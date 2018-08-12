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
        cube(size=[12, 17, 10]);
      }
    }
    translate([-6, -5, 31]) {
      cube(size=[10, 10, 7]);
    }
  }
}
