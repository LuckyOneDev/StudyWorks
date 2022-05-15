module timer
#(
    parameter timerBaseAddr = 0,
    parameter timerbits = 8,
    parameter addrWidth = 2
)
(
    input sel,
    enable,
    reset,
    clk,
    write,
    input logic [addrWidth-1:0] addr,
    input logic [timerbits-1:0] wdata,
    output logic [timerbits-1:0] rdata,
    output logic ready,
    slverr
);

  localparam STATE_IDLE = 0;
  localparam STATE_SETUP = 1;
  localparam STATE_WRITE = 2;
  localparam STATE_READ = 3;

  localparam CTR_STATUS_ADDR = timerBaseAddr;
  localparam CTR_GOAL_ADDR = timerBaseAddr + 1;
  localparam CTR_CURR_ADDR = timerBaseAddr + 2;

  localparam CTR_STATUS_START = 0;
  localparam CTR_STATUS_STOP = 1;
  localparam CTR_STATUS_STATE = 2;
  localparam CTR_STATE_LEN = 2;

  typedef enum logic [CTR_STATUS_STATE+CTR_STATE_LEN-1:CTR_STATUS_STATE] {
    CTR_IDLE = 0,
    CTR_RUNNING = 1,
    CTR_COMPLETE = 2
  } e_ctr_state;

  logic [1:0] apb_state;
  
  logic [timerbits:0] current_value;
  logic [timerbits:0] max_value;

  logic [1:0] state_bits;

  e_ctr_state state;

  // Reset is zero positive
  always @(negedge reset) begin
    apb_state <= STATE_IDLE;
  end

  always @(posedge clk) begin
    if (state_bits[CTR_STATUS_START] && !state_bits[CTR_STATUS_STOP] && (current_value < max_value) ) current_value++;

    if (addr >= timerBaseAddr && addr <= timerBaseAddr + CTR_STATE_LEN) begin
      case (apb_state)
        STATE_IDLE: begin
          rdata  <= 0;
          slverr <= 0;
          state_bits <= 0;
        if (sel && !enable) apb_state = STATE_SETUP;
        end
        STATE_SETUP: begin
          if (sel && enable) begin
            ready <= 1;
            if (write) apb_state = STATE_WRITE;
            else apb_state = STATE_READ;
          end
        end
        // WRITE
        STATE_WRITE: begin
          if (sel && enable && write) begin
            case (addr)
              CTR_STATUS_ADDR: begin
                state_bits <= rdata;
              end
              CTR_GOAL_ADDR: begin
                max_value <= rdata;
              end
              CTR_CURR_ADDR: begin
                slverr <= 1;
                //current_value <= rdata;
              end
            endcase
          end else apb_state = STATE_IDLE;
        end
        // READ
        STATE_READ: begin
          if (sel && enable && !write) begin
            case (addr)
              CTR_STATUS_ADDR: begin
                rdata <= state_bits;
              end
              CTR_GOAL_ADDR: begin
                rdata <= max_value;
              end
              CTR_CURR_ADDR: begin
                rdata <= current_value;
              end
            endcase
          end else apb_state = STATE_IDLE;
        end
        default: begin
          apb_state = STATE_IDLE;
        end
      endcase
    end
  end

endmodule
