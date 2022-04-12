module SumTB  #(parameter reglength = 3, r1 = 7, r2 = 7)();
	reg clk = 0;
	
	reg[reglength-1:0] reg1 = r1;
	reg[reglength-1:0] reg2 = r2;

	summator #(.reglength(reglength)) sm_inst(.r1(reg1), .r2(reg2), .clk(clk), .sum(sum));

	always @(posedge clk) begin
		$display("sum: %b", sum);
	end

	initial
		begin
			#12 $finish;
		end

	always 
		#1 clk = ~clk;
endmodule
