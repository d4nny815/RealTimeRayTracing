#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP

#include "Primitives.hpp"

#define RAY_T_MIN 0.0001f
#define RAY_T_MAX 1000000000000000.0f

typedef struct Ray_t {
    Vertex_t origin;
    Vector_t direction; // normalized
    float t;
} Ray_t;

Vertex_t ray_point(Ray_t ray, float t);
bool does_ray_triangle_intersect(Ray_t ray, Face_t face);
float ray_triangle_intersection(Ray_t ray, Face_t face);


#endif