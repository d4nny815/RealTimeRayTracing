#include "Lighting.h"


/**
 * @brief Calculate the intensity of the color based on the normal vector and the light vector
 * @param initial_color The initial color of the face
 * @param normal_vec The normal vector of the face
 * @param light_vec The light vector, assumed to be a unit vecto
 * @return The new color value
*/
uint16_t calc_color_intensity(uint16_t initial_color, Vector_t normal_vec, Vector_t light_vec) {
    float m_mag = vec_dot_product(normal_vec, light_vec);
    m_mag = fabs(m_mag);

    uint8_t red = (uint8_t) ((initial_color >> 8) & 0xf);
    uint8_t green = (uint8_t) ((initial_color >> 4) & 0xf);
    uint8_t blue = (uint8_t) (initial_color & 0xf);

    red = (uint8_t) (red * m_mag) & 0xf;
    green = (uint8_t) (green * m_mag) & 0xf;
    blue = (uint8_t) (blue * m_mag) & 0xf;

    return (red << 8) | (green << 4) | blue;
}