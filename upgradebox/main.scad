module step0_fill() {
    union() {
        import("rpi_hat.stl", convexity = 5);
        translate([50, 92, 0]) cube([36, 45, 2]);

    }
   
}

module step1_add_switch() {
    difference () {
       step0_fill();
       translate([61, 90, 0]) cylinder(h = 3, r = 8);
       translate([61, 120, 0]) cube([30, 20, 5], center = true);
        
    }

}

//step1_add_switch();

module step2_add_oled() {
    step1_add_switch();
}

union() {
    step2_add_oled();
    translate([0, 22, 0]) import("oled_hat.stl", convexity = 5);
}
