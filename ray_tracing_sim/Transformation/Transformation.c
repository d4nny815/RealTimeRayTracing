#include "Transformation.h"


void transformVertex(Vertex_t* v, float* transform_matrix, const int num_dimensions) {
    float vertex_vector[] = {v->x, v->y, v->z, 0};
    float* result_mat = (float*) malloc(sizeof(float) * num_dimensions);

    for (int i=0; i<num_dimensions; i++) {
        result_mat[i] = 0; 
        for (int j=0; j<num_dimensions; j++) {
            result_mat[i] += vertex_vector[j] * transform_matrix[j*num_dimensions + i];
        }
    }
    v->x = result_mat[0];
    v->y = result_mat[1];
    v->z = result_mat[2];
    free(result_mat);
    return;
}

void transformFace(Face_t* f, float* transform_matrix, const int num_dimensions) {
    transformVertex(&f->v1, transform_matrix, num_dimensions);
    transformVertex(&f->v2, transform_matrix, num_dimensions);
    transformVertex(&f->v3, transform_matrix, num_dimensions);

    f->normal = get_normal(f->v1, f->v2, f->v3);
    return;
}
