// import Primitives::*;

// module DotProd (
//     input Vertex_t Point, 
//     input Vector_t Col,
//     output Vertex_t Result
//     );

//     logic [31:0] x, y, z;

//     always_comb begin
//         x = Point.x * Col.i + Point.y * Col.j + Point.z * Col.k;
//         y = Point.x * Col.i + Point.y * Col.j + Point.z * Col.k;
//         z = Point.x * Col.i + Point.y * Col.j + Point.z * Col.k;
//         Result.x = x[31:16];
//         Result.y = y[31:16];
//         Result.z = z[31:16];
        

//         // Result.x = Point.x * Col.i + Point.y * Col.j + Point.z * Col.k;
//         // Result.y = Point.x * Col.i + Point.y * Col.j + Point.z * Col.k;
//         // Result.z = Point.x * Col.i + Point.y * Col.j + Point.z * Col.k;
//     end

// endmodule