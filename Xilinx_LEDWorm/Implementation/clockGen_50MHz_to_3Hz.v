`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:24:11 11/11/2015 
// Design Name: 
// Module Name:    clockGen_50MHz_to_3Hz 
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
module clockGen_50MHz_to_3Hz (outClk_3Hz,
										inClk_50MHz);
	input inClk_50MHz;
	output reg outClk_3Hz;
	integer count;
	
	always @(posedge inClk_50MHz) begin
		if (count < 16666666) begin
			count = count + 1;
		end else begin
			outClk_3Hz = ~outClk_3Hz;
			count = 0;
		end
	end
	
endmodule
