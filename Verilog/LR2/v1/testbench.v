module SumTB #(parameter reglength = 3);
	reg clk = 0;

	reg[reglength:0] i, j, k = 0;

	reg[reglength:0] sumReg;
	reg[0:0] A;
	reg[0:0] B;
	reg[0:0] testErrorN;
	wire[0:0] sum;

	summator #(.reglength(reglength)) sm_inst(.r1(A), .r2(B), .clk(clk), .sum(sum));

	initial
		begin
			clk <= 0;
			sumReg <= 0;
			@(posedge clk);
			for (i = 1; i < 2 ** reglength; i = i + 1) begin
				for (j = 1; j < 2 ** reglength; j = j + 1) begin
					for (k = 0; k < reglength; k = k + 1) begin
						A <= i[k];
						B <= j[k];
						@(posedge clk);
					end

				A <= 0;
				B <= 0;
				@(posedge clk);

				for (k = 0; k < reglength + 1; k = k + 1) begin
						sumReg[k] <= sum;
						@(posedge clk);
					end

				testErrorN <= sumReg == i + j ? 1 : 0;
				@(posedge clk);

				sumReg <= 0;
				@(posedge clk);
				end
			end
			$finish();
		end
	initial begin
		$dumpfile("test.vcd");
		$dumpvars(0,SumTB);
	end
	always
		#1 clk = ~clk;

endmodule
