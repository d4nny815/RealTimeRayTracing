// File: VGATiming.sv

// This module is responsible for generating the timing signals for the VGA display.
// The VGA display has a resolution of 1024 x 768 @ 70 Hz
module VGATiming (
    input clk_75MHz,
    output logic hsync_n,
    output logic vsync_n,
    output logic in_display_area,
    output logic [9:0] hcount,
    output logic [9:0] vcount
    );

    localparam H_VISIBLE_AREA = 1024;
    localparam H_FRONT_PORCH = 24;
    localparam HSYNC_PULSE = 136;
    localparam H_BACK_PORCH = 144;
    localparam HSYNC_LINE = 1328;

    localparam V_VISIBLE_AREA = 768;
    localparam V_FRONT_PORCH = 3;
    localparam VSYNC_PULSE = 6;
    localparam V_BACK_PORCH = 29;
    localparam VSYNC_LINE = 806;

    logic [10:0] htiming;
    logic [9:0] vtiming;
    logic v_clk;

    // Horizontal counter
    always_ff @(posedge clk_75MHz ) begin
        if (htiming < HSYNC_LINE - 1) begin
            htiming <= htiming + 1;
            v_clk <= 0;
        end else begin
            htiming <= 0;
            v_clk <= 1;
        end
    end

    // Vertical counter
    always_ff @(posedge v_clk) begin
        if (vtiming < VSYNC_LINE - 1) begin
            vtiming <= vtiming + 1;
        end else begin
            vtiming <= 0;
        end
    end

    always_comb begin
        hsync_n = ~((htiming >= H_VISIBLE_AREA + H_FRONT_PORCH) && ( htiming < H_VISIBLE_AREA + H_FRONT_PORCH + HSYNC_PULSE));
        vsync_n = ~((vtiming >= V_VISIBLE_AREA + V_FRONT_PORCH) && ( vtiming < V_VISIBLE_AREA + V_FRONT_PORCH + VSYNC_PULSE));
        hcount = htiming[9:0];
        vcount = vtiming[9:0];
        in_display_area = (htiming <= H_VISIBLE_AREA - 1) && (vtiming <= V_VISIBLE_AREA - 1);
    end

endmodule