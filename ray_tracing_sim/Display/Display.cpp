#include "Display.hpp"

Display_t create_display() {
    Display_t display;

    for (int i = 0; i < DISPLAY_HEIGHT; i++) {
        for (int j = 0; j < DISPLAY_WIDTH; j++) {
            display.color_buffer[j][i] = 0;
            display.z_buffer[j][i] = 255;
        }
    }

    return display;
}


void display_set_color(Display_t* display, int h_pix, int v_pix, uint16_t color) {
    display->color_buffer[h_pix][v_pix] = color;
}


void display_set_z(Display_t* display, int h_pix, int v_pix, uint16_t z) {
    display->z_buffer[h_pix][v_pix] = z;

}

uint16_t display_get_color(Display_t display, int h_pix, int v_pix) {
    return display.color_buffer[h_pix][v_pix];
}

void print_color_buffer(Display_t display) {
    for (int i = 0; i < DISPLAY_HEIGHT; i++) {
        for (int j = 0; j < DISPLAY_WIDTH; j++) {
            printf("%hhu ", display_get_color(display, j, i));
        }
        printf("\n");
    }
}


uint16_t display_get_z(Display_t display, int h_pix, int v_pix) {
    return display.z_buffer[h_pix][v_pix];
}

void save_display(Display_t display, const char* filename) {
    std::ofstream file;
    std::string extension = ".ppm";
    std::string full_filename = filename + extension;
    file.open(full_filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        exit(1);
    }

    file << "P3\n";
    file << DISPLAY_WIDTH << " " << DISPLAY_HEIGHT << "\n";
    file << "255\n";

    for (int i=0; i<DISPLAY_HEIGHT; i++) {
        for (int j=0; j<DISPLAY_WIDTH; j++) {
            uint16_t color = display_get_color(display, j, i);
            // if (color) printf("Color: %x at %hx %hx\n", color, j, i);
            uint8_t r = (color & 0xF00) >> 8;
            uint8_t g = (color & 0x0F0) >> 4;
            uint8_t b = color & 0x00F;
            r *= 16;
            g *= 16;
            b *= 16;
            // if (color) printf("Color: %hhx %hhx %hhx\n", r, g, b);
            file << (int)r << " " << (int)g << " " << (int)b << " ";
        }
        file << "\n";
    }

    file.close();
    return;
}
