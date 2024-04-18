module RayTracerTB();
    logic clk;

    initial begin
        clk = 0;
        forever #5 clk = ~clk;
    end
    // default clocking cb @(posedge clk); endclocking

    RayTracer DUT (
        .SYSCLK(clk),
        .BTNC(),
        .BTNU(),
        .BTNL(),
        .BTNR(),
        .BTND(),
        .SW(),
        .LED(),
        .VGA_R(),
        .VGA_G(),
        .VGA_B(),
        .VGA_HS(),
        .VGA_VS()
    );

    initial begin
        @(posedge clk iff DUT.locked);
        while (1) begin
            @(posedge clk);
            // assert (DUT.display_module.h_pixel / 4 == DUT.frame_buffer.h_pixel) else $fatal("h_pixel mismatch");
            // assert (DUT.display_module.v_pixel / 4 == DUT.frame_buffer.v_pixel) else $fatal("v_pixel mismatch");
        end
    end

endmodule