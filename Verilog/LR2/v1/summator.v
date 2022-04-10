module summator #(parameter reglength = 3, parameter r1val = 0, parameter r2val = 0)(input wire clk);
	reg[reglength-1:0] r1 = r1val;
	reg[reglength-1:0] r2 = r2val;
	
	reg[reglength:0] summa = 0;
	reg carry = 0;

	wire sum_wire;
	wire carry_wire;
	fullsum ha(.A(r1[0]), .B(r2[0]), .sum(sum_wire), .iost(carry), .oost(carry_wire));

	always @ (posedge clk) 
	begin
		summa[0] = sum_wire;
		summa = summa << 1;
		carry = carry_wire;
		r1 = r1 >> 1;
		r2 = r2 >> 1;
		$display("summa %b", summa);
	end
endmodule