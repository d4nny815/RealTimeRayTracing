module FrameBufferTB();
    logic clk_mem, clk_cpu, dram_clk;
    // initial begin
    //     clk_mem = 0; forever #2.5 clk_mem = ~clk_mem;
    // end
    // initial begin
    //     clk_cpu = 0; forever #5 clk_cpu = ~clk_cpu;
    // end
    // default clocking tb_clk @(posedge dram_clk); endclocking 



    logic [26:0] addr;
    logic [2:0] cmd;
    logic read_en, write_en, resetn;

    logic [127:0] dout;
    logic mem_rdy, mem_valid;

    FrameBuffer DUT (
        .clk        (clk_mem),
        .clk_cpu    (clk_cpu),
        .rst        (resetn),
        .addr       (addr),
        .cmd        (cmd),
        .read_en    (read_en),
        .write_en   (write_en),
        .mem_rdy    (mem_rdy),
        .mem_valid  (mem_valid),
        .dout       (dout)
    );

    // assign dram_clk = DUT.ddr2_ram.ui_clk;

    // task reset;
    //     resetn = 0; addr = 0; cmd = 0; read_en = 0; write_en = 0;
    //     @(posedge dram_clk iff !DUT.ddr2_ram.init_calib_complete);
    //     resetn = 1;
    // endtask : reset


    // task read(logic [26:0] read_addr);
    //     addr = read_addr;
    //     cmd = 3'b001;
    //     read_en = 1;
    //     @(posedge dram_clk iff !mem_rdy);
    //     read_en = 0;
    //     cmd = 0;
    //     @(posedge dram_clk iff mem_valid);
    // endtask : read

    // initial begin
    //     $display("start simulation");
    //     reset();

    //     ##(3);
    //     read(27'hbeef);
        






    //     ##(1000); 
    //     //$finish;
    // end

endmodule