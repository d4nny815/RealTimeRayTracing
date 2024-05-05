
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
} Face_t;



std::vector<Face_t> parse_obj(const char* filename);
Vertex_t parse_vertex(std::string line);
Vector_t parse_vector(std::string line);
Face_t parse_face(std::string line, std::vector<Vertex_t> vertices, std::vector<Vector_t> vertex_normals);

Vector_t vec_cross_product(Vector_t A, Vector_t B);
float vec_dot_product(Vector_t A, Vector_t B);
Vector_t vec_scalar(Vector_t A, float scalar);
Vector_t vec_add(Vector_t A, Vector_t B);
Vector_t vec_normalize(Vector_t A);
float vec_magnitude(Vector_t A);
// float q_rsqrt(float number);

void print_vertex(Vertex_t v);
void print_vector(Vector_t v);
void print_face(Face_t f);



#endif // PRIMITIVES_H