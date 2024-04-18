module FrameBufferController(
    input clk,
    input rst
    
    );

    typedef enum logic [2:0] {
        INIT        = 3'b000,
        LOAD_OBJS   = 3'b001,
        LOAD_CAM    = 3'b010,
        RTU_TO_FB   = 3'b011,
        CAM_TO_RTU  = 3'b100,
        OBJ_TO_RTU  = 3'b101
    } state_t;

    state_t state, next_state;

    always_ff @ (posedge clk) begin
        if (rst) begin
            state <= INIT;
        end else begin
            state <= next_state;
        end
    end

    always_comb begin
        next_state = state;
        case (state)
            INIT: begin
                next_state = LOAD_OBJS;
            end
            LOAD_OBJS: begin
                next_state = LOAD_CAM;
            end
            LOAD_CAM: begin
                next_state = RTU_TO_FB;
            end
            RTU_TO_FB: begin
                next_state = CAM_TO_RTU;
            end
            CAM_TO_RTU: begin
                next_state = OBJ_TO_RTU;
            end
            OBJ_TO_RTU: begin
                next_state = RTU_TO_FB;
            end
            
            default: next_state = INIT;
        endcase
    end




endmodule