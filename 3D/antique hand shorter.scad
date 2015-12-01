union() {
  translate([0, 0, 2])
  linear_extrude(height = 2) import("body shorter with holes.dxf", convexity=20);
  
  difference() {
    linear_extrude(height = 2) import("base.dxf");
    translate([0, 0, -0.1]) linear_extrude(height = 2.2) import("arm.dxf");
  }
}