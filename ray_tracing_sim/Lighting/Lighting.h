#ifndef LIGHTING_H
#define LIGHTING_H
#include "../Primitives/Primitives.hpp"
#include <stdint.h>
#include <math.h>


uint16_t calc_color_intensity(uint16_t initial_color, Vector_t normal_vec, Vector_t light_vec);


#endif