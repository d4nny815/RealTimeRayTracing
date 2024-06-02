import Primitives::*;

module GPU #(
    parameter FACES = 92 
    ) (
    input logic clk,
    input logic reset,

    input Face_t face,

    output logic [$clog2(FACES) - 1 : 0] mem_addr

    );

    localparam FACE_CNT_BITS = $clog2(FACES);


    // ! for debug
    logic [FACE_CNT_BITS-1:0] face_num_T, face_num_L, face_num_P;

    Face_t face_L, face_lighting, face_P, face_projection;


    // ##################################################
    // * FETCH STAGE
    // ##################################################
    Counter #(
        .BITS(FACE_CNT_BITS)
    ) face_cntr (
        .clk(clk),
        .reset(reset || mem_addr == (FACES - 1)),
        .ld(1'b0),
        .up(1'b1),
        .data_in(7'd0),
        .count(mem_addr)
    );

    // // ##################################################
    // // * TRANSFORM STAGE
    // // ##################################################

    // always_ff @(posedge clk) begin
    //     face_num_T <= mem_addr;
    // end

    // Face_t face_transform;

    // Vector_t Col1, Col2, Col3;
    // Matrix_t M;
    // always_comb begin
    //     Col1.i = 16'h0020; // 0.125
    //     Col1.j = 0;
    //     Col1.k = 0;

    //     Col2.i = 0;
    //     Col2.j = 16'h00e0; // 0.875
    //     Col2.k = 0;

    //     Col3.i = 0;
    //     Col3.j = 0;
    //     Col3.k = 16'h0080; // 0.5

    //     M.v1 = Col1;
    //     M.v2 = Col2;
    //     M.v3 = Col3;
    // end


    // TransformFaceModule transformation (
    //     .face_i     (face),
    //     .M          (M),
    //     .face_o     (face_transform)
    // );

    // ##################################################
    // * LIGHTING STAGE
    // ##################################################

    always_ff @(posedge clk) begin
        face_num_L <= mem_addr;
    end

    assign face_L = face;
    Vector_t LIGHTING;

    always_comb begin
        LIGHTING = 48'h0076008b00b2;
    end

    LightingModule lighting (
        .face_i     (face_L),
        .light      (LIGHTING),
        .face_o     (face_lighting)
    );

    // ##################################################
    // * PROJECTION STAGE
    // ##################################################
    always_ff @(posedge clk) begin
        face_num_P <= face_num_L;
        face_P <= face_lighting;
    end

    localparam SCREEN_WIDTH = 255;
    localparam SCREEN_HEIGHT = 192;
    localparam SCREEN_DEPTH = 255;

    ProjectionModule projection (
        .face_i         (face_P),
        .screen_width   (SCREEN_WIDTH),
        .screen_height  (SCREEN_HEIGHT),
        .screen_depth   (SCREEN_DEPTH),
        .face_o         (face_projection)
    );



endmodule