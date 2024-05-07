#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#define DISPLAY_WIDTH 512
#define DISPLAY_HEIGHT 384

#include <cstdint>
#include <fstream>
#include <iostream>

typedef struct Display_t {
    uint16_t pixels[DISPLAY_WIDTH][DISPLAY_HEIGHT];
} Display_t;

Display_t create_display();
void display_pixel(Display_t* display, int h_pix, int v_pix, uint16_t color);
uint16_t get_pixel(Display_t display, int h_pix, int v_pix);

void save_display(Display_t display, const char* filename);



#endif // DISPLAY_HPP