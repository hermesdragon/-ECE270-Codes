`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   22:33:51 11/06/2015
// Design Name:   Booth_Multiplier_II
// Module Name:   /home/sidharth/Documents/Xilinx Projects/NEW2/Booth_Tester_2.v
// Project Name:  NEW2
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: Booth_Multiplier_II
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module Booth_Tester_2;

	// Inputs
	reg [3:0] multiplicand;
	reg [3:0] multiplier;

	// Outputs
	wire [7:0] product;

	// Instantiate the Unit Under Test (UUT)
	Booth_Multiplier_II uut (
		.product(product), 
		.multiplicand(multiplicand), 
		.multiplier(multiplier)
	);

	initial begin
		// Initialize Inputs
		multiplicand = 4'b1100;
		multiplier = 4'b1011;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here

	end
      
endmodule

