// FrameBuffer module
// This module is responsible for storing the pixel data for the VGA display.
// The VGA display has a resolution of 512 x 384 with 12-bit color depth.
module FrameBuffer(
    input clk,
    input [15:0] pixel_addr_RTU,
    input [11:0] pixel_data_RTU,
    input we_RTU,

    input [15:0] pixel_addr_DISP,
    input re_DISP,

    output logic [11:0] pixel_data_DISP
    );
    
    localparam V_PIXELS = 192;
    localparam H_PIXELS = 256;
    localparam MEM_SIZE = 2 ** ($clog2(V_PIXELS) + $clog2(H_PIXELS));

    (* rom_style="{distributed | block}" *)
    (* ram_decomp = "power" *) logic [11:0] frame [0:MEM_SIZE - 1];
    initial
        $readmemh("start_frame.mem", frame, 0, MEM_SIZE - 1); 

    always_ff @ (negedge clk) begin
        if (we_RTU) begin
            frame[pixel_addr_RTU] <= pixel_data_RTU;
        end
        if (re_DISP) begin
            pixel_data_DISP <= frame[pixel_addr_DISP];
        end
    end

    // always_comb begin
    //     pixel_data_DISP = re_DISP ? frame[pixel_addr_DISP] : 12'd0;
    // end
 

    // ! If I want to learn how to use to DRAM
    // mig_7series_0 ddr2_ram (
    //     // ! DONT TOUCH 
    //     // Memory interface ports
    //     .ddr2_addr                      (ddr2_addr),        // output [12:0]    ddr2_addr
    //     .ddr2_ba                        (ddr2_ba),          // output [2:0]     ddr2_ba
    //     .ddr2_cas_n                     (ddr2_cas_n),       // output           ddr2_cas_n
    //     .ddr2_ck_n                      (ddr2_ck_n),        // output [0:0]     ddr2_ck_n
    //     .ddr2_ck_p                      (ddr2_ck_p),        // output [0:0]     ddr2_ck_p
    //     .ddr2_cke                       (ddr2_cke),         // output [0:0]     ddr2_cke
    //     .ddr2_ras_n                     (ddr2_ras_n),       // output           ddr2_ras_n
    //     .ddr2_we_n                      (ddr2_we_n),        // output           ddr2_we_n
    //     .ddr2_dq                        (ddr2_dq),          // inout [15:0]     ddr2_dq
    //     .ddr2_dqs_n                     (ddr2_dqs_n),       // inout [1:0]      ddr2_dqs_n
    //     .ddr2_dqs_p                     (ddr2_dqs_p),       // inout [1:0]      ddr2_dqs_p
    //     .init_calib_complete            (init_calib_complete),  // output       init_calib_complete

	//     .ddr2_cs_n                      (ddr2_cs_n),        // output [0:0]     ddr2_cs_n
    //     .ddr2_dm                        (ddr2_dm),          // output [1:0]     ddr2_dm
    //     .ddr2_odt                       (ddr2_odt),         // output [0:0]     ddr2_odt
        
    //     // * use these below
    //     // Application interface ports
    //     .app_addr                       (addr), 
    //     .app_cmd                        (cmd),          // input [2:0]      app_cmd 001-read, 000-write
    //     .app_en                         (read_en),           // input            app_en
    //     .app_wdf_data                   (0),        // input [127:0]    app_wdf_data
    //     .app_wdf_end                    (0),      // input            app_wdf_end
    //     .app_wdf_wren                   (write_en),     // input            app_wdf_wren
    //     .app_rd_data                    (dout),      // output [127:0]   app_rd_data
    //     .app_rd_data_end                (),  // output           app_rd_data_end
    //     .app_rd_data_valid              (mem_valid),// output           app_rd_data_valid
    //     .app_rdy                        (mem_rdy),          // output           app_rdy
    //     .app_wdf_rdy                    (),      // output           app_wdf_rdy
    //     .app_sr_req                     (0),       // input            app_sr_req
    //     .app_ref_req                    (0),      // input            app_ref_req
    //     .app_zq_req                     (0),       // input            app_zq_req
    //     .app_sr_active                  (),    // output           app_sr_active
    //     .app_ref_ack                    (),      // output           app_ref_ack
    //     .app_zq_ack                     (),       // output           app_zq_ack
    //     .ui_clk                         (),           // output           ui_clk
    //     .ui_clk_sync_rst                (),  // output           ui_clk_sync_rst

    //     .app_wdf_mask                   (0),     // input [15:0]  app_wdf_mask
      
    //     // System Clock Ports
    //     .sys_clk_i                      (clk),
    //     // Reference Clock Ports
    //     .clk_ref_i                      (clk_cpu),
    //     .sys_rst                        (rst)           // input  sys_rst
    // );

endmodule