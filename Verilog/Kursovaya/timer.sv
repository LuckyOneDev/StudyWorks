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

  logic [1:0] apb_state;
  
  logic [timerbits:0] current_value;
  logic [timerbits:0] max_value;

  localparam CTR_IDLE = 0;
  localparam CTR_RUNNING = 1;
  localparam CTR_COMPLETE = 2;

  logic [3:0] state_bits;

  task write_transition();
   if (sel && enable) begin
    case (addr)
        CTR_STATUS_ADDR: begin
          state_bits[CTR_STATUS_START] <= wdata[0];
          state_bits[CTR_STATUS_STOP] <= wdata[1];
          state_bits[CTR_STATUS_STATE+:CTR_STATE_LEN] <= CTR_RUNNING;
        end
        CTR_GOAL_ADDR: begin
           max_value <= wdata;
        end
        CTR_CURR_ADDR: begin
          slverr <= 1;
          //current_value <= rdata;
        end
     endcase
    end else apb_state = STATE_IDLE;
  endtask

task read_transition();
  if (sel && enable) begin
   case (addr)
      CTR_STATUS_ADDR: begin
        rdata <= state_bits;
        if (rdata[CTR_STATUS_START] == 0) current_value <= 0;
      end
      CTR_GOAL_ADDR: begin
        rdata <= max_value;
      end
      CTR_CURR_ADDR: begin
        rdata <= current_value;
      end
    endcase
  end else apb_state = STATE_IDLE;
endtask

  // Reset is zero positive
  always @(negedge reset) begin
    apb_state <= STATE_IDLE;
    current_value <= 0;
    max_value <= 0;
    state_bits <= 0;
  end

  always @(posedge clk) begin

    if (state_bits[CTR_STATUS_STATE+:CTR_STATE_LEN] == CTR_RUNNING && current_value > max_value) state_bits[CTR_STATUS_STATE+:CTR_STATE_LEN] <= CTR_COMPLETE;
    if (!state_bits[CTR_STATUS_STOP] && state_bits[CTR_STATUS_START] && current_value < max_value) current_value++;

    $display("%d %d", current_value, max_value);

    if (addr >= timerBaseAddr && addr <= timerBaseAddr + 2) begin
      case (apb_state)
        STATE_IDLE: begin
          rdata  <= 0;
          slverr <= 0;
          ready <= 0;
          if (sel) apb_state = STATE_SETUP;
        end
        STATE_SETUP: begin
          if (sel && enable) begin
            if (write) begin
              apb_state = STATE_WRITE;
            end 
            else begin 
              apb_state = STATE_READ;
            end
          end
        end
        // WRITE
        STATE_WRITE: begin
          ready <= 1;
          write_transition();
        end
        // READ
        STATE_READ: begin
          ready <= 1;
          read_transition();
        end
        default: begin
          apb_state = STATE_IDLE;
        end
      endcase
    end
  end

endmodule
