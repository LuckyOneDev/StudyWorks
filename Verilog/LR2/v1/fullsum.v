module fullsum(input wire A, B, clk, output wire sum);
	reg carry = 0;
	assign sum = (A ^ B) ^ carry;
	always @ (posedge clk) begin
		carry = (A & B) | (B & carry) | (A & carry);
	end
endmodule
