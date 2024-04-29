module ResetController (
    input clk,
    output logic rst
    );

    logic reset_cnt, internal_rst, internal_up;
    logic [3:0] counter;

    typedef enum logic [1:0] {
        INIT,
        RESET,
        IDLE
    } state_t;
    state_t state, next_state;

    always_ff @(posedge clk) begin
        state <= next_state;
    end

    always_comb begin 
        rst = 0; internal_rst = 0; internal_up = 0;
        case (state)
            INIT: begin
                next_state = RESET;
                internal_rst = 1;
            end
            RESET: begin
                rst = 1;
                internal_up = 1;
                if (reset_cnt)
                    next_state = IDLE;
                else 
                    next_state = RESET;
            end
            IDLE: begin
                next_state = IDLE;
            end
        default: next_state = INIT;
        endcase
    end

    

    always_ff @(posedge clk) begin
        if (internal_rst) begin
            counter <= 0;
        end else if (internal_up) begin
            counter <= counter + 1;
        end
    end

    assign reset_cnt = &counter;
endmodule