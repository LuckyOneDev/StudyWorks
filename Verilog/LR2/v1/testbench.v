module SumTB  #(parameter r1 = 3, parameter r2 = 3)();
	reg clk = 0;

	summator #(.reglength(3), .r1val(r1), .r2val(r2)) sm_inst(clk);

	initial
		begin
			$display("r1: %d\nr2: %d", r1, r2);
			#8 $finish;
		end

	always 
		#1 clk = ~clk;
endmodule