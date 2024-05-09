#include "RayTracer.hpp"

Vertex_t ray_point(Ray_t ray, float t) {
    Vertex_t point;
    point.x = ray.origin.x + t * ray.direction.i;
    point.y = ray.origin.y + t * ray.direction.j;
    point.z = ray.origin.z + t * ray.direction.k;

    return point;
}

bool does_ray_triangle_intersect(Ray_t ray, Face_t face) {
    float dot_product = vec_dot_product(face.normal, ray.direction);
    return dot_product > 0 && dot_product > RAY_T_MIN && dot_product < RAY_T_MAX;
}

float ray_triangle_intersection(Ray_t ray, Face_t face) {
    Vertex_t midpoint = {
        (face.v1.x + face.v2.x + face.v3.x) / 3,
        (face.v1.y + face.v2.y + face.v3.y) / 3,
        (face.v1.z + face.v2.z + face.v3.z) / 3
    };
    Vector_t point_distance = {
        midpoint.x - ray.origin.x,
        midpoint.y - ray.origin.y,
        midpoint.z - ray.origin.z
    };
    return vec_dot_product(point_distance, face.normal) / vec_dot_product(ray.direction, face.normal);
}

Camera_t create_camera(Vertex_t origin, Vector_t target, Vector_t upguide, float fov, float aspect_ratio) {
    Camera_t camera;

    camera.origin = origin;
    camera.forward = vec_normalize(vec_add(target, vec_scalar(vertex_to_vector(origin), -1)));
    camera.right = vec_normalize(vec_cross_product(camera.forward, upguide));
    camera.up = vec_cross_product(camera.right, camera.forward); // dont need to normalize because right and forward are already normalized
    
    camera.v_fov = tan(fov);
    camera.h_fov = camera.v_fov * aspect_ratio;

    return camera;
}

Ray_t create_ray(Camera_t camera, Vertex_t point) {
    Ray_t ray;
    ray.origin = camera.origin;
    ray.direction = vec_normalize(
        vec_add(
            camera.forward,
            vec_add(
                vec_scalar(camera.right, camera.h_fov * (point.x)),
                vec_scalar(camera.up, camera.v_fov * (point.y))
            )
        )
    );
    ray.t = RAY_T_MAX;

    return ray;
}
