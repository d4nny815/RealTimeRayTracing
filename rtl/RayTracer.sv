typedef struct packed {
    logic [1:0] header;
    logic [7:0] vpixel;
    logic [7:0] hpixel;
    logic [11:0] color;
} Packet_t;


module RayTracer (
    input SYSCLK,
    input BTNU, 
    input sclk_pmod,
    input mosi,
    input cs_n,
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
    logic clk_75MHz, clk_100MHz, locked, reset;
    clk_wiz_0 clock_wizard (
        .clk_75MHz      (clk_75MHz),     // output clk_75MHz
        .reset          (reset), // input reset
        .locked         (locked),       // output locked
        .clk_in1        (SYSCLK)      // input clk_in1
    );

    logic fb_we;
    logic empty, rd_en;
    logic [1:0] packet_type;
   
    Packet_t frame;
    
    RayTracerController ray_tracing_controller (
        .clk            (clk_75MHz),
        .itf_packet_type(packet_type),
        .itf_empty      (empty),
        .fb_we          (fb_we),
        .fifo_re        (rd_en)
    );
   
    
    logic [31:0] dout;
    SPIInterface spi_interface (
        .sclk_pmod      (sclk_pmod),
        .cs_n           (cs_n),
        .mosi           (mosi),
        .miso           (),
        .rd_clk         (clk_75MHz),
        .rd_en          (rd_en),
        .dout           (dout),
        .empty          (empty),
        .packet_type    (packet_type)
    );

    assign frame.vpixel = dout[31:24];
    assign frame.hpixel = dout[23:16];
    assign frame.color = {dout[3:0], dout[15:12], dout[11:8]}; 


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

    logic [7:0] v_pix, h_pix;
    assign v_pix = v_pixel[9:2] + 1;
    assign h_pix = h_pixel[9:2] + 1;
    
    FrameBuffer frame_buffer (
        .clk            (clk_75MHz),
        .pixel_addr_RTU ({frame.hpixel, frame.vpixel}),
        .pixel_data_RTU (frame.color),
        .we_RTU         (fb_we),
        .pixel_addr_DISP({h_pix, v_pix}),
        .re_DISP        (1'b1),
        .pixel_data_DISP(pixel_data)
    );

   ila_1 RAY_TRACER_ILA (
	    .clk            (clk_75MHz), // input wire clk
	    .probe0         (cs_n), // input wire [0:0]  probe0  
	    .probe1         (fifo_re), // input wire [0:0]  probe1 
	    .probe2         (fb_we), // input wire [0:0]  probe2 
	    .probe3         (packet_type), // input wire [1:0]  probe3 
	    .probe4         (frame), // input wire [27:0]  probe4 
	    .probe5         (dout), // input wire [31:0]  probe5
        .probe6         (empty),
        .probe7         (spi_interface.data_reg)
   );
 

    typedef enum logic {
        INIT,
        RUNNING
    } state_t;
    state_t state, next_state;

    always_ff @ (posedge SYSCLK) begin
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