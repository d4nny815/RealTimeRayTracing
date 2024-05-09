#ifndef PROJECTION_H
#define PROJECTION_H

#define FLOAT_SCALAR 128.0
#define SHIFT 7 
#define SPACE_CONST 1
#define SPACE_TRANSLATOR (unsigned int)(SPACE_CONST*FLOAT_SCALAR)

#include <stdlib.h>
#include "../Primitives/Primitives.hpp"

uint8_t project_Vx(Vertex_t v, uint8_t screen_width);
uint8_t project_Vy(Vertex_t v, uint8_t screen_height);
uint8_t project_Vz(Vertex_t v, uint8_t screen_depth);
intFace_t project_Face(Face_t f, uint8_t screen_width, uint8_t screen_height, uint8_t screen_depth);

#endif