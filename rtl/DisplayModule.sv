// DisplayModule module definition
// This module is responsible for generating the timing signals for the VGA display.
// The VGA display has a resolution of 1024 x 768 @ 70 Hz
module DisplayModule(
    input logic clk_75MHz,
    input logic [11:0] pixel_data,
    output logic VGA_HS,
    output logic VGA_VS,
    output logic [3:0] VGA_R,
    output logic [3:0] VGA_G,
    output logic [3:0] VGA_B,
    output logic [9:0] h_pixel, 
    output logic [9:0] v_pixel
    );

    logic in_disp_area;
    VGATiming vga_timing (
        .clk_75MHz      (clk_75MHz),
        .hsync_n        (VGA_HS),
        .vsync_n        (VGA_VS),
        .in_display_area(in_disp_area),
        .hcount         (h_pixel),
        .vcount         (v_pixel)
    );

    always_comb begin
        VGA_R = in_disp_area ? pixel_data[11:8] : 4'h0;
        VGA_G = in_disp_area ? pixel_data[7:4] : 4'h0;
        VGA_B = in_disp_area ? pixel_data[3:0] : 4'h0;
    end

endmodule