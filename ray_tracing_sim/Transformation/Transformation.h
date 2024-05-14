#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H
#include "../Primitives/Primitives.hpp"
#include <stdlib.h>
#include <stdio.h>

#define MAT_DIM 4
static float TRANSFORM_MATRIX[MAT_DIM * MAT_DIM] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

void transformVertex(Vertex_t* v,  float* transform_matrix, const int num_dimensions);
void transformFace(Face_t* f, float* transform_matrix, const int num_dimensions);

#endif