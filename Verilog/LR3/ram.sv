`define READ 0
`define WRITE 1

module ram #(
    parameter word_size   = 20,
    parameter word_amount = 30
) (
    input logic [$clog2(word_amount)] address,  // адрес обращения
    input logic select,  // признак обращения
    input logic operation,  // тип операции (запись/чтение)
    input logic [word_size] wdata,  // данные для записи
    output logic [word_size] rdata  // прочитанные данные
);

  reg [word_size * word_amount] memory = 0;

  always @(posedge select) begin
    if (operation == `READ) begin
      rdata = memory[address+:word_size];
    end else begin
      memory[address+:word_size] = wdata;
    end
  end

endmodule
