module summator #(parameter reglength = 3)(input wire[reglength-1:0] r1, r2, input wire clk, output reg[reglength:0] sum);
	reg[reglength-1:0] reg1, reg2 = 0;

	always @ (posedge clk) begin
		reg1 <= r1;
		reg2 <= r2;
		sum = reg1 + reg2;
	end
endmodule
