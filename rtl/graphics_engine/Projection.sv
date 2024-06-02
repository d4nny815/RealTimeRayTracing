import Primitives::*;

module ProjectionModule (
    input Face_t face_i,
    input logic [15:0] screen_width,  // unsigned 16b
    input logic [15:0] screen_height, // unsigned 16b
    input logic [15:0] screen_depth,  // unsigned 16b   

    output Face_t face_o
    );

    ProjectVertex new_v1 (
        .v_i            (face_i.v1),
        .screen_width   (screen_width),
        .screen_height  (screen_height),
        .screen_depth   (screen_depth),
        .v_o            (face_o.v1)
    );

    ProjectVertex new_v2 (
        .v_i            (face_i.v2),
        .screen_width   (screen_width),
        .screen_height  (screen_height),
        .screen_depth   (screen_depth),
        .v_o            (face_o.v2)
    );

    ProjectVertex new_v3 (
        .v_i            (face_i.v3),
        .screen_width   (screen_width),
        .screen_height  (screen_height),
        .screen_depth   (screen_depth),
        .v_o            (face_o.v3)
    );

    assign face_o.normal = face_i.normal;
    assign face_o.color = face_i.color;

endmodule

module ProjectVertex(
    input Vertex_t v_i,
    input logic [15:0] screen_width,
    input logic [15:0] screen_height,
    input logic [15:0] screen_depth,

    output Vertex_t v_o
    );

    Project_Vx new_vx (
        .x_i            (v_i.x),
        .screen_width   (screen_width),
        .x_o            (v_o.x)
    );

    Project_Vy new_vy (
        .y_i            (v_i.y),
        .screen_height  (screen_height),
        .y_o            (v_o.y)
    );

    Project_Vz new_vz (
        .z_i            (v_i.z),
        .screen_depth   (screen_depth),
        .z_o            (v_o.z)
    );

endmodule


module Project_Vx(
    input logic [15:0]  x_i,
    input logic [15:0] screen_width,

    output logic [15:0] x_o
    );

    logic [31:0] conv_screen_width, conv_x; // q16.16

    logic [31:0] shift, shift_2, buffer;
    logic [15:0] shift_int, result;

    localparam FLOAT_SCALAR = 32'h00800000; // 128.0
    localparam SPACE_TRANSLATOR = 16'h0080; // 128

    always_comb begin
        conv_x = $signed(x_i) << 8; // q8.8 to q16.16
        q16_16_mult(conv_x, FLOAT_SCALAR, shift);

        shift_int = shift[31:16];
        shift_int = $signed(shift_int) >>> 2;
        shift_int = shift_int + SPACE_TRANSLATOR;
        shift_int = shift_int >> 1;

        conv_screen_width = screen_width << 16; // u16.0 to q16.16
        shift_2 = shift_int << 16; // u16.0 to q16.16

        q16_16_mult(shift_2, conv_screen_width, buffer);
        result = buffer[31:16]; 
        result = result >> 7;

        if (result[15]) begin
            x_o = 16'd0;
        end else if (result > screen_width) begin
            x_o = screen_width;
        end else begin
            x_o = result;
        end
    end

endmodule

module Project_Vy(
    input logic [15:0] y_i,
    input logic [15:0] screen_height,

    output logic [15:0] y_o
    );

   logic [31:0] conv_screen_height, conv_y; // q16.16

    logic [31:0] shift, shift_2, buffer;
    logic [15:0] shift_int, result;

    localparam FLOAT_SCALAR = 32'h00800000; // 128.0
    localparam SPACE_TRANSLATOR = 16'h0080; // 128

    always_comb begin
        conv_y = $signed(-y_i) << 8; // q8.8 to q16.16
        // conv_y = -conv_y;
        q16_16_mult(conv_y, FLOAT_SCALAR, shift);

        shift_int = shift[31:16];
        shift_int = $signed(shift_int) >>> 2;
        shift_int = shift_int + SPACE_TRANSLATOR;
        shift_int = shift_int >> 1;

        // buffer = shift_int * screen_height;
        conv_screen_height = screen_height << 16; // u16.0 to q16.16
        shift_2 = shift_int << 16; // u16.0 to q16.16

        q16_16_mult(shift_2, conv_screen_height, buffer);
        result = buffer[31:16]; 
        result = result >> 7;

        if (result[15]) begin
            y_o = 16'd0;
        end else if (result > screen_height) begin
            y_o = screen_height;
        end else begin
            y_o = result;
        end
    end

endmodule

module Project_Vz(
    input logic [15:0] z_i,
    input logic [15:0] screen_depth,

    output logic [15:0] z_o
    );

    logic [31:0] conv_screen_depth, conv_z; // q16.16

    logic [31:0] shift, shift_2, buffer;
    logic [15:0] shift_int, result;

    localparam FLOAT_SCALAR = 32'h00800000; // 128.0
    localparam SPACE_TRANSLATOR = 16'h0080; // 128


    always_comb begin
        conv_z = $signed(z_i) << 8; // q8.8 to q16.16
        q16_16_mult(conv_z, FLOAT_SCALAR, shift);

        shift_int = shift[31:16];
        shift_int = $signed(shift_int) >>> 2;
        shift_int = shift_int + SPACE_TRANSLATOR;
        shift_int = shift_int >> 1;

        conv_screen_depth = screen_depth << 16; // u16.0 to q16.16
        shift_2 = shift_int << 16; // u16.0 to q16.16

        q16_16_mult(shift_2, conv_screen_depth, buffer);
        result = buffer[31:16]; 
        result = result >> 7;

        if (result[15]) begin
            z_o = 16'd0;
        end else if (result > screen_depth) begin
            z_o = screen_depth;
        end else begin
            z_o = result;
        end




    end



endmodule