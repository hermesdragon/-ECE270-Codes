`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:20:08 10/20/2015 
// Design Name: 
// Module Name:    DataFlow_PE 
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
module DataFlow_PE (out1, out0, in2, in1, in0);

	output wire out1, out0;
	input wire in2, in1, in0;
	
	assign out1 = (in2 | in1);
	assign out0 = (((~in1) & in0) | in2);

endmodule
