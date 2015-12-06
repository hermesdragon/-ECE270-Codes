`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:59:25 11/11/2015 
// Design Name: 
// Module Name:    clockGen_divBy2 
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
module clockGen_divBy2 (outClk, inClk);

	input inClk;
	output reg outClk;
	reg tempClk;
	
	always @(posedge inClk) begin
		outClk = ~outClk;						// Toggles @ half the input frequency
	end

endmodule
