import Primitives::*;

// task get_normal(Vertex_t v1, Vertex_t v2, Vertex_t v3, output Vector_t normal);
//     Vector_t v1v2, v1v3;
//     Vector_t cross_product;

//     v1v2.i = v2.x - v1.x;
//     v1v2.j = v2.y - v1.y;
//     v1v2.k = v2.z - v1.z;

//     v1v3.i = v3.x - v1.x;
//     v1v3.j = v3.y - v1.y;
//     v1v3.k = v3.z - v1.z;

//     cross_product(v1v2, v1v3, normal);
//     normalize(normal, normal);
// endtask

// task cross_product(input Vector_t a, input Vector_t b, output Vector_t result);
//     result.i = a.j * b.k - a.k * b.j;
//     result.j = a.k * b.i - a.i * b.k;
//     result.k = a.i * b.j - a.j * b.i;
// endtask

// task normalize(input Vector_t a, output Vector_t result);
//     logic [15:0] mag;
//     magnitude(a, mag);
//     result.i = a.i / mag;
//     result.j = a.j / mag;
//     result.k = a.k / mag;
// endtask

// task magnitude(input Vector_t a, output logic [15:0] result);
//     logic [15:0] mag1, mag2, mag3;
//     q8_8_mult(a.i, a.i, mag1);
//     q8_8_mult(a.j, a.j, mag2);
//     q8_8_mult(a.k, a.k, mag3);
//     result = $sqrt(mag1 + mag2 + mag3);
// endtask

module TransformFaceModule (
    input Face_t face_i,
    input Matrix_t M,

    output Face_t face_o
    );

    TransformVertexModule vertex1 (
        .Point  (face_i.v1),
        .M      (M),
        .Result (face_o.v1)
    );

    TransformVertexModule vertex2 (
        .Point  (face_i.v2),
        .M      (M),
        .Result (face_o.v2)
    );

    TransformVertexModule vertex3 (
        .Point  (face_i.v3),
        .M      (M),
        .Result (face_o.v3)
    );

    // ! will only work in sim
    // get_normal(face_o.v1, face_o.v2, face_o.v3, face_o.normal);

    assign face_o.normal = face_i.normal;

    assign face_o.color = face_i.color;

endmodule


module TransformVertexModule (
    input Vertex_t Point, 
    input Matrix_t M,
    output Vertex_t Result
    );

    DotProduct PointX (
        .Point  (Point),
        .Col    (M.v1),
        .Result (Result.x)
    );

    DotProduct PointY (
        .Point  (Point),
        .Col    (M.v2),
        .Result (Result.y)
    );
    DotProduct PointZ (
        .Point  (Point),
        .Col    (M.v3),
        .Result (Result.z)
    );

endmodule