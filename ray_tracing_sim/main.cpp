#include <iostream>
using namespace std;

#include "Primitives.hpp"
#include "RayTracer.hpp"
#include "Display.hpp"
#define DEFAULT_COLOR 0x0fff

void ray_trace(Camera_t camera, Display_t* display, vector<Face_t> obj_mem);


int main(void) {
    // vector<Face_t> obj_mem = parse_obj("scene.ply", 90, 152);
    vector<Face_t> obj_mem = parse_obj("cube.ply", 24, 12);

    Vertex_t cam_pos = Vertex_t({3.0f, 0.5f, 3.5f});

    Camera_t cam = create_camera(cam_pos, 
                                Vector_t({0.0f, 0.0f, 1.0f}), 
                                Vector_t({0.0f, 1.0f, 0.0f}),
                                1.0f, 1.0f);

    Display_t display = create_display();

    ray_trace(cam, &display, obj_mem);

    save_display(display, "output");
    return 0;
}

void ray_trace(Camera_t camera, Display_t* display, vector<Face_t> obj_mem) {
    for (int i = 0; i < DISPLAY_WIDTH; i++) {
        for (int j = 0; j < DISPLAY_HEIGHT; j++) {
            Vertex_t point = Vertex_t({
                (float)i / DISPLAY_WIDTH - 0.5f,
                (float)j / DISPLAY_HEIGHT - 0.5f,
                0.0f});

            Ray_t ray = create_ray(camera, point);

            for (Face_t face : obj_mem) {
                if (does_ray_triangle_intersect(ray, face)) {
                    float t = ray_triangle_intersection(ray, face);
                    if (t < ray.t) {
                        ray.t = t;
                        display_pixel(display, i, j, face.color);
                    }
                }
            }

            if (ray.t == RAY_T_MAX) {
                display_pixel(display, i, j, DEFAULT_COLOR);
            }
        }
    }
    return;
}