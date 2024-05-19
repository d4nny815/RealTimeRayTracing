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
    // ! DANNY
    // ! export ply with -z forward and y up
    // vector<Face_t> obj_mem = parse_obj("scene.ply", 90, 152);
    // vector<Face_t> obj_mem = parse_obj("cube.ply", 24, 12);
    // vector<Face_t> obj_mem = parse_obj("cube2.ply", 24, 12);
    vector<Face_t> obj_mem = parse_obj("obj3.ply", 264, 92);
    // vector<Face_t> obj_mem = parse_obj("funny.ply", 5100, 2124);

    Vector_t LIGHT_VEC = {.6, .707, .9};
	Vector_t LIGHT_VEC_NORMALIZED = vec_normalize(LIGHT_VEC);

    for (Face_t face : obj_mem) {
        transformFace(&face, TRANSFORM_MATRIX, MAT_DIM);   
        face.color = calc_color_intensity(face.color, face.normal, LIGHT_VEC_NORMALIZED);
        
        
        print_face(face);
    }



    // printf("Transformation\n");
    // for (Face_t& face: obj_mem) {
    //     transformFace(&face, TRANSFORM_MATRIX, MAT_DIM);

    //     // print_face(face);
    // }



    // printf("Lighting\n");
    // Vector_t LIGHT_VEC = {.6, .707, .9};
	// Vector_t LIGHT_VEC_NORMALIZED = vec_normalize(LIGHT_VEC);
    // for (Face_t& face: obj_mem) {
    //     face.color = calc_color_intensity(face.color, face.normal, LIGHT_VEC_NORMALIZED);

    //     // print_face(face);
    // }

    // printf("Projection\n");
    // std::vector<intFace_t> projected_faces;
    // for (Face_t face: obj_mem) {
    //     intFace_t projected_face = project_Face(face, DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 1, DEPTH - 1);
    //     // print_intFace(projected_face);
    //     projected_faces.push_back(projected_face);
    // }


    // printf("Rasterization\n");
    // Display_t display = create_display();
    // rasterize(projected_faces, &display);
    // // print_color_buffer(display);

    // printf("Saving Display\n");
    // save_display(display, "output");

    // printf("Done\n");
    // return 0;

}
