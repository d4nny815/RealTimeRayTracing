



module SPIInterface (
    input logic sclk_pmod,
    input logic mosi,
    input logic cs_n,
    output logic miso,


    input rd_clk,
    input rd_en,
    output logic [31:0] dout,
    output logic empty,
    output logic [1:0] packet_type
    );

    localparam BYTE_SIZE = 8;
    localparam HEADER_SIZE = 1 * BYTE_SIZE;
    localparam FRAME_SIZE = 4 * BYTE_SIZE;
    localparam POLYGON_SIZE = 50 * BYTE_SIZE;
    localparam CAMERA_SIZE = 12 * BYTE_SIZE;
//    localparam FIFO_DEPTH = 16;
    localparam FIFO_WIDTH = 32;
    
//    Packet_t packet;
    
    logic sclk;
    assign sclk = sclk_pmod;
 
    logic [$clog2(FIFO_WIDTH): 0] data_cntr;

    logic clr, header_we, data_we, fifo_we, counter_eq, data_reg_rdy, cntr_up, cntr_clr;
    logic [1:0] cntr_sel;
   
    //  ila_0 SPI_SIGS_ILA (
	//      .clk                (rd_clk), // input wire clk
	//      .probe0             (cs_n), // input wire [0:0]  probe0  
	//      .probe1             (sclk_pmod), // input wire [0:0]  probe1 
	//      .probe2             (mosi), // input wire [0:0]  probe2 
	//      .probe3             (fifo_we), // input wire [0:0]  probe3 
	//      .probe4             (counter_eq), // input wire [0:0]  probe4 
	//      .probe5             (header_reg), // input wire [7:0]  probe5 
	//      .probe6             (data_reg), // input wire [31:0]  probe6 
	//      .probe7             (counter), // input wire [9:0]  probe7 
	//      .probe8             (spi_controller.state), // input wire [2:0]  probe8 
	//      .probe9             (spi_controller.next_state), // input wire [2:0]  probe9 
	//      .probe10            (packet_type) // input wire [1:0]  probe10
    //  );

    // * Controller
    SPIController spi_controller (
        .clk                (~sclk),
        .cs_n               (cs_n),
        .packet_type        (header_reg[1:0]),
        .counter_eq         (counter_eq),
        .data_reg_rdy       (data_cntr == FIFO_WIDTH + 2),
        .clr                (clr),
        .header_we          (header_we),
        .data_we            (data_we),
        .fifo_we            (),
        .cntr_clr           (cntr_clr),
        .cntr_up            (cntr_up),
        .cntr_sel           (cntr_sel)
    );


    // * Header Shift Register
    logic [HEADER_SIZE - 1 : 0] header_reg;
    always_ff @(posedge sclk) begin
        if (header_we) begin
            header_reg <= {header_reg[HEADER_SIZE - 2: 0], mosi};
        end
    end
    assign packet_type = data_we ? header_reg[1:0] : 2'd0;


    // * Data Shift Register
    logic [FIFO_WIDTH - 1: 0] data_reg;
    
    always_ff @(negedge sclk) begin
        if (clr) begin
            data_reg <= 0;
            data_cntr <= 0;
        end
        else if (fifo_we) begin
            data_reg <= {data_reg[FIFO_WIDTH - 2: 0], mosi};
            data_cntr <= 0;
        end 
        else if (data_we) begin
            data_reg <= {data_reg[FIFO_WIDTH - 2: 0], mosi};
            data_cntr <= data_cntr + 1;
        end
    end


    // * Bit Counter
    logic [$clog2(HEADER_SIZE + POLYGON_SIZE) - 1: 0] counter;
    always_ff @(posedge sclk) begin
        if (cntr_clr) begin
            counter <= 0;
        end else if (cntr_up) begin
            counter <= counter + 1;
        end
    end

    always_comb begin
        case (cntr_sel)
            2'b00: counter_eq = (counter == HEADER_SIZE - 2);
            2'b01: counter_eq = (counter == FRAME_SIZE);
            2'b10: counter_eq = (counter == POLYGON_SIZE - 1);
            2'b11: counter_eq = (counter == CAMERA_SIZE - 1);
            default: counter_eq = 0;
        endcase
    end

    assign fifo_we = counter_eq && spi_controller.state == spi_controller.DATA;

    logic fifo_rst;
    ResetController resetFIFO (
        .clk        (rd_clk),
        .rst        (fifo_rst)
    );

    // * Async FIFO
    async_fifo fifo (
        .rst            (fifo_rst),        // input wire rst
        .wr_clk         (~sclk),         // input wire wr_clk
        .rd_clk         (rd_clk),         // input wire rd_clk
        .din            (data_reg),        // input wire [30 : 0] din
        .wr_en          (fifo_we),    // input wire wr_en
        .rd_en          (rd_en),    // input wire rd_en
        .dout           (dout),      // output wire [30 : 0] dout
        .full           (),      // output wire full
        .empty          (empty)    // output wire empty
    );
   

endmodule