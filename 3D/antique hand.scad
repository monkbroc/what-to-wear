union() {
  translate([0, 0, 2])
  difference() {
    linear_extrude(height = 2) import("body.dxf", convexity=20);
    translate([0, 0, -0.1]) linear_extrude(height = 2.2) import("hole1.dxf");
    translate([0, 0, -0.1]) linear_extrude(height = 2.2) import("hole2.dxf");
    translate([0, 0, -0.1]) linear_extrude(height = 2.2) import("hole3.dxf");
  }
  difference() {
    linear_extrude(height = 2) import("base.dxf");
    translate([0, 0, -0.1]) linear_extrude(height = 2.2) import("arm.dxf");
  }
}