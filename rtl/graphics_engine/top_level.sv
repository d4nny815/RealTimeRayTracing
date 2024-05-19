module top (
    input logic CLK,
    input logic RST
    );

    localparam FACES = 92;

    logic [6 : 0] face_cnt;

    Face_t face_F;

    GPU #(
        .FACES      (FACES)
    ) gpu (
        .clk        (CLK),
        .reset      (RST),

        .face       (face_F),

        .mem_addr   (face_cnt)
    );
    

    ObjectMemory #(
        .FACE_CNT   (FACES)
    ) obj_mem (
        .clk        (CLK),
        .face_cntr  (face_cnt),
        .face_data  (face_F)
    );





endmodule