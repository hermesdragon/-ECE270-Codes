`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:06:10 11/11/2015 
// Design Name: 
// Module Name:    clockGen_divBy4 
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
module clockGen_divBy4 (outClk, inClk);

	input inClk;
	output outClk;
	wire tempClk;
	
	clockGen_divBy2 half (tempClk, inClk);
	clockGen_divBy2 quarter (outClk, tempClk);

endmodule