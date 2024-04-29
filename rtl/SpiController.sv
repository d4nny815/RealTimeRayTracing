
module SPIController (
    input logic clk,
    input logic cs_n,
    input logic [1:0] packet_type,
    input logic counter_eq,
    input logic data_reg_rdy,
    

    output logic clr,
    output logic header_we,
    output logic data_we,
    output logic fifo_we,

    output logic cntr_clr,
    output logic cntr_up,
    output logic [1:0] cntr_sel
    );
    

    typedef enum logic [1:0] {
        INIT,
        IDLE,
        HEADER,
        DATA
    } state_t;
    state_t state, next_state;

    always_ff @(posedge clk or posedge cs_n) begin
        if (cs_n) begin
            state <= IDLE;
        end else begin
            state <= next_state;
        end
    end

    always_comb begin
        clr = 0; cntr_sel = 2'b00; cntr_up = 0;  cntr_clr = 0;
        header_we = 0; data_we = 0; fifo_we = 0;
        case (state)
            INIT: begin
                next_state = IDLE;
                clr = 1; cntr_clr = 1;
            end

            IDLE: begin
                cntr_up = 0;
                if (!cs_n) begin
                    next_state = HEADER;
                    clr = 1;
                    cntr_clr = 1;
                end
                else 
                    next_state = IDLE;
            end

            HEADER: begin
                cntr_up = 1;
                cntr_sel = 2'b00;
                header_we = 1;
                if (counter_eq) begin
                    next_state = DATA;
                    cntr_clr = 1;
                end
                else
                    next_state = HEADER;
            end

            DATA: begin
                cntr_up = 1;
                cntr_sel = packet_type;
                fifo_we = data_reg_rdy;
                data_we = 1;
                if (counter_eq) begin
                    cntr_clr = 1;
                    header_we = 1;
                    next_state = IDLE;
                end
                else begin
                    next_state = DATA;
                end
            end

//            HEADER2: begin
//                cntr_sel = 3'b100;
//                cntr_up = 1;
//                header_we = 1;
//                if (counter_eq) begin
//                    next_state = DATA;
//                    cntr_clr = 1;
//                end else
//                    next_state = HEADER2;
//            end
            
            default: next_state = INIT;
        endcase
    end


endmodule