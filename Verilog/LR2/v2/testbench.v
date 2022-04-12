module SumTB #(parameter reglength = 3);
	reg clk = 0;
	
	reg[reglength:0] i = 0;

	reg[reglength-1:0] reg1 = 0;
	reg[reglength-1:0] reg2 = 0;

	reg reset = 0;

	summator #(.reglength(reglength)) sm_inst(.r1(reg1), .r2(reg2), .clk(clk), .sum(sum), .reset(reset));

	always @(posedge clk) begin
		$display(sum);
	end

	initial
		begin
			repeat (2 ** reglength) begin
				reg2 = 0;
				repeat (2 ** reglength) begin
					$display("%d + %d:", reg1, reg2);
					#8 
					$display("end");
					reset = ~reset;
					reg2 = reg2 + 1;
				end
				reg1 = reg1 + 1;
			end
			$finish;
		end

	always 
		#1 clk = ~clk;
endmodule
