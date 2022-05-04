`define READ 0
`define WRITE 1

module ram #(
    parameter word_size   = 20,
    parameter word_amount = 30
) (
    input logic [$clog2(word_amount):0] address,  // адрес обращения
    input logic select,  // признак обращения
    input logic operation,  // тип операции (запись/чтение)
    input logic [word_size:0] wdata,  // данные для записи
    output logic [word_size:0] rdata  // прочитанные данные
);

  reg [word_size:0][word_amount:0] memory = 0;

  always @(posedge select) begin
    if (operation == `READ) begin
      rdata = memory[address];
    end else begin
      memory[address] = wdata;
    end
  end

endmodule
