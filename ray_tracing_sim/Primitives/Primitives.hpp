
#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <math.h>

#define COMMENT_CHAR "#"
#define VERTEX_CHAR "v"
#define VERTEX_NORMAL_CHAR "vn"
#define FACE_CHAR "f"

typedef struct Vertex_t {
    float x;
    float y;
    float z;
} Vertex_t;

typedef struct Vector_t {
    float i;
    float j;
    float k;
} Vector_t;

typedef struct Face_t {
    Vertex_t v1;
    Vertex_t v2;
    Vertex_t v3;
    Vector_t normal;
    uint16_t color;
} Face_t;

typedef struct intVertex_t {
    uint16_t x;
    uint16_t y;
    uint16_t z;
} intVertex_t;

typedef struct intFace_t {
    intVertex_t v1;
    intVertex_t v2;
    intVertex_t v3;
    Vector_t normal;
    uint16_t color;
} intFace_t;



Vector_t vec_cross_product(Vector_t A, Vector_t B);
float vec_dot_product(Vector_t A, Vector_t B);
Vector_t vec_scalar(Vector_t A, float scalar);
Vector_t vec_add(Vector_t A, Vector_t B);
Vector_t get_normal(Vertex_t v1, Vertex_t v2, Vertex_t v3);
Vector_t vec_normalize(Vector_t A);
float vec_magnitude(Vector_t A);
Vector_t vertex_to_vector(Vertex_t v);
uint8_t face_get_red(Face_t f);
uint8_t face_get_green(Face_t f);
uint8_t face_get_blue(Face_t f);

void print_vertex(Vertex_t v);
void print_vector(Vector_t v);
void print_face(Face_t f);
void print_intVertex(intVertex_t v);
void print_intFace(intFace_t f);



#endif // PRIMITIVES_H