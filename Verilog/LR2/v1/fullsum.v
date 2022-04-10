module fullsum(input wire A, B, input wire iost, output wire sum, oost);
	assign sum = (A ^ B) ^ iost;
	assign oost = (A & B) | (B & iost) | (A & iost);
endmodule