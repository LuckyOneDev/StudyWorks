module summator #(parameter reglength = 3)(input wire r1, r2, input wire clk, output wire sum);
	reg[reglength-1:0] reg1, reg2 = 0;

	fullsum s(.A(reg1[0]), .B(reg2[0]), .clk(clk), .sum(sum));

	always @ (posedge clk) begin
		reg1[reglength-1] <= r1;
		reg2[reglength-1] <= r2;
		reg1 = reg1 >> 1;
		reg2 = reg2 >> 1;
	end
endmodule
