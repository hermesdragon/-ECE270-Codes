`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:55:42 10/20/2015 
// Design Name: 
// Module Name:    eightInput_PE 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module eightInput_PE (out, in);

	output reg[3:0] out;
	input [7:0] in;
	
	always @(in[7:0]) begin
		if (in[7]) begin
			out <= 4'b1000;
		end else if (in[6]) begin
			out <= 4'b0111;
		end else if (in[5]) begin
			out <= 4'b0110;
		end else if (in[4]) begin
			out <= 4'b0101;
		end else if (in[3]) begin
			out <= 4'b0100;
		end else if (in[2]) begin
			out <= 4'b0011;
		end else if (in[1]) begin
			out <= 4'b0010;
		end else if (in[0]) begin
			out <= 4'b0001;
		end else begin
			out <= 4'b0000;
		end
	end

endmodule
