`define IDLE 0
`define SETUP 1
`define WRITE 2
`define READ 3

module timer #(
    parameter timerbits = 8,
    parameter addrWidth = 2,
    parameter timerBaseAddr = 0
) (
    input sel,
    enable,
    reset,
    clk,
    write,
    input logic [addrWidth-1:0] addr,
    input logic [timerbits:0] wdata,
    output logic [timerbits:0] rdata,
    output logic ready,
    slverr
);

  typedef enum logic [CTR_STATUS_STATE+CTR_STATE_LEN-1:CTR_STATUS_STATE] {
    CTR_IDLE = 0,
    CTR_RUNNING = 1,
    CTR_COMPLETE = 2
  } e_ctr_state;

  logic [1:0] apb_state;

  logic [timerbits:0] prdata;
  assign rdata = prdata;

  logic pslverr;
  assign slverr = pslverr;

  logic pready;
  assign ready = pready;

  logic [timerbits:0] max_value;
  logic [timerbits:0] current_value;
  logic is_running;
  e_ctr_state state;
  // Reset is zero positive
  always @(negedge reset) begin
    apb_state = `IDLE;
  end

  always @(posedge clk) begin
    if (is_running && current_value < max_value) current_value++;

    if (addr > timerBaseAddr) begin
      case (apb_state)
        `IDLE: begin
          pready  <= 1;
          prdata  <= 0;
          pslverr <= 0;
          if (sel && !enable) apb_state = `SETUP;
        end
        `SETUP: begin
          if (sel && enable && ready) begin
            if (write) apb_state = `WRITE;
            else apb_state = `READ;
          end
        end
        `WRITE: begin
          if (sel && enable && write) begin
            case (addr)
              0: begin
                max_value = rdata;
              end
              1: begin
                is_running = rdata[0];
              end
            endcase
          end else apb_state = `IDLE;
        end
        `READ: begin
          if (sel && enable && !write) begin

          end else apb_state = `IDLE;
        end
        default: begin
          apb_state = `IDLE;
        end
      endcase
    end
  end

endmodule
