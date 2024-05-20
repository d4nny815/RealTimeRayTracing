#include "Projection.h"

/**
 * @brief Projects a vertex onto the x-axis of the screen
 * @param v The vertex to project.
 * @param screen_width The width of the screen.
 * @return The x-coordinate of the projected vertex.
*/
uint8_t project_Vx(Vertex_t v, uint8_t screen_width) {
    // for testing purposes, to see accuracy compared to int math
    // double x = (((double)v->x / 4.0) + 1) / 2.0;
    // x *= screen_width + 1;
    // v->x = x;
    // printf("x using float math %f with v->x: %f\n", x, v->x);

    int16_t shift = (int16_t)(v.x * FLOAT_SCALAR);  // 2^8, so we can use bit shift and not lose precision
    
    shift >>= 2;
    shift += SPACE_TRANSLATOR;
    shift >>= 1;
    shift *= screen_width;
    shift >>= SHIFT;
    if (shift < 0) {
    shift = 0;
    } else if (shift > screen_width) {
    shift = screen_width;
    }
    // printf("shift: %hhd hex: %hhx\n\n", (uint8_t)shift);

    // printf("x using int math %hhu with v->x: %f\n", (uint8_t)shift, v->x);
    return (uint8_t)shift;
}


/**
 * @brief Projects a vertex onto the y-axis of the screen
 * @param v The vertex to project.
 * @param screen_height The height of the screen.
 * @return The y-coordinate of the projected vertex.
*/
uint8_t project_Vy(Vertex_t v, uint8_t screen_height) {
    int16_t shift = (int16_t)(-v.y * FLOAT_SCALAR);  // 2^8, so we can use bit shift and not lose precision
    shift = ((shift >> 2) + SPACE_TRANSLATOR) >> 1;
    shift *= screen_height;
    shift >>= SHIFT;
    if (shift < 0) {
        shift = 0;
    } else if (shift > screen_height) {
        shift = screen_height;
    }
    return (uint8_t)shift;
}


/**
 * @brief Projects a vertex onto the z-axis of the screen
 * @param v The vertex to project.
 * @param screen_depth The depth of the screen.
 * @return The z-coordinate of the projected vertex.
*/
uint8_t project_Vz(Vertex_t v, uint8_t screen_depth) {

    int16_t shift = (int16_t)(v.z * FLOAT_SCALAR);  // 2^8, so we can use bit shift and not lose precision
    shift = ((shift >> 2) + SPACE_TRANSLATOR) >> 1;
    shift *= screen_depth;
    shift >>= SHIFT;
    if (shift < 0) {
        shift = 0;
    } else if (shift > screen_depth) {
        shift = screen_depth;
    }

    return (uint8_t)shift;
}


/**
 * @brief Projects a face onto the screen
 * @param f The face to project.
 * @param screen_width The width of the screen.
 * @param screen_height The height of the screen.
 * @param screen_depth The depth of the screen.
 * @return pointer to the projected face, NULL if malloc fails
*/
intFace_t project_Face(Face_t f, uint8_t screen_width, uint8_t screen_height, uint8_t screen_depth) {
    intFace_t new_f;

    new_f.v1.x = project_Vx(f.v1, screen_width);
    new_f.v1.y = project_Vy(f.v1, screen_height);
    new_f.v1.z = project_Vz(f.v1, screen_depth);

    new_f.v2.x = project_Vx(f.v2, screen_width);
    new_f.v2.y = project_Vy(f.v2, screen_height);
    new_f.v2.z = project_Vz(f.v2, screen_depth);

    new_f.v3.x = project_Vx(f.v3, screen_width);
    new_f.v3.y = project_Vy(f.v3, screen_height);
    new_f.v3.z = project_Vz(f.v3, screen_depth);

    new_f.normal = f.normal;
    new_f.color = f.color;
    return new_f;
}

