`define READ 0
`define WRITE 1

module testbench #(
    parameter word_size   = 27,
    parameter word_amount = 37
);

  logic [$clog2(word_amount)] address;  // адрес обращения
  logic                       select;  // признак обращения
  logic                       operation;  // тип операции (запись/чтение)
  logic [          word_size] wdata;  // данные для записи
  logic [          word_size] rdata;  // прочитанные данные

  ram #(
      .word_size  (word_size),
      .word_amount(word_amount)
  ) ram_inst (
      .address(address),
      .select(select),
      .operation(operation),
      .wdata(wdata),
      .rdata(rdata)
  );

  task TestMem(input logic [$clog2(word_amount)] test_address, input logic [word_size] test_data);
    // Запись
    select <= 0;
    operation <= `WRITE;
    address <= test_address;
    wdata <= test_data;
    #1;
    select <= 1;
    #1;
    select <= 0;
    #1;
    // Чтение
    select <= 1;
    operation <= `READ;
    address <= test_address;
    #1;
    if (rdata == test_data) $display("Data successfully read from %b", test_address);
    #1;
    select <= 0;
    #1;
  endtask

  initial begin
    TestMem(0, 7);
    TestMem(20, 11);
    TestMem(36, 134_217_727);
    $finish;
  end

  initial begin
    $dumpfile("var_dump.vcd");
    $dumpvars;
  end
endmodule


