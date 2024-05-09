#ifndef OFF_FILE_H
#define OFF_FILE_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <vector>
#include "../Primitives/Primitives.hpp"

typedef struct ObjectDetails {
    int32_t vertices;
    int32_t faces;
    int32_t edges;
} ObjectDetails;

typedef struct OffFile {
    ObjectDetails details;   // vertices, faces, edges
    std::vector<Vertex_t> vertices;     // list of vertices
    std::vector<Face_t> faces;        // list of faces
} OffFile;

OffFile* read_off_file(const char* filename);
int get_object_details(FILE* file, ObjectDetails* details);
std::vector<Vertex_t> off_get_vertices(FILE* file, int vertices_cnt);
std::vector<Face_t> off_get_faces(FILE* file, int faces_cnt, std::vector<Vertex_t> vertices);

// void free_off_file(OffFile* off_file);

#endif // OFF_FILE_H