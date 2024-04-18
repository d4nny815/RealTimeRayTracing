// rtu_api.rs
use bytemuck::{Pod, Zeroable};

#[derive(Clone, Copy, Pod, Zeroable)]
#[repr(C, packed)]
pub struct CameraPos {
    pub x: f32,
    pub y: f32,
    pub z: f32,
}

impl CameraPos {
    pub fn new(x: f32, y: f32, z: f32) -> Self {
        Self { x, y, z }
    }

    pub fn move_camera(&mut self, x: f32, y: f32, z: f32) {
        self.x += x;
        self.y += y;
        self.z += z;
    }

    pub fn print_pos(&self) {
        let x = self.x;
        let y = self.y;
        let z = self.z;
        println!("Camera Position: x: {}, y: {}, z: {}", x, y, z);
    }
}

#[derive(Clone, Copy, Pod, Zeroable)]
#[repr(C, packed)]
pub struct Frame {
    pub v_pixel: u8,
    pub h_pixel: u8,
    pub color: u16,
}

impl Frame {
    fn new(v_pixel: u8, h_pixel: u8, color: u16) -> Self {
        Self {
            v_pixel,
            h_pixel,
            color,
        }
    }
}

#[derive(Clone, Copy, Pod, Zeroable)]
#[repr(C, packed)]
pub struct Vertex {
    x: f32,
    y: f32,
    z: f32,
}

impl Vertex {
    pub fn new(x: f32, y: f32, z: f32) -> Self {
        Self { x, y, z }
    }
}

#[derive(Clone, Copy, Pod, Zeroable)]
#[repr(C, packed)]
pub struct Vector {
    x: f32,
    y: f32,
    z: f32,
}

impl Vector {
    pub fn new(x: f32, y: f32, z: f32) -> Self {
        Self { x, y, z }
    }

    pub fn get_normal_vec(vertex1: Vertex, vertex2: Vertex, vertex3: Vertex) -> Self {
        let vec1 = Vector::new(vertex2.x - vertex1.x, vertex2.y - vertex1.y, vertex2.z - vertex1.z);
        let vec2 = Vector::new(vertex3.x - vertex1.x, vertex3.y - vertex1.y, vertex3.z - vertex1.z);
        let x = vec1.y * vec2.z - vec1.z * vec2.y;
        let y = vec1.z * vec2.x - vec1.x * vec2.z;
        let z = vec1.x * vec2.y - vec1.y * vec2.x;
        Vector::new(x, y, z)
    }
}

#[derive(Clone, Copy, Pod, Zeroable)]
#[repr(C, packed)]
pub struct Polygon {
    vertex1: Vertex,
    vertex2: Vertex,
    vertex3: Vertex,
    normal: Vector,
    color: u16,
}

impl Polygon {
    pub fn new(vertex1: Vertex, vertex2: Vertex, vertex3: Vertex, color: u16) -> Self {
        let normal = Vector::get_normal_vec(vertex1, vertex2, vertex3);
        Self {
            vertex1,
            vertex2,
            vertex3,
            normal,
            color,
        }
    }
    pub fn new_default() -> Self {
        Self {
            vertex1: Vertex::new(0.0, 0.0, 0.0),
            vertex2: Vertex::new(0.0, 0.0, 0.0),
            vertex3: Vertex::new(0.0, 0.0, 0.0),
            normal: Vector::new(0.0, 0.0, 0.0),
            color: 0x0F0F,
        }
    }
}

#[derive(Clone, Copy, Pod, Zeroable)]
#[repr(C, packed)]
pub struct TransmitData {
    pub header: u8,
    pub frame: Frame,
    pub camera_pos: CameraPos,
    pub polygon: Polygon,
}

impl TransmitData {
    pub fn new_init() -> Self {
        Self {
            header: HeaderType::Init as u8,
            frame: Frame::new(0, 0, 0),
            camera_pos: CameraPos::new(0.0, 0.0, 0.0),
            polygon: Polygon::new_default(),
        }
    }

    pub fn new_frame(v_pixel: u8, h_pixel: u8, color: u16) -> Self {
        Self {
            header: HeaderType::Frame as u8,
            frame: Frame::new(v_pixel, h_pixel, color),
            camera_pos: CameraPos::new(0.0, 0.0, 0.0),
            polygon: Polygon::new_default(),
        }
    }

    pub fn new_cam_pos(x: f32, y: f32, z: f32) -> Self {
        Self {
            header: HeaderType::CameraPos as u8,
            frame: Frame::new(0, 0, 0),
            camera_pos: CameraPos::new(x, y, z),
            polygon: Polygon::new_default(),
        }
    }

    pub fn new_polygon(vertex1: Vertex, vertex2: Vertex, vertex3: Vertex, color: u16) -> Self {
        Self {
            header: HeaderType::Polygon as u8,
            frame: Frame::new(0, 0, 0),
            camera_pos: CameraPos::new(0.0, 0.0, 0.0),
            polygon: Polygon::new(vertex1, vertex2, vertex3, color),
        }
    }
}


pub enum HeaderType {
    Init = 0x00,
    Frame = 0x01,
    Polygon = 0x02,
    CameraPos = 0x03,
}

impl HeaderType {
    pub fn from_u8(value: u8) -> Option<Self> {
        match value {
            0x00 => Some(Self::Init),
            0x01 => Some(Self::Frame),
            0x02 => Some(Self::Polygon),
            0x03 => Some(Self::CameraPos),
            _ => None,
        }
    }
}