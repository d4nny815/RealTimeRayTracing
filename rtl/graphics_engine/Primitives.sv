package Primitives;


typedef struct packed {
    logic [15:0] x;  // 16b fixed point, 8b signed integer, 8b fraction
    logic [15:0] y;  // 16b fixed point, 8b signed integer, 8b fraction
    logic [15:0] z;  // 16b fixed point, 8b signed integer, 8b fraction 
} Vertex_t;

typedef struct packed {
    logic [15:0] i;  // 16b fixed point, 8b signed integer, 8b fraction
    logic [15:0] j;  // 16b fixed point, 8b signed integer, 8b fraction
    logic [15:0] k;  // 16b fixed point, 8b signed integer, 8b fraction
} Vector_t;

typedef struct packed {
    Vertex_t v1;
    Vertex_t v2;
    Vertex_t v3;
    Vector_t normal;
    logic [11:0] color;
} Face_t;

typedef struct packed {
    Vector_t v1; // column 1
    Vector_t v2; // column 2
    Vector_t v3; // column 3
} Matrix_t;


localparam FACES_BITS = $bits(Face_t);

endpackage : Primitives

import Primitives::*;


task q8_8_mult(
    input logic [15:0] a,
    input logic [15:0] b,
    output logic [15:0] result
    );

    logic [31:0] tmp;
    logic sign_a, sign_b, res_sign;
    logic [15:0] op1, op2;


    sign_a = a[15];
    sign_b = b[15];

    case ({sign_a, sign_b})
        2'b00: begin
            op1 = a;
            op2 = b;
        end
        2'b10: begin
            op1 = -a;
            op2 = b;
        end 
        2'b01: begin
            op1 = a;
            op2 = -b;
        end
        2'b11: begin
            op1 = -a;
            op2 = -b;
        end
    endcase

    tmp = op1 * op2;

    case ({sign_a, sign_b})
        2'b00: result = tmp[23:8];
        2'b10: result = -tmp[23:8];
        2'b01: result = -tmp[23:8];
        2'b11: result = tmp[23:8];
    endcase
    
endtask : q8_8_mult


module DotProduct (
    input Vertex_t Point, 
    input Vector_t Col,
    output logic [15:0] Result
    );

    logic [15:0] x, y, z;

    always_comb begin
        q8_8_mult(Point.x, Col.i, x);
        q8_8_mult(Point.y, Col.j, y);
        q8_8_mult(Point.z, Col.k, z);
    
        Result = x + y + z;
    end



endmodule





