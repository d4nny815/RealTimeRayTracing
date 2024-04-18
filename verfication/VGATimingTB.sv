module VGATimingTB();
    logic clk_75MHz;
    logic hsync;
    logic vsync;
    logic [9:0] hcount;
    logic [9:0] vcount;

    initial begin
        clk_75MHz = 0;
        forever #6 clk_75MHz = ~clk_75MHz;
    end

    VGATiming vga_timing (
        .clk_75MHz      (clk_75MHz),
        .hsync_n        (hsync),
        .vsync_n        (vsync),
        .hcount         (hcount),
        .vcount         (vcount)
    );

    initial begin
        $display("start simulation");
        $monitor("hsync=%b, vsync=%b, hcount=%d, vcount=%d", hsync, vsync, hcount, vcount);
    end
endmodule