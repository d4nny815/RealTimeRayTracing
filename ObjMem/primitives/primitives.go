package primitives

import (
	"fmt"
)

func Float_to_q8_8(f float32) uint16 {
	// fmt.Printf("f: %f, f*256: %f, uint16(f*256): %d\n", f, f*256.0, uint16(f*256.0))
	return uint16(f * 256.0)
}

type Vertex_t struct {
	X uint16 // signed fixed point q8.8
	Y uint16 // signed fixed point q8.8
	Z uint16 // signed fixed point q8.8
}

func NewVertex_t(x, y, z float32) Vertex_t {
	return Vertex_t{Float_to_q8_8(x), Float_to_q8_8(y), Float_to_q8_8(z)}
}

func (v Vertex_t) Print_hex() {
	fmt.Printf("x: %x, y: %x, z: %x\n", v.X, v.Y, v.Z)
}

func (v Vertex_t) Print_dec() {
	x := int16(v.X)
	y := int16(v.Y)
	z := int16(v.Z)
	fmt.Printf("x: %f, y: %f, z: %f\n", float32(x)/256.0, float32(y)/256.0, float32(z)/256.0)
}

func (v Vertex_t) Make_machine_code() string {
	return fmt.Sprintf("%04x%04x%04x", v.X, v.Y, v.Z)
}

type Vector_t struct {
	I uint16 // signed fixed point q8.8
	J uint16 // signed fixed point q8.8
	K uint16 // signed fixed point q8.8
}

func NewVector_t(i, j, k float32) Vector_t {
	return Vector_t{Float_to_q8_8(i), Float_to_q8_8(j), Float_to_q8_8(k)}
}

func (v Vector_t) Print_hex() {
	fmt.Printf("i: %x, j: %x, k: %x\n", v.I, v.J, v.K)
}

func (v Vector_t) Print_dec() {
	i := int16(v.I)
	j := int16(v.J)
	k := int16(v.K)
	fmt.Printf("i: %f, j: %f, k: %f\n", float32(i)/256.0, float32(j)/256.0, float32(k)/256.0)
}

func (v Vector_t) Make_machine_code() string {
	return fmt.Sprintf("%04x%04x%04x", v.I, v.J, v.K)
}

type Face_t struct {
	V1     Vertex_t
	V2     Vertex_t
	V3     Vertex_t
	Normal Vector_t
	Color  uint16
}

func NewFace_t(v1, v2, v3 Vertex_t, normal Vector_t, color uint16) Face_t {
	return Face_t{v1, v2, v3, normal, color}
}

func (f Face_t) Print_hex() {
	fmt.Printf("Face: {\n")
	fmt.Printf("v1: ")
	f.V1.Print_hex()
	fmt.Printf("v2: ")
	f.V2.Print_hex()
	fmt.Printf("v3: ")
	f.V3.Print_hex()
	fmt.Printf("normal: ")
	f.Normal.Print_hex()
	fmt.Printf("red: %x, green: %x, blue: %x\n", f.Color>>8, (f.Color>>4)&0xf, f.Color&0xf)
	fmt.Printf("}\n")
}

func (f Face_t) Print_dec() {
	fmt.Printf("Face: {\n")
	fmt.Printf("v1: ")
	f.V1.Print_dec()
	fmt.Printf("v2: ")
	f.V2.Print_dec()
	fmt.Printf("v3: ")
	f.V3.Print_dec()
	fmt.Printf("normal: ")
	f.Normal.Print_dec()
	fmt.Printf("red: %x, green: %x, blue: %x\n", f.Color>>8, (f.Color>>4)&0xf, f.Color&0xf)
	fmt.Printf("}\n")
}

func (f Face_t) Make_machine_code() string {
	return fmt.Sprintf("%s%s%s%s%04x", f.V1.Make_machine_code(), f.V2.Make_machine_code(), f.V3.Make_machine_code(), f.Normal.Make_machine_code(), f.Color)
}
