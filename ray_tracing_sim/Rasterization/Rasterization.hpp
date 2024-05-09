#ifndef RASTERIZATION_H
#define RASTERIZATION_H

// Where DISPLAY_WIDTH and DISPLAY_HEIGHT are the dimensions of the display
#define DISPLAY_WIDTH 256
#define DISPLAY_HEIGHT 256
#define DEPTH 256

#include <unistd.h>
#include <stdint.h>
#include <wait.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include "../Primitives/Primitives.hpp"
#include "../Display/Display.hpp"


// ? what if i calc the max amount of blocks a polygon can be and that becomes the MAX POLYGON Buffer size 
#define MAX_POLYGON_BUFFER DISPLAY_WIDTH*DISPLAY_HEIGHT*DEPTH // need a 2^24 = 16MB Memory Block if storing 8b color
// ! this changes depending on display size
#define FRAME_BUFFER_SIZE DISPLAY_HEIGHT*DISPLAY_WIDTH  // need a 2^16 = 64kB Framebuffer 

#include "../Primitives/Primitives.hpp"
#include <stdlib.h>
#include <math.h>

std::vector<intVertex_t> getLineVertices(intVertex_t v1, intVertex_t v2);
int compareVertices(const intVertex_t v1, const intVertex_t v2);
uint32_t hashVertex(const intVertex_t v);
std::vector<intVertex_t> getVerticesInFace(intFace_t f);
void rasterize(std::vector<intFace_t> faces, Display_t* display);
// void parallel_rasterize(ArrayList* faces, uint8_t* Z_BUFFER, uint8_t* COLOR_BUFFER, int num_processes);




#endif