package plyfile

import (
	"ObjMem/primitives"
	"bufio"
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
)

// const (
// 	DEFAULT = 0
// )

func Parse_ply_file(filename string, vertices_cnt, faces_cnt int32) []primitives.Face_t {
	file, err := os.Open(filename)
	if err != nil {
		fmt.Printf("Failed to open file: %s\nError: %s\n", filename, err)
		panic(err)
	}
	defer file.Close()

	reader := bufio.NewReader(file)
	vertices := make([]primitives.Vertex_t, vertices_cnt)
	vertex_normals := make([]primitives.Vector_t, vertices_cnt)
	colors := make([]uint32, vertices_cnt)

	faces := make([]primitives.Face_t, faces_cnt)

	for {
		line, err := reader.ReadString('\n')
		if err == io.EOF {
			break
		}
		if err != nil {
			panic(err)
		}

		if line == "end_header\n" {
			break
		}
	}

	for i := 0; i < int(vertices_cnt); i++ {
		line, err := reader.ReadString('\n')
		if err != nil {
			panic(err)
		}
		parse_vertex_line(line, &vertices[i], &vertex_normals[i], &colors[i])
	}
	fmt.Println("Vertices parsed")

	for i := 0; i < int(faces_cnt); i++ {
		line, err := reader.ReadString('\n')
		if err != nil {
			panic(err)
		}
		faces[i] = parse_face_line(line, vertices, vertex_normals, colors, faces)
	}
	fmt.Println("Faces parsed")

	return faces
}

func parse_vertex_line(line string, v *primitives.Vertex_t, vn *primitives.Vector_t, vc *uint32) {
	parts := strings.Split(line, " ")

	x, _ := strconv.ParseFloat(parts[0], 32)
	y, _ := strconv.ParseFloat(parts[1], 32)
	z, _ := strconv.ParseFloat(parts[2], 32)

	v.X = primitives.Float_to_q8_8(float32(x))
	v.Y = primitives.Float_to_q8_8(float32(y))
	v.Z = primitives.Float_to_q8_8(float32(z))

	i, _ := strconv.ParseFloat(parts[3], 32)
	j, _ := strconv.ParseFloat(parts[4], 32)
	k, _ := strconv.ParseFloat(parts[5], 32)

	vn.I = primitives.Float_to_q8_8(float32(i))
	vn.J = primitives.Float_to_q8_8(float32(j))
	vn.K = primitives.Float_to_q8_8(float32(k))

	red, _ := strconv.Atoi(parts[6])
	red &= 0xff
	green, _ := strconv.Atoi(parts[7])
	green &= 0xff
	blue, _ := strconv.Atoi(parts[8])
	blue &= 0xff
	*vc = uint32((red << 16) | (green << 8) | blue)
	// fmt.Printf("red: %x, green: %x, blue: %x , vc: %x\n", red, green, blue, *vc)
}

func parse_face_line(line string, vertices []primitives.Vertex_t, vertex_normals []primitives.Vector_t, colors []uint32, faces []primitives.Face_t) primitives.Face_t {
	parts := strings.FieldsFunc(line, func(r rune) bool {
		return r == ' ' || r == '\n'
	})

	v1_ind, err := strconv.Atoi(parts[1])
	if err != nil {
		panic(err)
	}
	v2_ind, err := strconv.Atoi(parts[2])
	if err != nil {
		panic(err)
	}
	v3_ind, err := strconv.Atoi(parts[3])
	if err != nil {
		panic(err)
	}

	// fmt.Printf("v1_ind: %d, v2_ind: %d, v3_ind: %d\n", v1_ind, v2_ind, v3_ind)

	red_tmp := ((colors[v1_ind] >> 16) + (colors[v2_ind] >> 16) + (colors[v3_ind] >> 16)) / 3
	// fmt.Printf("red1: %x, red2: %x, red3: %x, red_tmp: %x\n", colors[v1_ind]>>16, colors[v2_ind]>>16, colors[v3_ind]>>16, red_tmp)
	red := red_tmp & 0xff
	green_tmp := ((colors[v1_ind] >> 8) + (colors[v2_ind] >> 8) + (colors[v3_ind] >> 8)) / 3
	green := green_tmp & 0xff
	blue_tmp := (colors[v1_ind] + colors[v2_ind] + colors[v3_ind]) / 3
	blue := blue_tmp & 0xff

	face_color := ((red >> 4) << 8) | ((green >> 4) << 4) | (blue >> 4)
	// fmt.Printf("red: %x, green: %x, blue: %x , face_color: %x\n", red, green, blue, uint16(face_color))
	// panic("stop")
	face := primitives.Face_t{
		V1:     vertices[v1_ind],
		V2:     vertices[v2_ind],
		V3:     vertices[v3_ind],
		Normal: primitives.NewVector_t(0.0, 0.0, 0.0),
		Color:  uint16(face_color),
	}

	return face
}


