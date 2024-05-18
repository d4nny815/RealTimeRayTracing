fn main() {

    let nums = [0.75, 10.5, -1.125, 0.125, 0.875, 0.5, 0.0];

    for num in nums.iter() {
        let fixed: i16 = dec_to_16bit_fixed_point(*num);
        print_16bit_fixed_point(fixed);
    }

    // let dec: f32 = 0.75;
    // let fixed: i16 = dec_to_16bit_fixed_point(dec);
    // print_16bit_fixed_point(fixed);
}

fn dec_to_16bit_fixed_point(dec: f32) -> i16 {
    (dec * 256.0) as i16
}


// print in decimal format
fn print_16bit_fixed_point(fixed: i16) {
    println!("Fixed point: {}", fixed);
    // println!("Binary: {:016b}", fixed);
    println!("Hex: {:04x}", fixed);
    println!("Decimal: {}", fixed as f32 / 256.0);
    println!();
}
