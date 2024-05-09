#include "Rasterization.h"
#include <stdio.h>
#include <assert.h>


void test_geeksforgeeks() {
    Vertex_i v1 = {0, 0, 0};
    Vertex_i v2 = {5, 5, 5};

    ArrayList* vertices = getLineVertices(v1, v2);
    for (unsigned int i = 0; i < vertices->index; i++) {
        Vertex_i* v = (Vertex_i*) array_list_get(vertices, i);
        printf("Vertex %d: (%hhu, %hhu, %hhu)\n", i, v->x, v->y, v->z);
    }

    array_list_free(vertices, free_vertex);
}

void test_compareVertices1() {
    Vertex_i v1 = {1, 2, 3};
    Vertex_i v2 = {1, 2, 3};

    assert(compareVertices(v1, v2) == 1);
    printf("test_compareVertices1 passed\n");
}

void test_compareVertices2() {
    Vertex_i v1 = {1, 2, 3};
    Vertex_i v2 = {1, 2, 4};

    assert(compareVertices(v1, v2) == 0);
    printf("test_compareVertices2 passed\n");
}

void test_hashVertex() {
    for (unsigned int i = 0; i < HEIGHT; i++) {
        for (unsigned int j = 0; j < WIDTH; j++) {
            for (unsigned int k = 0; k < DEPTH; k++) {
                uint32_t hash = hashVertex((Vertex_i){i, j, k});
                uint8_t x = (hash >> 16) & 0xFF;
                uint8_t y = (hash >> 8) & 0xFF;
                uint8_t z = hash & 0xFF;
                assert(x == i);
                assert(y == j);
                assert(z == k);
            }
        }
    }

    printf("test_hashVertex passed\n");
}

void test_getVerticesInFace() {
    Face_i f;
    f.v1 = (Vertex_i){0, 0, 0};
    f.v2 = (Vertex_i){2, 1, 3};
    f.v3 = (Vertex_i){5, 5, 5};

    ArrayList* vertices = getVerticesInFace(f);
    for (unsigned int i = 0; i < vertices->index; i++) {
        Vertex_i* v = (Vertex_i*) array_list_get(vertices, i);
        print_vertex_i(*v);
        printf("\n");
    }

    array_list_free(vertices, free_vertex);
    printf("test_getVerticesInFace passed\n");
}



int main(void) {
    test_geeksforgeeks();
    test_compareVertices1();
    test_compareVertices2();
    test_hashVertex();
    test_getVerticesInFace();


    return 0;
}