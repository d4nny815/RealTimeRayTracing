#include "Rasterization.hpp"


/**
 * @brief Get the Vertices of a line between two vertices.
 * @param v1 The first vertex.
 * @param v2 The second vertex.
 * @return The vertices of the line.
 * @note https://www.geeksforgeeks.org/bresenhams-algorithm-for-3-d-line-drawing/
*/
std::vector<intVertex_t> getLineVertices(intVertex_t v1, intVertex_t v2) {
    std::vector<intVertex_t> vertices;


    // make a copy of the first vertex
    intVertex_t v;
    v.x = v1.x;
    v.y = v1.y;
    v.z = v1.z;
    vertices.push_back(v);

    uint8_t x1 = v1.x;
    uint8_t y1 = v1.y;
    uint8_t z1 = v1.z;
    uint8_t x2 = v2.x;
    uint8_t y2 = v2.y;
    uint8_t z2 = v2.z;
    int16_t dx = abs(x2 - x1);
    int16_t dy = abs(y2 - y1);
    int16_t dz = abs(z2 - z1);

    int8_t xs = (x2 - x1) > 0 ? 1 : -1;
    int8_t ys = (y2 - y1) > 0 ? 1 : -1;
    int8_t zs = (z2 - z1) > 0 ? 1 : -1;

    int16_t p1, p2;

    // Driving axis is X-axis"
    if (dx >= dy && dx >= dz) {
        p1 = 2 * dy - dx;
        p2 = 2 * dz - dx;
        while (x1 != x2) {
            x1 += xs;
            if (p1 >= 0) {
              y1 += ys;
              p1 -= 2 * dx;
            }
            if (p2 >= 0) {
              z1 += zs;
              p2 -= 2 * dx;
            }
            p1 += 2 * dy;
            p2 += 2 * dz;
            intVertex_t v;
            v.x = x1;
            v.y = y1;
            v.z = z1;

            vertices.push_back(v);
        }
    } 
 
    // Driving axis is Y-axis"
    else if (dy >= dx && dy >= dz) {
        p1 = 2 * dx - dy;
        p2 = 2 * dz - dy;
        while (y1 != y2) {
            y1 += ys;
            if (p1 >= 0) {
              x1 += xs;
              p1 -= 2 * dy;
            }
            if (p2 >= 0) {
              z1 += zs;
              p2 -= 2 * dy;
            }
            p1 += 2 * dx;
            p2 += 2 * dz;
            intVertex_t v;
            v.x = x1;
            v.y = y1;
            v.z = z1;

            vertices.push_back(v);
        }
    } 
    
    // Driving axis is Z-axis"
    else {
        p1 = 2 * dy - dz;
        p2 = 2 * dx - dz;
        while (z1 != z2) {
            z1 += zs;
            if (p1 >= 0) {
              y1 += ys;
              p1 -= 2 * dz;
            }
            if (p2 >= 0) {
              x1 += xs;
              p2 -= 2 * dz;
            }
            p1 += 2 * dy;
            p2 += 2 * dx;
            intVertex_t v;
            v.x = x1;
            v.y = y1;
            v.z = z1;

            vertices.push_back(v);
        }
    }
    return vertices;
}


/**
 * @brief Compare two vertices.
 * @param v1 The first vertex.
 * @param v2 The second vertex.
 * @return 1 if the vertices are the same, 0 otherwise.
*/
int compareVertices(const intVertex_t v1, const intVertex_t v2) {
    return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
}


/**
 * @brief Hash a vertex.
 * @param v The vertex.
 * @return The hash of the vertex.
 * @note every vertex is hashed to a unique value.
*/
uint32_t hashVertex(const intVertex_t v) {
    return (uint32_t)(v.x << 16 | v.y << 8 | v.z);
}


/**
 * @brief Get all the vertices in a polyfon.
 * @param f The face.
 * @return The vertices in the face.
*/
std::vector<intVertex_t> getVerticesInFace(intFace_t f) {
    std::vector<intVertex_t> vertices;
    std::vector<intVertex_t> line1 = getLineVertices(f.v1, f.v2);
    std::vector<intVertex_t> line2 = getLineVertices(f.v1, f.v3);
    int already_exists;
    

    for (unsigned int i = 0; i < line1.size(); i++) {
        for (unsigned int j = 0; j < line2.size(); j++) {
            intVertex_t v1 = line1.at(i); 
            intVertex_t v2 = line2.at(j);
            std::vector<intVertex_t> line3 = getLineVertices(v1, v2);
            for (unsigned int k = 0; k < line3.size(); k++) {
                intVertex_t v = line3.at(k); 
                
                // This is gross and not my best work, but it works and I dont want to fix the hashset
                // linear search through the list
                already_exists = 0;
                for (unsigned int l = 0; l < vertices.size(); l++) {
                    intVertex_t v_cmp = vertices.at(l);
                    if (compareVertices(v, v_cmp)) {
                        already_exists = 1;
                        break;
                    }
                }
                if (already_exists) { continue; }

                // print_intVertex(v);
                intVertex_t v_cpy;
                v_cpy.x = v.x;
                v_cpy.y = v.y;
                v_cpy.z = v.z;
                vertices.push_back(v_cpy);
            }
        }
    }

    return vertices;
}


