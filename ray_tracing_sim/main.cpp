#include <iostream>
using namespace std;

#include "OffFile/OffFile.hpp"
#include "Primitives/Primitives.hpp"
#include "PlyFile/PlyFile.hpp"
#include "Transformation/Transformation.h"
#include "Lighting/Lighting.h"
#include "Projection/Projection.h"
#include "Rasterization/Rasterization.hpp"
#include "Display/Display.hpp"


int main(void) {
    // vector<Face_t> obj_mem = parse_obj("scene.ply", 90, 152);
    // OffFile* off_file = read_off_file("teapot.off");
    vector<Face_t> obj_mem = parse_obj("cube.ply", 24, 12);
    // std::vector<Face_t> obj_mem = off_file->faces;

    



    printf("Transformation\n");
    for (Face_t& face: obj_mem) {
        transformFace(&face, TRANSFORM_MATRIX, MAT_DIM);

        // print_face(face);
    }



    printf("Lighting\n");
    Vector_t LIGHT_VEC = {.6, .707, .9};
	Vector_t LIGHT_VEC_NORMALIZED = vec_normalize(LIGHT_VEC);
    for (Face_t& face: obj_mem) {
        face.color = calc_color_intensity(face.color, face.normal, LIGHT_VEC_NORMALIZED);

        // print_face(face);
    }

    printf("Projection\n");
    std::vector<intFace_t> projected_faces;
    for (Face_t face: obj_mem) {
        intFace_t projected_face = project_Face(face, DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 1, DEPTH - 1);
        // print_intFace(projected_face);
        projected_faces.push_back(projected_face);
    }


    printf("Rasterization\n");
    Display_t display = create_display();
    rasterize(projected_faces, &display);
    // print_color_buffer(display);

    printf("Saving Display\n");
    save_display(display, "output");

    printf("Done\n");
    return 0;

}
