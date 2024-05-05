#include "Primitives.hpp"

std::vector<Face_t> parse_obj(const char* filename, int vertices_cnt, int faces_cnt) {
    std::fstream file (filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        exit(1);
    }


    

    while (!file.eof()) {
        std::string line;
        std::getline(file, line);

        if (line.compare("end_header") == 0) {
            printf("end header\n");
            break;
        }
    }

    std::vector<Vertex_t> vertices;
    std::vector<Vector_t> vertex_normals;
    std::vector<uint32_t> colors;
    for (int _=0; _<vertices_cnt; _++) {
        Vertex_t v;
        Vector_t vn;
        uint32_t color_base;

        std::string line;
        std::getline(file, line);
        parse_vertex(line, &v, &vn, &color_base);

        vertices.push_back(v);
        vertex_normals.push_back(vn);
        colors.push_back(color_base);
    }

    // printf("Vertices:\n");
    // for (Vertex_t v : vertices) {
        // print_vertex(v);
    // }

    // printf("Vertex Normals:\n");
    // for (Vector_t vn : vertex_normals) {
    //     print_vector(vn);
    // }

    // printf("Colors:\n");
    // for (uint16_t color : colors) {
    //     printf("0x%04x\n", color);
    // }

    std::vector<Face_t> faces;

    for (int _=0; _<faces_cnt; _++) {
        Face_t face = {};
        std::string line;
        std::getline(file, line);
        parse_face(line, &face, vertices, vertex_normals, colors);
        faces.push_back(face);
    }

    // printf("Faces:\n");
    // for (Face_t f : faces) {
    //     print_face(f);
    // }
    return faces;
}

void parse_vertex(std::string line, Vertex_t* v, Vector_t* vn, uint32_t* color) {
    std::string x, y, z, nx, ny, nz, r, g, b;

    size_t start = 0;
    size_t end = line.find(" ");
    x = line.substr(start, end - start);
    start = end + 1;
    end = line.find(" ", start);
    y = line.substr(start, end - start);
    start = end + 1;
    end = line.find(" ", start);
    z = line.substr(start, end - start);
    start = end + 1;
    end = line.find(" ", start);
    nx = line.substr(start, end - start);
    start = end + 1;
    end = line.find(" ", start);
    ny = line.substr(start, end - start);
    start = end + 1;
    end = line.find(" ", start);
    nz = line.substr(start, end - start);
    start = end + 1;
    end = line.find(" ", start);
    r = line.substr(start, end - start);
    start = end + 1;
    end = line.find(" ", start);
    g = line.substr(start, end - start);
    start = end + 1;
    end = line.find(" ", start);
    b = line.substr(start, end - start);

    v->x = std::stof(x);
    v->y = std::stof(y);
    v->z = std::stof(z);

    vn->i = std::stof(nx);
    vn->j = std::stof(ny);
    vn->k = std::stof(nz);

    uint8_t red = (std::stoi(r));
    uint8_t green = (std::stoi(g));
    uint8_t blue = (std::stoi(b));
    *color = (red << 16) | (green << 8) | blue;

    return;
}

void parse_face(std::string line, Face_t* face, std::vector<Vertex_t> vertices, std::vector<Vector_t> vertex_normals, std::vector<uint32_t> colors) {
    std::string v1_ind, v2_ind, v3_ind;

    size_t start = 2;
    size_t end = line.find(" ", start);
    v1_ind = line.substr(start, end - start);
    start = end + 1;
    end = line.find(" ", start);
    v2_ind = line.substr(start, end - start);
    start = end + 1;
    end = line.find(" ", start);
    v3_ind = line.substr(start, end - start);

    face->v1 = vertices[std::stoi(v1_ind)];
    face->v2 = vertices[std::stoi(v2_ind)];
    face->v3 = vertices[std::stoi(v3_ind)];

    face->normal.i = (vertex_normals[std::stoi(v1_ind)].i + 
                        vertex_normals[std::stoi(v2_ind)].i + 
                        vertex_normals[std::stoi(v3_ind)].i) 
                        / 3;
    face->normal.j = (vertex_normals[std::stoi(v1_ind)].j +
                        vertex_normals[std::stoi(v2_ind)].j +
                        vertex_normals[std::stoi(v3_ind)].j)
                        / 3;
    face->normal.k = (vertex_normals[std::stoi(v1_ind)].k +
                        vertex_normals[std::stoi(v2_ind)].k +
                        vertex_normals[std::stoi(v3_ind)].k)
                        / 3;
    face->normal = vec_normalize(face->normal);
            
                
    uint8_t red = ((colors[std::stoi(v1_ind)] >> 16) + 
                    (colors[std::stoi(v2_ind)] >> 16) + 
                    (colors[std::stoi(v3_ind)] >> 16)) / 3;
    uint8_t green = ((colors[std::stoi(v1_ind)] >> 8) + 
                    (colors[std::stoi(v2_ind)] >> 8) + 
                    (colors[std::stoi(v3_ind)] >> 8)) / 3;
    uint8_t blue = ((colors[std::stoi(v1_ind)]) +
                    (colors[std::stoi(v2_ind)]) +
                    (colors[std::stoi(v3_ind)])) / 3;    

    face->color = ((red >> 4) << 8) | ((green >> 4) << 4) | (blue >> 4);
    return;
}


float vec_dot_product(Vector_t A, Vector_t B) {
    return A.i * B.i + A.j * B.j + A.k * B.k;
}

Vector_t vec_cross_product(Vector_t A, Vector_t B) {
    Vector_t C;
    C.i = A.j * B.k - A.k * B.j;
    C.j = A.k * B.i - A.i * B.k;
    C.k = A.i * B.j - A.j * B.i;
    return C;
}

Vector_t vec_scalar(Vector_t A, float scalar) {
    Vector_t result;
    result.i = A.i * scalar;
    result.j = A.j * scalar;
    result.k = A.k * scalar;
    return result;
}

Vector_t vec_add(Vector_t A, Vector_t B) {
    Vector_t result;
    result.i = A.i + B.i;
    result.j = A.j + B.j;
    result.k = A.k + B.k;
    return result;
}

Vector_t vec_normalize(Vector_t A) {
    float magnitude = vec_magnitude(A);
    return vec_scalar(A, 1 / magnitude); // will have to figure out how divide in hardware
}

float vec_magnitude(Vector_t A) {
    return sqrt(A.i * A.i + A.j * A.j + A.k * A.k);
}




void print_vertex(Vertex_t v) {
    std::cout << "Vertex: (" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
}

void print_vector(Vector_t v) {
    std::cout << "Vector: <" << v.i << ", " << v.j << ", " << v.k << ">" << std::endl;
}

void print_face(Face_t f) {
    printf("Face: {\n");
    print_vertex(f.v1);
    print_vertex(f.v2);
    print_vertex(f.v3);
    print_vector(f.normal);
    printf("Color: r: %hhx, g: %hhx, b: %hhx\n", (f.color >> 8) & 0xf, (f.color >> 4) & 0xf, f.color & 0xf);
    printf("}\n");
}

