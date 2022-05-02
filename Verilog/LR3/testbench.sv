`define READ 0
`define WRITE 1

module testbench 
#(
    parameter word_size = 20,
    parameter word_amount = 30
);

    logic[$clog2(word_amount)] address;   	// адрес обращения
    logic select;                    		// признак обращения
    logic operation;                  		// тип операции (запись/чтение)
    logic[word_size] wdata;             	// данные для записи
    logic[word_size] rdata;              	// прочитанные данные

	ram #(.word_size(word_size), .word_amount(word_amount)) ram_inst(.address(address), .select(select), .operation(operation), .wdata(wdata), .rdata(rdata));

	initial begin
		// Запись
		select <= 1;
		operation <= `WRITE;
		address <= 2;
		wdata <= 17;
		#1
		select <= 0;
		#1
		// Чтение
		select <= 1;
		operation <= `READ;
		address <= 2;
		#1
		if (rdata == 17) $display("success");
		#1
		select <= 0;
		#1
		$finish;
	end

	initial begin
		$dumpfile("var_dump.vcd");
		$dumpvars;
	end
endmodule