#include <iostream>
using namespace std;

#include "Primitives.hpp"
#include "RayTracer.hpp"

#define DISPLAY_WIDTH 256
#define DISPLAY_HEIGHT 192




int main(void) {
    vector<Face_t> obj_mem = parse_obj("scene.obj");
    
    Ray_t ray = {
        {0.0f, 0.0f, 0.0f},
        {0.1f, 0.5f, 1.0f},
        13.0f
    };

    int i = 0;
    for (Face_t face : obj_mem) {
        if (does_ray_triangle_intersect(ray, face)) {
            printf("Ray intersects triangle %d at %f\n", i++, ray_triangle_intersection(ray, face));
            print_vertex(ray_point(ray, ray_triangle_intersection(ray, face)));
        }
    }

    printf("Ray intersects %d of %ld triangles\n", i, obj_mem.size());

    return 0;
}