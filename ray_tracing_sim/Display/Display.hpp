#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#define DISPLAY_WIDTH 256
#define DISPLAY_HEIGHT 192

#include <cstdint>
#include <fstream>
#include <iostream>

typedef struct Display_t {
    uint16_t z_buffer[DISPLAY_WIDTH][DISPLAY_HEIGHT];
    uint16_t color_buffer[DISPLAY_WIDTH][DISPLAY_HEIGHT];    
} Display_t;


Display_t create_display();
void display_set_color(Display_t* display, int h_pix, int v_pix, uint16_t color);
void display_set_z(Display_t* display, int h_pix, int v_pix, uint16_t z);
uint16_t display_get_color(Display_t display, int h_pix, int v_pix);
uint16_t display_get_z(Display_t display, int h_pix, int v_pix);
void save_display(Display_t display, const char* filename);

void print_color_buffer(Display_t display);


#endif // DISPLAY_HPP