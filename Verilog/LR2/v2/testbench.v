module SumTB #(parameter reglength = 3);
	reg clk = 0;
	
	reg[reglength:0] i, j = 0;

	reg[reglength-1:0] reg1 = 0;
	reg[reglength-1:0] reg2 = 0;

	summator #(.reglength(reglength)) sm_inst(.r1(reg1[0]), .r2(reg2[0]), .clk(clk), .sum(sum));

	always @(posedge clk) begin
		$display(sum);
		reg1 = reg1 >> 1;
		reg2 = reg2 >> 1;
	end

	initial
		begin
			for (i = 0; i < 2 ** reglength; i = i + 1) begin
				reg2 = 0;
    			for (j = 0; j < 2 ** reglength; j = j + 1) begin
					$display("%d + %d:", reg1, reg2);
					#16
					$display("end");
					reg2 = j + 1;
					reg1 = i;
				end
				reg1 = i + 1;
			end
			$finish;
		end

	always 
		#1 clk = ~clk;
endmodule
