package primitives

import (
	"fmt"
	"math"
)

func Uint16_to_q8_8(x uint16) int16 {
	return int16(x << 8)
}

func Float_to_q16_16(f float32) int32 {
	return int32(f * 65536.0)
}

func Float_to_q8_8(f float32) int16 {
	// fmt.Printf("f: %f, f*256: %f, uint16(f*256): %d\n", f, f*256.0, uint16(f*256.0))
	return int16(f * 256.0)
}

func Q8_8_to_float(q int16) float32 {
	return float32(q) / 256.0
}

func Q8_8_mult(q1, q2 int16) int16 {
	sign1 := q1 >> 15
	sign2 := q2 >> 15

	if sign1 == 0 && sign2 == 0 {
		op1 := Q8_8_to_float(q1)
		op2 := Q8_8_to_float(q2)
		return Float_to_q8_8(op1 * op2)
	} else if sign1 == 0 && sign2 == 1 {
		op1 := Q8_8_to_float(q1)
		op2 := Q8_8_to_float(q2)
		return Float_to_q8_8(op1 * -op2)
	} else if sign1 == 1 && sign2 == 0 {
		op1 := Q8_8_to_float(q1)
		op2 := Q8_8_to_float(q2)
		return Float_to_q8_8(-op1 * op2)
	} else {
		op1 := Q8_8_to_float(q1)
		op2 := Q8_8_to_float(q2)
		return Float_to_q8_8(-op1 * -op2)
	}
}

type Vertex_t struct {
	X int16 // signed fixed point q8.8
	Y int16 // signed fixed point q8.8
	Z int16 // signed fixed point q8.8
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
	fmt.Printf("(%f, %f, %f)\n", float32(x)/256.0, float32(y)/256.0, float32(z)/256.0)
}

// func (v *Vertex_t) scalar(scalar float32) {
// 	v.X = Float_to_q8_8(Q8_8_to_float(v.X) * scalar)
// 	v.Y = Float_to_q8_8(Q8_8_to_float(v.Y) * scalar)
// 	v.Z = Float_to_q8_8(Q8_8_to_float(v.Z) * scalar)
// }

func (v Vertex_t) Dot_product(v2 Vector_t) int16 {
	return Q8_8_mult(v.X, v2.I) + Q8_8_mult(v.Y, v2.J) + Q8_8_mult(v.Z, v2.K)
}

func (v Vertex_t) Make_machine_code() string {
	return fmt.Sprintf("%04x%04x%04x", uint16(v.X), uint16(v.Y), uint16(v.Z))
}

type Vector_t struct {
	I int16 // signed fixed point q8.8
	J int16 // signed fixed point q8.8
	K int16 // signed fixed point q8.8
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
	fmt.Printf("<%f, %f, %f>\n", float32(i)/256.0, float32(j)/256.0, float32(k)/256.0)
}

func (v Vector_t) Make_machine_code() string {
	return fmt.Sprintf("%04x%04x%04x", uint16(v.I), uint16(v.J), uint16(v.K))
}

func Get_normal(v1, v2, v3 Vertex_t) Vector_t {
	vec1 := NewVector_t(Q8_8_to_float(v2.X)-Q8_8_to_float(v1.X), Q8_8_to_float(v2.Y)-Q8_8_to_float(v1.Y), Q8_8_to_float(v2.Z)-Q8_8_to_float(v1.Z))
	vec2 := NewVector_t(Q8_8_to_float(v3.X)-Q8_8_to_float(v1.X), Q8_8_to_float(v3.Y)-Q8_8_to_float(v1.Y), Q8_8_to_float(v3.Z)-Q8_8_to_float(v1.Z))

	tmp := vec1.cross_product(vec2)
	return tmp.Normalize()
}

func (v Vector_t) cross_product(v2 Vector_t) Vector_t {
	var vec Vector_t

	vec.I = Q8_8_mult(v.J, v2.K) - Q8_8_mult(v.K, v2.J)
	vec.J = Q8_8_mult(v.K, v2.I) - Q8_8_mult(v.I, v2.K)
	vec.K = Q8_8_mult(v.I, v2.J) - Q8_8_mult(v.J, v2.I)

	return vec
}

func (v Vector_t) Normalize() Vector_t {
	mag := v.magnitude()
	i := Q8_8_to_float(v.I) / mag
	j := Q8_8_to_float(v.J) / mag
	k := Q8_8_to_float(v.K) / mag

	return NewVector_t(i, j, k)
}

func (v Vector_t) magnitude() float32 {
	i := float64(Q8_8_to_float(v.I))
	j := float64(Q8_8_to_float(v.J))
	k := float64(Q8_8_to_float(v.K))

	return float32(math.Sqrt(i*i + j*j + k*k))
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
	fmt.Printf("\tv1: ")
	f.V1.Print_hex()
	fmt.Printf("\tv2: ")
	f.V2.Print_hex()
	fmt.Printf("\tv3: ")
	f.V3.Print_hex()
	fmt.Printf("\tnormal: ")
	f.Normal.Print_hex()
	fmt.Printf("\tred: %x, green: %x, blue: %x\n", f.Color>>8, (f.Color>>4)&0xf, f.Color&0xf)
	fmt.Printf("}\n")
}

func (f Face_t) Print_dec() {
	fmt.Printf("Face: {\n")
	fmt.Printf("\tv1: ")
	f.V1.Print_dec()
	fmt.Printf("\tv2: ")
	f.V2.Print_dec()
	fmt.Printf("\tv3: ")
	f.V3.Print_dec()
	fmt.Printf("\tnormal: ")
	f.Normal.Print_dec()
	fmt.Printf("\tred: %x, green: %x, blue: %x\n", f.Color>>8, (f.Color>>4)&0xf, f.Color&0xf)
	fmt.Printf("}\n")
}

func (f Face_t) Make_machine_code() string {
	return fmt.Sprintf("%s%s%s%s%03x", f.V1.Make_machine_code(), f.V2.Make_machine_code(), f.V3.Make_machine_code(), f.Normal.Make_machine_code(), f.Color)
}
