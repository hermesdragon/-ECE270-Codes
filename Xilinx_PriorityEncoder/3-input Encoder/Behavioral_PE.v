`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:34:13 10/20/2015 
// Design Name: 
// Module Name:    Behavioral_PE 
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
module Behavioral_PE (out1, out0, in2, in1, in0);

	output reg out1, out0;
	input wire in2, in1, in0;

	always @(in2 or in1 or in0) begin
		if (in2 == 1'b1) begin
			out1 = 1'b1;
			out0 = 1'b1;
		end else if (in1 == 1'b1) begin
			out1 = 1'b1;
			out0 = 1'b0;
		end else if (in0 == 1'b1) begin
			out1 = 1'b0;
			out0 = 1'b1;
		end else begin
			out1 = 1'b0;
			out0 = 1'b0;
		end
	end

endmodule
