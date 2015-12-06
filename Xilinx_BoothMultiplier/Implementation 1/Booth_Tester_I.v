`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   22:18:33 11/06/2015
// Design Name:   Booth_Multiplier_1
// Module Name:   /home/sidharth/Documents/Xilinx Projects/NEW1/Booth_Tester_I.v
// Project Name:  NEW1
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: Booth_Multiplier_1
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module Booth_Tester_I;

	// Inputs
	reg [3:0] multiplicand;
	reg [3:0] multiplier;
	reg clock;
	reg start;

	// Outputs
	wire [7:0] product;
	wire busy;

	// Instantiate the Unit Under Test (UUT)
	Booth_Multiplier_1 uut (
		.product(product), 
		.multiplicand(multiplicand), 
		.multiplier(multiplier), 
		.clock(clock), 
		.start(start), 
		.busy(busy)
	);

	initial begin
		// Initialize Inputs
		multiplicand = 1100;
		multiplier = 1011;
		clock = 0;
		start = 0;
		#5 start = 1;
		#1 start = 0;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here

	end
	
	always begin
		#10 clock = ~clock;
	end
      
endmodule

