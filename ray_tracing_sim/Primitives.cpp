#include "Primitives.hpp"

std::vector<Face_t> parse_obj(const char* filename) {
    std::fstream file (filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        exit(1);
    }


    std::vector<Vertex_t> vertices;
    std::vector<Vector_t> vertex_normals;
    std::vector<Face_t> faces;

    while (!file.eof()) {
        std::string line;
        std::getline(file, line);

        std::string type = line.substr(0, line.find(' '));
        if (type.compare(VERTEX_CHAR) == 0) {
            vertices.push_back(parse_vertex(line));
        }
        else if (type.compare(VERTEX_NORMAL_CHAR) == 0) {
            vertex_normals.push_back(parse_vector(line));
        }
        else if (type.compare(FACE_CHAR) == 0) {
            faces.push_back(parse_face(line, vertices, vertex_normals));
        } 

    }

    return faces;
}

Vertex_t parse_vertex(std::string line) {
    Vertex_t v;
    std::string x, y, z;
    
    x = line.substr(2, line.find(' ', 2) - 2);
    y = line.substr(line.find(' ', 2) + 1, line.find(' ', line.find(' ', 2) + 1) - line.find(' ', 2) - 1);
    z = line.substr(line.find(' ', line.find(' ', 2) + 1) + 1, line.find(' ', line.find(' ', line.find(' ', 2) + 1) + 1) - line.find(' ', line.find(' ', 2) + 1) - 1);


    v.x = std::stof(x);
    v.y = std::stof(y);
    v.z = std::stof(z);

    return v;
}

Vector_t parse_vector(std::string line) {
    Vector_t v;
    std::string i, j, k;

    i = line.substr(3, line.find(' ', 3) - 3);
    j = line.substr(line.find(' ', 3) + 1, line.find(' ', line.find(' ', 3) + 1) - line.find(' ', 3) - 1);
    k = line.substr(line.find(' ', line.find(' ', 3) + 1) + 1, line.find(' ', line.find(' ', line.find(' ', 3) + 1) + 1) - line.find(' ', line.find(' ', 3) + 1) - 1);

    v.i = std::stof(i);
    v.j = std::stof(j);
    v.k = std::stof(k);

    return v;
}

Face_t parse_face(std::string line, std::vector<Vertex_t> vertices, std::vector<Vector_t> vertex_normals) {
    Face_t f;
    std::string v1_ind, v2_ind, v3_ind, vn_ind;

    v1_ind = line.substr(2, line.find('/', 2) - 2);
    v2_ind = line.substr(line.find(' ', 2) + 1, line.find('/', line.find(' ', 2) + 1) - line.find(' ', 2) - 1);
    v3_ind = line.substr(line.find(' ', line.find(' ', 2) + 1) + 1, line.find('/', line.find(' ', line.find(' ', 2) + 1) + 1) - line.find(' ', line.find(' ', 2) + 1) - 1);
    vn_ind = line.substr(line.find('/', line.find(' ', line.find(' ', 2) + 1) + 1) + 2, line.find(' ', line.find('/', line.find(' ', line.find(' ', 2) + 1) + 1) + 2) - line.find('/', line.find(' ', line.find(' ', 2) + 1) + 1) - 2);

    f.v1 = vertices.at(std::stoi(v1_ind) - 1);
    f.v2 = vertices.at(std::stoi(v2_ind) - 1);
    f.v3 = vertices.at(std::stoi(v3_ind) - 1);
    f.normal = vertex_normals.at(std::stoi(vn_ind) - 1);

    return f;
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
    printf("}\n");
}

