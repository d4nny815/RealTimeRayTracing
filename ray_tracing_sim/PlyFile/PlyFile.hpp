#ifndef PLYFILE_HPP
#define PLYFILE_HPP

#include "../Primitives/Primitives.hpp"


std::vector<Face_t> parse_obj(const char* filename, int vertices_cnt, int faces_cnt);
void parse_vertex_line(std::string line, Vertex_t *v, Vector_t *vn, uint32_t *color);
void parse_face_line(std::string line, Face_t* face, std::vector<Vertex_t> vertices, std::vector<Vector_t> vertex_normals, std::vector<uint32_t> colors);
// Vector_t parse_vector(std::string line);




#endif // PLYFILE_HPP