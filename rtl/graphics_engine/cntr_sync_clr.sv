module Counter #(
    parameter BITS = 8
    ) (
    input logic clk,
    input logic reset,
    input logic ld,
    input logic up,

    input logic [BITS - 1 : 0] data_in,

    output logic [BITS - 1 : 0] count
    );

    always_ff @(posedge clk) begin
        if (reset) begin
            count <= 0;
        end else if (ld) begin
            count <= data_in;
        end else if (up) begin
            count <= count + 1;
        end
    end


endmodule