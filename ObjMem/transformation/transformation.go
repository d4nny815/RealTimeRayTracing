package transformation

import (
	"ObjMem/primitives"
	"fmt"
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

func matrix_transpose(matrix [3][3]float32) [3][3]float32 {
	tmp := [3][3]float32{{matrix[0][0], matrix[1][0], matrix[2][0]},
		{matrix[0][1], matrix[1][1], matrix[2][1]},
		{matrix[0][2], matrix[1][2], matrix[2][2]}}

	return tmp
}

func (m Matrix_t) Print() {
	fmt.Println("Matrix: {")
	m.ROW1.Print_dec()
	m.ROW2.Print_dec()
	m.ROW3.Print_dec()
	fmt.Println("}")
}
