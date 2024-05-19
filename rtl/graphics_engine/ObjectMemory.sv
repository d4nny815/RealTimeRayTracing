import Primitives::*;

module ObjectMemory #(
    parameter FACE_CNT = 92
    ) (
    input clk,
    input logic [$clog2(FACE_CNT) - 1 : 0] face_cntr,

    output Face_t face_data
    );

    // Memory
//    (* rom_style="{distributed | block}" *)
//    (* ram_decomp = "power" *) 
    Face_t faces [0 : FACE_CNT - 1];

    initial begin
        $readmemh("obj3.mem", faces, 0, FACE_CNT - 1);
    end

    always_ff @( posedge clk ) begin 
        face_data <= faces[face_cntr];
    end


endmodule