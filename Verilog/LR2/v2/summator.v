module summator #(parameter reglength = 3)(input wire[reglength-1:0] r1, r2, input wire clk, output wire sum);
	reg[reglength:0] accumulator = 0;

	assign sum = accumulator[0];

	reg init = 1;
	reg[reglength-1:0] reg1, reg2 = 0;

	always @ (posedge clk) begin
		if (init) begin
			reg1 = r1;
			reg2 = r2;
			init = 0;
			accumulator = reg1 + reg2;
		end
		accumulator = accumulator >> 1;
	end
endmodule