/**
 * @brief Rasterize the faces.
 * @param faces The faces to rasterize. 
 * @param Z_BUFFER The Z buffer. All values initialized to MAX.
 * @param COLOR_BUFFER The color buffer. All values initialized to 0.
*/
void rasterize(std::vector<intFace_t> faces, Display_t* display) {
    for (unsigned int i=0; i<faces.size(); i++) {
        intFace_t f = faces.at(i);
        std::vector<intVertex_t> blocks = getVerticesInFace(f);
        for (unsigned int j=0; j<blocks.size(); j++) {
            intVertex_t v = blocks.at(j);

            // uint8_t z = display_get_z(*display, v.x, v.y);
            // printf("checking Z:%d against %d\n", v.z, z);
            if (v.z < display_get_z(*display, v.x, v.y)) {
                // printf("Setting z: %d, %d, %d\n", v.x, v.y, v.z);
                display_set_z(display, v.x, v.y, v.z);
                display_set_color(display, v.x, v.y, f.color);
            }
        }
        // printf("Rasterized face %d of %ld\n", i, faces.size());
    }
    return;
}


// void parallel_rasterize(ArrayList* faces, uint8_t* Z_BUFFER, uint8_t* COLOR_BUFFER, int num_processes) {
//     if (num_processes == 1) {
//         rasterize(faces, Z_BUFFER, COLOR_BUFFER);
//         return;
//     }
    
    
//     int num_faces = faces->index;
//     int faces_per_process = num_faces / num_processes;
//     int faces_remaining = num_faces % num_processes;
//     int start = 0;
//     int end = faces_per_process;
//     int pids[num_processes];
//     int fd_z[num_processes][2];
//     int fd_c[num_processes][2];

//     // struct to hold the data for the processes
//     typedef struct {
//         ArrayList* faces;
//         uint8_t* Z_BUFFER;
//         uint8_t* COLOR_BUFFER;
//     } ProcessData;

//     ProcessData data[num_processes];

//     // make the pipes
//     for (int i = 0; i < num_processes; i++) {
//         if (pipe(fd_c[i]) == -1) {
//             perror("pipe");
//             exit(1);
//         }
//         if (pipe(fd_z[i]) == -1) {
//             perror("pipe");
//             exit(1);
//         }
//     }

//     // distribute the faces to the processes
//     for (int i = 0; i < num_processes; i++) {
//         data[i].faces = array_list_new();
//         for (int j = start; j < end; j++) {
//             Face_i* f = (Face_i*) array_list_get(faces, j);
//             Face_i* f_cpy = (Face_i*) malloc(sizeof(Face_i));
//             f_cpy->v1 = f->v1;
//             f_cpy->v2 = f->v2;
//             f_cpy->v3 = f->v3;
//             f_cpy->normal = f->normal;
//             f_cpy->color = f->color;
//             array_list_append(data[i].faces, f_cpy);
//         }

//         data[i].Z_BUFFER = (uint8_t*) malloc(FRAME_BUFFER_SIZE * sizeof(uint8_t));
//         data[i].COLOR_BUFFER = (uint8_t*) malloc(FRAME_BUFFER_SIZE * sizeof(uint8_t));
//         memset(data[i].Z_BUFFER, DEPTH - 1, FRAME_BUFFER_SIZE * sizeof(uint8_t));
//         memset(data[i].COLOR_BUFFER, 0, FRAME_BUFFER_SIZE * sizeof(uint8_t));

//         start = end;
//         if (i < faces_remaining) {
//             end += faces_per_process + 1;
//         } else {
//             end += faces_per_process;
//         }
//     }
    
//     // fork the processes and have change the Z_BUFFER and COLOR_BUFFER in the structs
//     for (int i = 0; i < num_processes; i++) {
//         if ((pids[i] = fork()) == 0) {
//             rasterize(data[i].faces, data[i].Z_BUFFER, data[i].COLOR_BUFFER);
//             int w = write(fd_c[i][1], data[i].COLOR_BUFFER, FRAME_BUFFER_SIZE * sizeof(uint8_t));
//             if (w == -1) {
//                 perror("write");
//                 exit(1);
//             }
//             w = write(fd_z[i][1], data[i].Z_BUFFER, FRAME_BUFFER_SIZE * sizeof(uint8_t));
//             if (w == -1) {
//                 perror("write");
//                 exit(1);
//             }
//             exit(0);
            
//         }
//     }

//     // wait for the processes to finish
//     for (int i = 0; i < num_processes; i++) {
//         waitpid(pids[i], NULL, 0);
//     }

//     // combine the Z buffers
//     for (int i = 0; i < num_processes; i++) {
//         uint8_t* Z_BUFFER_i = (uint8_t*) malloc(FRAME_BUFFER_SIZE * sizeof(uint8_t));
//         int r = read(fd_z[i][0], Z_BUFFER_i, FRAME_BUFFER_SIZE * sizeof(uint8_t));
//         if (r == -1) {
//             perror("read");
//             exit(1);
//         }
//         uint8_t* COLOR_BUFFER_i = (uint8_t*) malloc(FRAME_BUFFER_SIZE * sizeof(uint8_t));
//         r = read(fd_c[i][0], COLOR_BUFFER_i, FRAME_BUFFER_SIZE * sizeof(uint8_t));
//         if (r == -1) {
//             perror("read");
//             exit(1);
//         }
//         for (int j = 0; j < FRAME_BUFFER_SIZE; j++) {
//             if (Z_BUFFER_i[j] < Z_BUFFER[j]) {
//                 Z_BUFFER[j] = Z_BUFFER_i[j];
//                 COLOR_BUFFER[j] = COLOR_BUFFER_i[j];
//             }

//         }
//         free(Z_BUFFER_i);
//         free(COLOR_BUFFER_i);

//     }


//     // free the memory
//     for (int i = 0; i < num_processes; i++) {
//         array_list_free(data[i].faces, free_face);
//         free(data[i].Z_BUFFER);
//         free(data[i].COLOR_BUFFER);
//     }



//     return;
// }
