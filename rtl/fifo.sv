module Fifo #(
    parameter DEPTH = 16,
    parameter WIDTH = 32
    ) (
    input rst,

    input wr_clk,
    input wr_en,
    input [WIDTH - 1: 0] wr_data,
    output logic almost_full,
    output logic full,

    
    input rd_clk,
    input rd_en,
    output logic [WIDTH - 1:0] rd_data,
    output logic almost_empty,
    output logic empty
    );

    localparam ALMOST_THRESHOLD = DEPTH * 3 / 4;

    logic [$clog2(DEPTH)-1:0] rd_ptr, wr_ptr;
    logic [WIDTH-1:0] queue [0:DEPTH-1];

    always_comb begin
        rd_data = queue[rd_ptr];
        empty = (rd_ptr == wr_ptr);
        almost_empty = (rd_ptr == wr_ptr - ALMOST_THRESHOLD);
        full = (rd_ptr == wr_ptr - 1);
        almost_full = (rd_ptr == wr_ptr - DEPTH + ALMOST_THRESHOLD);


    end

    always_ff @(posedge wr_clk or posedge rst) begin
        if (rst) begin
            wr_ptr <= 0;
            for (int i=0; i<DEPTH; i++)
                queue[i] <= 0;
        end

        if (wr_en && !full) begin
            queue[wr_ptr] <= wr_data;
            wr_ptr <= wr_ptr + 1;
        end
    end

    always_ff @(posedge rd_clk or posedge rst) begin
        if (rst) begin
            rd_ptr <= 0;
        end

        if (rd_en && !empty) begin
            rd_ptr <= rd_ptr + 1;
        end
    end



endmodule