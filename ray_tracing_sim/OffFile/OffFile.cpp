#include "OffFile.hpp"

/**
 * @brief Reads an OFF file and returns an OffFile struct containing the data.
 * @param filename The name of the file to read.
 * @return A pointer to the new OffFile struct.
*/
OffFile* read_off_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) return NULL;

    OffFile* off_file = (OffFile*)malloc(sizeof(OffFile));
    if (off_file == NULL) {
        fclose(file);
        return NULL;
    }

    int result = get_object_details(file, &off_file->details);
    if (result != 0) {
        fclose(file);
        return NULL;
    }

    std::vector<Vertex_t> vertices = off_get_vertices(file, off_file->details.vertices);
    // if (vertices == NULL) {
    //     fclose(file);
    //     return NULL;
    // }

    std::vector<Face_t> faces = off_get_faces(file, off_file->details.faces, vertices);
    // if (vertices == NULL) {
        // fclose(file);
        // return NULL;
    // }


    off_file->vertices = vertices;
    off_file->faces = faces;
    fclose(file);
    return off_file;
}


/**
 * @brief Reads the object details from the file and stores them in the ObjectDetails struct.
 * @param file The file to read from.
 * @param object_details The ObjectDetails struct to store the data in.
 * @return 0 on success, -1 on failure.
*/
int get_object_details(FILE* file, ObjectDetails* object_details) {
    const int LINE_SIZE = 256;
    char line[LINE_SIZE];
    if (fgets(line, LINE_SIZE, file) == NULL) return -1;
    if (strcmp(line, "OFF\n") != 0) return -1;
    if (fgets(line, LINE_SIZE, file) == NULL) return -1;
    int num_vertices, num_faces, num_edges;
    if (sscanf(line, "%d %d %d", &num_vertices, &num_faces, &num_edges) != 3) return -1;
    object_details->vertices = num_vertices;
    object_details->faces = num_faces;
    object_details->edges = num_edges;
    return 0;
}


/**
 * @brief Reads the vertices from the off file and stores them in an ArrayList.
 * @param file The file to read from. Assume the file pointer is at the correct position.
 * @param vertices_cnt The number of vertices to read.
 * @return A pointer to the new ArrayList containing the vertices.
*/
std::vector<Vertex_t> off_get_vertices(FILE* file, int vertices_cnt) {
    char* line = NULL;
    size_t len = 0;

    std::vector<Vertex_t> vertices;
    for (int i=0; i<vertices_cnt; i++) {
        Vertex_t vertex;
        if (getline(&line, &len, file) == -1) {
            free(line);
            return vertices;
        }

        if (sscanf(line, "%f %f %f", &vertex.x, &vertex.y, &vertex.z) != 3) {
            free(line);
            return vertices;
        }

        vertices.push_back(vertex);
    }
    free(line);
    return vertices;
}


/**
 * @brief Reads the faces from the off file and stores them in an ArrayList.
 * @param file The file to read from. Assume the file pointer is at the correct position.
 * @param faces_cnt The number of faces to read.
 * @param vertices The ArrayList containing the vertices.
 * @return A pointer to the new ArrayList containing the faces.
*/
std::vector<Face_t> off_get_faces(FILE* file, int faces_cnt, std::vector<Vertex_t> vertices) {
    char* line = NULL;
    size_t len = 0;
    const int ARGS = 4;

    std::vector<Face_t> faces;
    int num_faces, v1_index, v2_index, v3_index;
    for (int i=0; i<faces_cnt; i++) {
        Face_t face;
        if (getline(&line, &len, file) == -1) {
            free(line);
            return faces;
        }

        if (sscanf(line, "%d %d %d %d", &num_faces, &v1_index, &v2_index, &v3_index) != ARGS) {
            free(line);
            return faces;
        }

        face.v1 = vertices.at(v1_index);
        face.v2 = vertices.at(v2_index);
        face.v3 = vertices.at(v3_index);

        face.color = 0xfff;

        faces.push_back(face);
    }
    free(line);
    return faces;
}


/**
 * @brief Frees the OffFile struct and all of its members.
 * @param off_file The OffFile struct to free.
*/
// void free_off_file(OffFile* off_file) {
//     array_list_free(off_file->vertices, free_vertex);
//     array_list_free(off_file->faces, free_face);
//     free(off_file);
// }


