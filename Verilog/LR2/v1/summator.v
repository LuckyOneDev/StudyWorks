module summator #(parameter reglength = 3)(input wire[reglength-1:0] r1, r2, input wire clk, output wire sum);
	
	reg init = 1;
	reg[reglength-1:0] reg1, reg2 = 0;

	fullsum s(.A(reg1[0]), .B(reg2[0]), .clk(clk), .sum(sum));

	always @ (posedge clk) begin
		if (init) begin
			reg1 <= r1;
			reg2 <= r2;
			init <= 0;
		end

		reg1 = reg1 >> 1;
		reg2 = reg2 >> 1;
	end
endmodule
