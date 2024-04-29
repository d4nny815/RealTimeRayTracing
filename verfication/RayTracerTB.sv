
module RayTracerTB();
    logic clk;
    initial begin
        clk = 0; forever #5 clk = ~clk; end

    logic sclk;
    initial begin
        sclk = 0; forever #50 sclk = ~sclk; end

     default clocking cb @(posedge clk); endclocking

    localparam SPI_BITS_PER_WORD = 8;
    logic [7:0] header;
    logic [7:0] frame [0: 4 - 1]; 
    logic mosi, cs_n;
    RayTracer DUT (
        .SYSCLK     (clk),
        .BTNU       (),
        .sclk_pmod  (sclk),
        .mosi       (mosi),
        .cs_n       (cs_n),
        // .BTNC       (),
        // .BTNL(),
        // .BTNR(),
        // .BTND(),
        // .SW(),
        // .LED(),
        .VGA_R      (),
        .VGA_G      (),
        .VGA_B      (),
        .VGA_HS     (),
        .VGA_VS     ()
    );

    task send_init();
        header = 8'h00;
        for (int i=0; i<SPI_BITS_PER_WORD; i++) begin
            @(posedge sclk);
            cs_n = 0;
            mosi = header[7 - i];
        end

    endtask : send_init
    
    task send_frame(logic [7:0] frame_i [0:3]);
        cs_n = 0;
        header = 8'h01;
        // frame = '{8'd0, 8'd0, 8'd15, 8'd15};
        frame = frame_i;
        for (int i=0; i<SPI_BITS_PER_WORD; i++) begin
            @(posedge sclk);
            mosi = header[7 - i];
        end
        @(posedge sclk);
        @(posedge sclk);

        cs_n = 0;
        for (int i=0; i<4; i++) begin
            for (int j=0; j<SPI_BITS_PER_WORD; j++) begin
                @(posedge sclk);
                mosi = frame[i][7 - j];
            end
        end

        @(posedge sclk);
        cs_n = 1;
        $display("done sending frame");
    endtask

    initial begin
        cs_n = 1; mosi = 0; sclk = 0;
        @(posedge clk iff DUT.locked);
        
//        $display("sending frame");
//        for (int i=0; i<10; i++)
//            send_frame('{i[7:0], 8'd0, 8'd15, 8'd15});
            
    end

endmodule