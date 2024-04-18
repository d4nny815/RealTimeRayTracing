// main.rs
#[warn(non_snake_case)]
use rppal::spi::{Bus, SlaveSelect, Spi};
use k_board::keyboard::Keyboard;
use k_board::keys::Keys;

mod rtu_api;
use rtu_api::{HeaderType, TransmitData};

use crate::rtu_api::{CameraPos, Frame, Polygon};


const WREN: u8 = 0x06;

fn main() {
    test_mode();
}


fn test_mode() {
    let mut spi = Spi::new(Bus::Spi0, SlaveSelect::Ss0, 8_000_000, rppal::spi::Mode::Mode0).unwrap();

    println!("Press Up to send a frame");
    println!("Press Down to send camera position");
    println!("Press Left to send a polygon");
    println!("Press Right to send init");
    
    use std::mem;
    println!("{}", mem::size_of::<TransmitData>());
    println!("{}", mem::size_of::<Frame>());
    println!("{}", mem::size_of::<CameraPos>());
    println!("{}", mem::size_of::<Polygon>());

    let mut camera = rtu_api::CameraPos::new(0.0, 0.0, 0.0);
    let mut keyboard = Keyboard::new();
    loop {
        let key = keyboard.read_key();
        match key {
            Keys::Up => {
                let data = TransmitData::new_frame(0, 0, 0x0F0F);
                send_rtu(&mut spi, data);
            }
            Keys::Down => {
                camera.move_camera(1.0, 0.0, 0.0);
                let data = TransmitData::new_cam_pos(camera.x, camera.y, camera.z);
                camera.print_pos();
                send_rtu(&mut spi, data);
            }
            Keys::Left => {
                let data = TransmitData::new_polygon(
                    rtu_api::Vertex::new(0.0, 0.0, 0.0),
                    rtu_api::Vertex::new(0.0, 0.0, 0.0),
                    rtu_api::Vertex::new(0.0, 0.0, 0.0),
                    0x0F0F,
                );
                send_rtu(&mut spi, data);
            }
            Keys::Right => {
                let data = TransmitData::new_init();
                send_rtu(&mut spi, data);
            }
            _ => {}
        }
    }
}


fn send_rtu(spi: &mut Spi, data: TransmitData) {
    if let Some(header) = HeaderType::from_u8(data.header) {
        spi.write(&[WREN]).unwrap();
        let header_bytes: &[u8] = bytemuck::bytes_of(&data.header);
        match header {
            HeaderType::Frame => {
                println!("Sending Frame");
                let frame_bytes: &[u8] = bytemuck::bytes_of(&data.frame);
                let data_bytes = [header_bytes, frame_bytes].concat();
                spi.write(&data_bytes).unwrap();
                println!("{:?}", data_bytes);
            }
            HeaderType::Init => {
                println!("Sending Init");
                spi.write(header_bytes).unwrap();
                println!("{:?}", header_bytes);
            }
            HeaderType::Polygon => {
                println!("Sending Polygon");
                let polygon_bytes: &[u8] = bytemuck::bytes_of(&data.polygon);
                let data_bytes = [header_bytes, polygon_bytes].concat();
                spi.write(&data_bytes).unwrap();
                println!("{:?}", data_bytes);
            }
            HeaderType::CameraPos => {
                println!("Sending CameraPos");
                let camera_pos_bytes: &[u8] = bytemuck::bytes_of(&data.camera_pos);
                let data_bytes = [header_bytes, camera_pos_bytes].concat();
                spi.write(&data_bytes).unwrap();
                println!("{:?}", data_bytes);
            }
        }
    }
}
