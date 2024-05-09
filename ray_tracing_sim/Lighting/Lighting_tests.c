#include <stdio.h>
#include <assert.h>
#include "Lighting.h"
#include "../Primitives/Primitives.h"

void test_calc_color_intensity1() {
    ColorValue initial_color = {255};
    Vector normal_vec = {0.0, 0.0, 1.0};
    Vector light_vec = {1.0, 1.0, 1.0};
    uint8_t intensity = calc_color_intensity(initial_color, normal_vec, light_vec);
    assert(intensity == 255);

    printf("test_calc_color_intensity1 passed!\n");
}

void test_calc_color_intensity2() {
    ColorValue initial_color = {255};
    Vector normal_vec = {0.0, 0.0, 1.0};
    Vector light_vec = {0.0, 0.0, 1.0};
    uint8_t intensity = calc_color_intensity(initial_color, normal_vec, light_vec);
    assert(intensity == 255);

    printf("test_calc_color_intensity2 passed!\n");
}

void test_calc_color_intensity3() {
    ColorValue initial_color = {255};
    Vector normal_vec = {0.2, 1.0, 1.0};
    Vector light_vec = {0.3, 0.7, -1.0};
    uint8_t intensity = calc_color_intensity(initial_color, normal_vec, light_vec);
    uint8_t expected = 61;
    assert(intensity == expected);

    printf("test_calc_color_intensity3 passed!\n");
}

void test_calc_color_intensity4() {
    ColorValue initial_color = {150};
    Vector normal_vec = {0.2, .5, 0};
    Vector light_vec = {0.3, 0.3, -.1};
    uint8_t intensity = calc_color_intensity(initial_color, normal_vec, light_vec);
    uint8_t expected = 31;
    assert(intensity == expected);

    printf("test_calc_color_intensity4 passed!\n");
}


int main() {
    test_calc_color_intensity1();
    test_calc_color_intensity2();
    test_calc_color_intensity3();
    test_calc_color_intensity4();

    printf("All tests passed!\n");

    return 0;
}