package main

import (
	"ObjMem/plyfile"
	"ObjMem/primitives"
	"ObjMem/transformation"
	"fmt"
	"os"
	"path/filepath"
	"unsafe"
)

func main() {
	abs_path, err := filepath.Abs("plyfile/obj3.ply")
	if err != nil {
		panic(err)
	}
	obj_mem := plyfile.Parse_ply_file(abs_path, 264, 92)
	// make_machine_code("obj3.mem", obj_mem)
	mem_size_in_bytes := len(obj_mem) * int(unsafe.Sizeof(obj_mem[0]))
	fmt.Println("mem size:", mem_size_in_bytes, "bytes")

	transformation_matrix := [3][3]float32{{1.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		{0.0, 0.0, 1.0}}
	for i := 0; i < 3; i++ {
		fmt.Println(transformation_matrix[i])
	}

	new_matrix := transformation.NewMatrix_t(transformation_matrix)
	new_matrix.Print()
	// for i := 0; i < 3; i++ {
	// 	fmt.Println(new_matrix[i])
	// }

}

func make_machine_code(filename string, obj_mem []primitives.Face_t) {
	abs_path, err := filepath.Abs(filename)
	if err != nil {
		panic(err)
	}
	file, err := os.Create(abs_path)
	if err != nil {
		panic(err)
	}
	defer file.Close()

	for i := range obj_mem {
		face := obj_mem[i]
		face.Print_dec()
		// fmt.Println(face.Make_machine_code())
		file.WriteString(face.Make_machine_code())
		file.WriteString("\n")
	}
}
