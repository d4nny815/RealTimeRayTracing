#include "Primitives.hpp"

float vec_dot_product(Vector_t A, Vector_t B) {
    return A.i * B.i + A.j * B.j + A.k * B.k;
}

Vector_t vec_cross_product(Vector_t A, Vector_t B) {
    Vector_t C;
    C.i = A.j * B.k - A.k * B.j;
    C.j = A.k * B.i - A.i * B.k;
    C.k = A.i * B.j - A.j * B.i;
    return C;
}

Vector_t vec_scalar(Vector_t A, float scalar) {
    Vector_t result;
    result.i = A.i * scalar;
    result.j = A.j * scalar;
    result.k = A.k * scalar;
    return result;
}

Vector_t vec_add(Vector_t A, Vector_t B) {
    Vector_t result;
    result.i = A.i + B.i;
    result.j = A.j + B.j;
    result.k = A.k + B.k;
    return result;
}

Vector_t get_normal(Vertex_t v1, Vertex_t v2, Vertex_t v3) {
    Vector_t A = {v2.x - v1.x, v2.y - v1.y, v2.z - v1.z};
    Vector_t B = {v3.x - v1.x, v3.y - v1.y, v3.z - v1.z};
    return vec_normalize(vec_cross_product(A, B));
}

Vector_t vec_normalize(Vector_t A) {
    float magnitude = vec_magnitude(A);
    return vec_scalar(A, 1 / magnitude); // will have to figure out how divide in hardware
}

float vec_magnitude(Vector_t A) {
    return sqrt(A.i * A.i + A.j * A.j + A.k * A.k);
}

uint8_t face_get_red(Face_t f) {
    return (f.color >> 8) & 0xf;
}

uint8_t face_get_green(Face_t f) {
    return (f.color >> 4) & 0xf;
}

uint8_t face_get_blue(Face_t f) {
    return f.color & 0xf;
}

Vector_t vertex_to_vector(Vertex_t v) {
    return {v.x, v.y, v.z};
}




void print_vertex(Vertex_t v) {
    std::cout << "Vertex: (" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
}

void print_vector(Vector_t v) {
    std::cout << "Vector: <" << v.i << ", " << v.j << ", " << v.k << ">" << std::endl;
}

void print_face(Face_t f) {
    printf("Face: {\n");
    print_vertex(f.v1);
    print_vertex(f.v2);
    print_vertex(f.v3);
    print_vector(f.normal);
    printf("Color: r: %hhx, g: %hhx, b: %hhx\n", (f.color >> 8) & 0xf, (f.color >> 4) & 0xf, f.color & 0xf);
    printf("}\n");
}

void print_intVertex(intVertex_t v) {
    std::cout << "Vertex: (" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
}

void print_intFace(intFace_t f) {
    printf("Face: {\n");
    print_intVertex(f.v1);
    print_intVertex(f.v2);
    print_intVertex(f.v3);
    printf("Color: r: %hhx, g: %hhx, b: %hhx\n", (f.color >> 8) & 0xf, (f.color >> 4) & 0xf, f.color & 0xf);
    printf("}\n");
}

