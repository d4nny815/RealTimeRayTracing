package transformation

import (
	"ObjMem/primitives"
	"fmt"
)

const (
	MAT_DIM = 3
)

type Matrix_t struct {
	ROW1 primitives.Vector_t
	ROW2 primitives.Vector_t
	ROW3 primitives.Vector_t
}

func NewMatrix_t(matrix [3][3]float32) Matrix_t {
	return Matrix_t{convert_to_vector(matrix[0]), convert_to_vector(matrix[1]), convert_to_vector(matrix[2])}
}

func convert_to_vector(matrix [3]float32) primitives.Vector_t {
	return primitives.NewVector_t(matrix[0], matrix[1], matrix[2])
}

// func matrix_transpose(matrix [3][3]float32) [3][3]float32 {
// tmp := [3][3]float32{{matrix[0][0], matrix[1][0], matrix[2][0]},
// {matrix[0][1], matrix[1][1], matrix[2][1]},
// {matrix[0][2], matrix[1][2], matrix[2][2]}}
//
// return tmp
// }

func (m Matrix_t) Print() {
	fmt.Println("Matrix: {")
	m.ROW1.Print_dec()
	m.ROW2.Print_dec()
	m.ROW3.Print_dec()
	fmt.Println("}")
}

func (m Matrix_t) Transform_face(f primitives.Face_t) primitives.Face_t {
	var f_ret primitives.Face_t

	f_ret.V1 = m.Transform_vertex(f.V1)
	f_ret.V2 = m.Transform_vertex(f.V2)
	f_ret.V3 = m.Transform_vertex(f.V3)

	f_ret.Normal = primitives.Get_normal(f_ret.V1, f_ret.V2, f_ret.V3)

	f_ret.Color = f.Color

	return f_ret

}

func (m Matrix_t) Transform_vertex(v primitives.Vertex_t) primitives.Vertex_t {
	var v_ret primitives.Vertex_t

	v_ret.X = v.Dot_product(m.ROW1)
	v_ret.Y = v.Dot_product(m.ROW2)
	v_ret.Z = v.Dot_product(m.ROW3)

	return v_ret
}
