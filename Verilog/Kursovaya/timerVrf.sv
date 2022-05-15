module timerVrf ();
  localparam addrWidth = 32;
  localparam dataWidth = 8;

  localparam timerBaseAddr = 0;
  localparam CTR_STATUS_ADDR = timerBaseAddr;
  localparam CTR_GOAL_ADDR = timerBaseAddr + 1;
  localparam CTR_CURR_ADDR = timerBaseAddr + 2;

  localparam CTR_STATUS_START = 0;
  localparam CTR_STATUS_STOP = 1;
  localparam CTR_STATUS_STATE = 2;  //bits 2 and 3;
  localparam CTR_STATE_LEN = 2;
  typedef enum logic [CTR_STATUS_STATE+CTR_STATE_LEN-1:CTR_STATUS_STATE] {
    CTR_IDLE = 0,
    CTR_RUNNING = 1,
    CTR_COMPLETE = 2
  } e_ctr_state;

  logic [addrWidth-1:0] paddr;
  logic pwrite;
  logic psel;
  logic penable;
  logic [dataWidth-1:0] pwdata;
  logic [dataWidth-1:0] prdata;
  logic pready;
  logic pslverr;
  logic presetn;

  logic [dataWidth-1:0] dataBuf;
  logic errBuf;

  int testBuf;

  timer #(
      .timerbits(dataWidth),
      .addrWidth(addrWidth),
      .timerBaseAddr(timerBaseAddr)
  ) timer_inst (
      .sel(psel),
      .enable(penable),
      .reset(presetn),
      .clk(clk),
      .write(pwrite),
      .addr(paddr),
      .wdata(pwdata),
      .rdata(prdata),
      .ready(pready),
      .slverr(pslverr)
  );

  typedef enum {
    READ,
    WRITE
  } e_rw;
  task exchangeData(input e_rw exchMode, input logic [addrWidth-1:0] deviceAddr,
                    inout logic [dataWidth-1:0] data, output logic err);
    begin
      // IDLE -> SETUP
      paddr  <= deviceAddr;
      psel   <= 1;
      pwrite <= exchMode;
      if (exchMode == WRITE) pwdata <= data;
      @(posedge clk);
      // SETUP -> ACCESS
      penable <= 1;
      @(posedge clk);

      while (!pready) @(posedge clk);
      // ACCESS -> IDLE
      if (exchMode == READ) data <= prdata;
      err <= pslverr;
      penable <= 0;
      psel <= 0;
      @(posedge clk);
    end
  endtask

  task exchangeDataNoWait(input e_rw exchMode, input logic [addrWidth-1:0] deviceAddr,
                          inout logic [dataWidth-1:0] data, output logic err);
    begin
      // IDLE -> SETUP
      paddr  <= deviceAddr;
      psel   <= 1;
      pwrite <= exchMode;
      if (exchMode == WRITE) pwdata <= data;
      @(posedge clk);
      // SETUP -> ACCESS
      penable <= 1;
      @(posedge clk);

      repeat (2) @(posedge clk);
      // ACCESS -> IDLE
      if (exchMode == READ) data <= prdata;
      err <= pslverr;
      penable <= 0;
      psel <= 0;
      repeat (2) @(posedge clk);
    end
  endtask

  task exchangeDataNoPSEL(input e_rw exchMode, input logic [addrWidth-1:0] deviceAddr,
                          inout logic [dataWidth-1:0] data, output logic err);
    begin
      // IDLE -> SETUP
      paddr  <= deviceAddr;
      psel   <= 0;
      pwrite <= exchMode;
      if (exchMode == WRITE) pwdata <= data;
      @(posedge clk);
      // SETUP -> ACCESS
      penable <= 1;
      @(posedge clk);

      repeat (2) @(posedge clk);
      // ACCESS -> IDLE
      if (exchMode == READ) data <= prdata;
      err <= pslverr;
      penable <= 0;
      psel <= 0;
      repeat (2) @(posedge clk);
    end
  endtask

  initial begin
    presetn <= 0;
    pwdata <= 0;
    pwrite <= 0;
    dataBuf <= 0;
    errBuf <= 0;
    penable <= 0;
    psel <= 0;
    paddr <= 0;
    testBuf = 0;
    #10;
    presetn <= 1;
    @(posedge clk);

    ///////////////////////	- write + read on wrong addr///////////////////////////
    // There should be no reaction
    exchangeDataNoWait(WRITE, 3, dataBuf, errBuf);
    // There should be no reaction
    exchangeDataNoWait(READ, 3, dataBuf, errBuf);
    $display("dataBuf=%d, is it still zero? %d", dataBuf, dataBuf == 0);

    ////////////////////////// write + read without psel //////////////////////////
    // There should be no reaction
    exchangeDataNoPSEL(WRITE, CTR_STATUS_ADDR, dataBuf, errBuf);
    // There should be no reaction
    exchangeDataNoPSEL(READ, CTR_STATUS_ADDR, dataBuf, errBuf);
    $display("dataBuf=%d, is it still zero? %d", dataBuf, dataBuf == 0);

    ///////////////// start a timer and access current counter + state ////////////
    // get status,
    // dataBuf[CTR_STATUS_STATE+CTR_STATE_LEN-1:CTR_STATUS_STATE] == CTR_IDLE
    exchangeData(READ, CTR_STATUS_ADDR, dataBuf, errBuf);
    $display("dataBuf=%d, Is it equal to 0b 0000_(00)(0)(0)? %d", dataBuf, dataBuf == 0);

    dataBuf <= 25;
    @(posedge clk);
    // Setting ctr to 20 ticks
    exchangeData(WRITE, CTR_GOAL_ADDR, dataBuf, errBuf);

    dataBuf <= 0;
    @(posedge clk);
    dataBuf[CTR_STATUS_START] <= 1'b1;
    @(posedge clk);

    // starting ctr
    exchangeData(WRITE, CTR_STATUS_ADDR, dataBuf, errBuf);

    // accessing current ctr value
    exchangeData(READ, CTR_CURR_ADDR, dataBuf, errBuf);
    $display("dataBuf=%d, Is it not equal to 0? %d", dataBuf, dataBuf != 0);

    // get status,
    // dataBuf[CTR_STATUS_STATE+CTR_STATE_LEN-1:CTR_STATUS_STATE] == CTR_RUNNING
    exchangeData(READ, CTR_STATUS_ADDR, dataBuf, errBuf);
    $display(
        "dataBuf=%d, Is it equal to 0b 0000_(01)(0)(1)? %d", dataBuf,
        dataBuf[CTR_STATUS_STATE+:CTR_STATE_LEN] == CTR_RUNNING && dataBuf[CTR_STATUS_START] == 1 && dataBuf[CTR_STATUS_STOP] == 0);
    repeat (20) @(posedge clk);  // w8 until ctr ends
    // get status
    // dataBuf[CTR_STATUS_STATE+CTR_STATE_LEN-1:CTR_STATUS_STATE] == CTR_COMPLETE
    exchangeData(READ, CTR_STATUS_ADDR, dataBuf, errBuf);
    $display(
        "dataBuf=%d, Is it equal to 0b 0000_(10)(0)(0)? %d", dataBuf,
        dataBuf[CTR_STATUS_STATE+:CTR_STATE_LEN] == CTR_COMPLETE && dataBuf[CTR_STATUS_START] == 0 && dataBuf[CTR_STATUS_STOP] == 0);
    // get status,
    // dataBuf[CTR_STATUS_STATE+CTR_STATE_LEN-1:CTR_STATUS_STATE] == CTR_IDLE
    exchangeData(READ, CTR_STATUS_ADDR, dataBuf, errBuf);
    $display(
        "dataBuf=%d, Is it equal to 0b 0000_(00)(0)(0)? %d", dataBuf,
        dataBuf[CTR_STATUS_STATE+:CTR_STATE_LEN] == CTR_IDLE && dataBuf[CTR_STATUS_START] == 0 && dataBuf[CTR_STATUS_STOP] == 0);
    ////////////////// pause + read curr 2 times (should be the same) /////////////
    dataBuf <= 25;
    @(posedge clk);
    // Setting ctr to 20 ticks
    exchangeData(WRITE, CTR_GOAL_ADDR, dataBuf, errBuf);

    dataBuf <= 0;
    @(posedge clk);
    dataBuf[CTR_STATUS_START] <= 1'b1;
    @(posedge clk);

    // starting ctr
    exchangeData(WRITE, CTR_STATUS_ADDR, dataBuf, errBuf);

    dataBuf <= 0;
    @(posedge clk);
    dataBuf[CTR_STATUS_START] <= 1'b1;
    dataBuf[CTR_STATUS_STOP]  <= 1'b1;
    @(posedge clk);
    // stopping ctr (maybe?)
    exchangeData(WRITE, CTR_STATUS_ADDR, dataBuf, errBuf);

    // Both accesses should yield the same result
    // accessing current ctr value
    exchangeData(READ, CTR_CURR_ADDR, dataBuf, errBuf);
    testBuf = dataBuf;
    $display("dataBuf=%d, Is it not equal to 0? %d", dataBuf, dataBuf != 0);
    // accessing current ctr value
    exchangeData(READ, CTR_CURR_ADDR, dataBuf, errBuf);
    $display("dataBuf=%d, Is it the same as in first read? %d", dataBuf, testBuf == dataBuf);


    $finish();
  end

  initial begin
    $dumpfile("test.vcd");
    $dumpvars(0, timerVrf);
  end

  logic clk = 0;
  always #1 clk = ~clk;
endmodule
