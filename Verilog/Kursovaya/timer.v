`define IDLE 0
`define SETUP 1
`define WRITE 2
`define READ 3

module apb_timer 
#
(
    parameter timerbits = 8
)
(
    input sel, enable, reset, clk, write, 
    input wire addr, 
    input wire[timerbits:0] wdata,
    output wire[timerbits:0] rdata,
    output wire ready, slverr
);
reg[1:0] apb_state;

reg[timerbits:0] prdata;
assign rdata = prdata;

reg pslverr;
assign slverr = pslverr;

reg pready;
assign ready = pready;

reg[timerbits:0] max_value = 0;
reg[timerbits:0] current_value = 0;
reg continue = 0;

// Reset is zero positive
always @(negedge reset) begin
    apb_state = `IDLE;
end

always @(posedge clk) begin
    if (continue && current_value < max_value) current_value++;

    case (apb_state)
    `IDLE: begin
        pready <= 1;
        prdata <= 0;
        pslverr <= 0;
        if (sel && !enable) apb_state = `SETUP;
    end
    `SETUP: begin
        if (sel && enable && ready) begin
            if (write) apb_state = `WRITE; else apb_state = `READ;
        end
    end
    `WRITE: begin
        if (sel && enable && write) begin 
            case (addr)
                0: begin
                    max_value = rdata;
                end
                1: begin
                    continue = rdata[0];
                end
            endcase
        end 
        else apb_state = `IDLE;
    end
    `READ: begin
        if (sel && enable && !write ) begin 
            if (continue) pslverr = 1; else 
            begin
                prdata = current_value;
            end
        end 
        else apb_state = `IDLE;
    end
    default: begin
        apb_state = `IDLE;
    end
    endcase
end

endmodule