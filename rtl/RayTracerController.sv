module RayTracerController (
    input clk,

    input [1:0] itf_packet_type,
    input itf_empty,

    output logic fb_we,
    output logic fifo_re
    );

    typedef enum logic [2:0] {
        INIT,
        IDLE,
        HEADER,
        WRITE_FB
    } state_t;
    state_t state, next_state;

    always_ff @(posedge clk) begin
        state <= next_state;
    end

    always_comb begin
        fb_we = 0; fifo_re = 0;
    
        case (state)
            INIT: begin
                next_state = IDLE;
            end

            IDLE: begin
                if (itf_packet_type != 2'b00) begin
                    next_state = HEADER;
                end else
                    next_state = IDLE;
            end

            HEADER: begin
                if (itf_empty) begin
                    fifo_re = 0;
                    next_state = HEADER;
                end else begin
                    fifo_re = 1;
                    next_state = WRITE_FB;
                end
            end

            WRITE_FB: begin
                fb_we = 1;
                if (itf_empty) begin
                    next_state = IDLE;
                end else begin
                    next_state = HEADER;
                end
            end

            default: next_state = INIT;
        endcase
    end

endmodule