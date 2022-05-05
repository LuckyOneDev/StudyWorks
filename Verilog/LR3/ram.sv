`define READ 0
`define WRITE 1

module ram #(
    parameter word_size   = 27,
    parameter word_amount = 37
) (
    input logic [$clog2(word_amount)-1:0] address,  // адрес обращения
    input logic select,  // признак обращения
    input logic operation,  // тип операции (запись/чтение)
    input logic [word_size-1:0] wdata,  // данные для записи
    output logic [word_size-1:0] rdata  // прочитанные данные
);

  logic [word_amount-1:0][word_size-1:0] memory;

  always @(posedge select) begin
    if (operation == `READ) begin
      rdata = memory[address];
    end else begin
      memory[address] = wdata;
    end
  end

endmodule
