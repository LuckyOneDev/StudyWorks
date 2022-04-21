module timerVrf ();
	typedef enum logic[1:0] {
		IDLE = 0,
		RUNNING = 1,
		COMPLETE = 2
	} ctr_state;

	localparam addrWidth = 2;
	localparam dataWidth = 8;

  localparam timerBaseAddr = 0;
	localparam CTR_STATUS_ADDR = timerBaseAddr;
	localparam CTR_GOAL_ADDR = timerBaseAddr + 1;
	localparam CTR_CURR_ADDR = timerBaseAddr + 2;

	localparam CTR_STATUS_START = 0;
	localparam CTR_STATUS_STOP = 1;
	localparam CTR_STATUS_STATE = 2; //bits 2 and 3;

	logic[addrWidth-1:0] paddr;
	logic pwrite;
	logic psel;
	logic penable;
	logic[dataWidth-1:0] pwdata;
	logic[dataWidth-1:0] prdata;
	logic pready;
	logic pslverr;
	logic presetn;

	task exchangeData(
		input enum logic {READ=0, WRITE=1} exchMode,
		input logic[addrWidth-1:0] deviceAddr,
		inout logic[dataWidth-1:0] data,
		output logic err
	);
		begin
			// IDLE -> SETUP
			paddr <= deviceAddr;
			psel <= 1;
			pwrite <= exchMode;
			if (exchMode == WRITE) pwdata <= data;
			@(posedge clk);
			// SETUP -> ACCESS
			penable <= 1;
			@(posedge clk);

			while (!pready) @(posedge clk);
			// ACCESS -> IDLE
			if(exchMode == READ) data <= prdata;
			err <= pslverr;
			penable <= 0;
			psel <= 0;
			@(posedge clk);
		end
	endtask

//	TESTS:
//	- write + read on wrong addr
// 	- write + read without psel
// 	- w + r without enable
//	- w + r with X on pwrite (this cannot happen but whatever)
//	- start a timer and access current counter + state
//	- start a timer and w8 until it ends (state COMPLETE)
//	- restart a timer and access curr counter + state
//	- pause + read curr 2 times (should be the same)

	initial begin
		$dumpfile("test.vcd");
		$dumpvars(0, timerVrf);
	end

  logic clk = 0;
	always
		#1 clk = ~clk;
endmodule