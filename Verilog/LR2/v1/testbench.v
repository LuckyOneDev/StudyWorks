module SumTB  #(parameter reglength = 3, r1 = 0, r2 = 0)();
	reg clk = 0;
	
	reg[reglength-1:0] reg1 = r1;
	reg[reglength-1:0] reg2 = r2;
	
	wire[reglength:0] summa = 0;
	
	summator #(.reglength(3), .r1val(r1), .r2val(r2)) sm_inst(.r1(reg1), .r2(reg2), .clk(clk), .summa(summa));

	initial
		begin
			#8
			$display("r1: %d\nr2: %d summ: %d", r1, r2, summa);
			$finish;
		end

	always 
		#1 clk = ~clk;
endmodule
