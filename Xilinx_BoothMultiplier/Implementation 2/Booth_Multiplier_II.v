`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:00:42 11/06/2015 
// Design Name: 	 Sidharth Sharma
// Module Name:    Booth_Multiplier_II 
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
module Booth_Multiplier_II (product,
									 multiplicand,
									 multiplier);

	output [7:0] product;
	input signed [3:0] multiplicand, multiplier;					// To tell the synthesizer to treat this 4 bit input as signed
																				// instead of the 18 bit input that it does by defaul

	assign product = multiplicand * multiplier;					// uses the dedicated multiplier of FPGA

endmodule
