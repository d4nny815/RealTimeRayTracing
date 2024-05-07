#include "Display.hpp"

Display_t create_display() {
    Display_t display;
    for (int i = 0; i < DISPLAY_WIDTH; i++) {
        for (int j = 0; j < DISPLAY_HEIGHT; j++) {
            display.pixels[i][j] = 0;
        }
    }
    return display;
}

void display_pixel(Display_t* display, int h_pix, int v_pix, uint16_t color) {
    display->pixels[h_pix][v_pix] = color;

    return;
}

uint16_t get_pixel(Display_t display, int h_pix, int v_pix) {
    return display.pixels[h_pix][v_pix];
}

void save_display(Display_t display, const char* filename) {
    std::ofstream file;
    std::string file_extension = ".ppm";
    file.open(filename + file_extension);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        exit(1);
    }

    file << "P3\n";
    file << DISPLAY_WIDTH << " " << DISPLAY_HEIGHT << "\n";
    file << "255\n";

    for (int j = 0; j < DISPLAY_HEIGHT; j++) {
        for (int i = 0; i < DISPLAY_WIDTH; i++) {
            uint16_t color = display.pixels[i][j];
            uint8_t red = ((color >> 8) & 0xF) * 16;
            uint8_t green = ((color >> 4) & 0xF) * 16;
            uint8_t blue = (color & 0xF) * 16;


            file << (int)red << " " << (int)green << " " << (int)blue << " ";
        }
        file << "\n";
    }

}