import Primitives::*;

module LightingModule (
    // input logic [11:0] color_i,
    // input Vector_t normal,
    input Face_t face_i,
    input Vector_t light,
    // output logic [11:0] color_o
    
    output Face_t face_o
    );


    logic [15:0] mag_buf, mag, x, y, z;
    logic [15:0] red_buf, green_buf, blue_buf, red, green, blue;


    always_comb begin
        q8_8_mult(face_i.normal.i, light.i, x);
        q8_8_mult(face_i.normal.j, light.j, y);
        q8_8_mult(face_i.normal.k, light.k, z);
    
        mag_buf = x + y + z;
        mag = mag_buf[15] ? -mag_buf : mag_buf;
    
        red_buf = {4'b0, face_i.color[11:8], 8'b0};
        green_buf = {4'b0, face_i.color[7:4], 8'b0};
        blue_buf = {4'b0, face_i.color[3:0], 8'b0};
        
        q8_8_mult(mag, red_buf, red);
        q8_8_mult(mag, green_buf, green);
        q8_8_mult(mag, blue_buf, blue);

        face_o = face_i;
        face_o.color = {red[11:8], green[11:8], blue[11:8]};
    end

endmodule