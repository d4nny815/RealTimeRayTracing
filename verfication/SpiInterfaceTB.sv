module SPIInterfaceTB();
    logic clk;
    initial begin
        clk = 0;
        forever #40 clk = ~clk;
    end
    default clocking cb @(posedge clk); endclocking
    
    logic rd_clk;
    initial begin
        rd_clk = 0;
        forever #5 rd_clk = ~rd_clk;
    end

    int SPI_BITS_PER_WORD = 8;
    logic cs_n;
    logic mosi;

    logic [31:0] dout;
    logic rd_en;
    
    logic [7:0] header;
    logic [7:0] frame [0: 4 - 1] = '{8'd0, 8'd0, 8'd15, 8'd15};
    
    SPIInterface DUT (
        .sclk      (clk),
        .cs_n      (cs_n),
        .mosi      (mosi),
        .miso      (),
        .rd_clk    (rd_clk),
        .rd_en     (rd_en),
        .dout      (dout),
        .empty     ()
    );

    task send_wren(); 
        logic [7:0] ack = 8'h06;
        for (int i=0; i<SPI_BITS_PER_WORD; i++) begin
            @(posedge clk);
            cs_n = 0;
            mosi = ack[7 - i];
        end
        @(negedge clk);
        assert (DUT.ack_reg == 8'd6) else $fatal("ack mismatch");
    endtask : send_wren

    task send_init();
        send_wren();
        header = 8'h00;
        for (int i=0; i<SPI_BITS_PER_WORD; i++) begin
            @(posedge clk);
            cs_n = 0;
            mosi = header[7 - i];
        end

    endtask : send_init
    
    task send_frame();
        send_wren();
        cs_n = 0;
        header = 8'h01;
        for (int i=0; i<SPI_BITS_PER_WORD; i++) begin
            @(posedge clk);
            mosi = header[7 - i];
        end
        ##(2);
        assert (DUT.header_reg == header) else $fatal("header mismatch");

        cs_n = 0;
        for (int i=0; i<4; i++) begin
            for (int j=0; j<SPI_BITS_PER_WORD; j++) begin
                @(posedge clk);
                mosi = frame[i][7 - j];
            end
        end

        @(posedge clk);
        cs_n = 1;
    endtask

    task read_spi();
        for (int i=0; i<10; i++) begin
            rd_en = 1;
            @(negedge rd_clk);
            assert (dout == 32'hf0f) else $fatal("dout mismatch");
        end

        @(posedge rd_clk);
        rd_en = 0;
    endtask


    initial begin
        cs_n = 1; mosi = 0; rd_en = 0;
        ##(10);
        for (int i=0; i<10; i++) begin
               send_frame();
        end

        read_spi();

        ##(10);
        $finish;
    end


endmodule