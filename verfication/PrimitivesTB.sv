import Primitives::*;  


module PrimitiveTB();
    Vertex_t Result;
    Vertex_t Point;
    Vector_t Col1, Col2, Col3;

    Matrix_t M;

    TransformModule UUT (
        .Point  (Point),
        .M      (M),
        .Result (Result)
    );

    logic [15:0] op1, op2, res;



    initial begin
        Point.x = 16'h00c0; // 0.75
        Point.y = 16'h0a80; // 10.5
        Point.z = 16'hfee0; // -1.125

        Col1.i = 16'h0020; // 0.125
        Col1.j = 0;
        Col1.k = 0;

        Col2.i = 0;
        Col2.j = 16'h00e0; // 0.875
        Col2.k = 0;

        Col3.i = 0;
        Col3.j = 0;
        Col3.k = 16'h0080; // 0.5

        M.v1 = Col1;
        M.v2 = Col2;
        M.v3 = Col3;


        op1 = 16'h0160; // 1.375
        op2 = 16'h0420; // 4.125
        q8_8_mult(op1, op2, res);
        #5;
        assert (res == 16'h05ac) else $fatal("op1: %h, op2: %h, res: %h", op1, op2, res);


        op1 = 16'hfea0; // -1.25
        op2 = 16'h02c0; // 2.75
        q8_8_mult(op1, op2, res);
        #5;
        assert (res == 16'hfc38) else $fatal("op1: %h, op2: %h, res: %h", op1, op2, res);


        op1 = 16'hfe80; // -1.5
        op2 = 16'hfd40; // -2.75
        q8_8_mult(op1, op2, res);
        #5;
        assert (res == 16'h0420) else $fatal("op1: %h, op2: %h, res: %h", op1, op2, res);


        op1 = 16'h01e0; // 1.875
        op2 = 16'hfd80; // -2.5
        q8_8_mult(op1, op2, res);
        #5;
        assert (res == 16'hfb50) else $fatal("op1: %h, op2: %h, res: %h", op1, op2, res);


        #1;
        $display("Resultx: %f, Resulty: %f, Resultz: %f", Result.x, Result.y, Result.z);

        #10;
        $finish;
    end

endmodule