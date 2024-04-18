module RayTracer (
    input SYSCLK,
    input BTNU, 
    // input BTNC, BTNL, BTNR, BTND,  
    // input [15:0] SW,
    // output logic [15:0] LED,
    output logic [3:0] VGA_R,
    output logic [3:0] VGA_G,
    output logic [3:0] VGA_B,
    output logic VGA_HS,
    output logic VGA_VS 
    );
    logic RESET_BTN = BTNU;

    // Clock generation
    logic clk_75MHz, locked, reset;
    clk_wiz_0 clock_wizard (
        .clk_75MHz      (clk_75MHz), 
        .reset          (reset), // input reset 
        .locked         (locked),    
        .clk_in1        (SYSCLK)     
    );
    

    logic [11:0] pixel_data;
    logic [9:0] h_pixel, v_pixel;
    DisplayModule display_module (
        .clk_75MHz      (clk_75MHz),
        .pixel_data     (pixel_data), 
        .VGA_HS         (VGA_HS), 
        .VGA_VS         (VGA_VS),
        .VGA_R          (VGA_R),
        .VGA_G          (VGA_G),
        .VGA_B          (VGA_B),
        .h_pixel        (h_pixel),
        .v_pixel        (v_pixel)
    );

    FrameBuffer frame_buffer (
        .clk            (clk_75MHz),
        .pixel_addr_RTU (),
        .pixel_data_RTU (),
        .we_RTU         (),
        .pixel_addr_DISP({h_pixel[9:1], v_pixel[9:1]}),
        .re_DISP        (1'b1),
        .pixel_data_DISP(pixel_data)
    );

    typedef enum logic {
        INIT,
        RUNNING
    } state_t;
    state_t state, next_state;

    always_ff @ (posedge SYSCLK or posedge RESET_BTN) begin
        if (RESET_BTN) begin
            state <= INIT;
        end else begin
            state <= next_state;
        end
    end

    always_comb begin
        reset = 0;
        next_state = state;
        case (state)
            INIT: begin
                next_state = RUNNING;
                reset = 1;
            end
            RUNNING: begin
                if (RESET_BTN) begin
                    next_state = INIT;
                end
            end
        default: next_state = INIT;
        endcase
    end
endmodule