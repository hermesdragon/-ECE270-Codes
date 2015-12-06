`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   22:19:51 10/29/2015
// Design Name:   eightInput_PE
// Module Name:   /home/sidharth/Documents/Xilinx Projects/PriorityEncoder/eightInput_tester.v
// Project Name:  PriorityEncoder
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: eightInput_PE
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module eightInput_tester;

	// Inputs
	reg [7:0] in;

	// Outputs
	wire [3:0] out;

	// Instantiate the Unit Under Test (UUT)
	eightInput_PE uut (
		.out(out), 
		.in(in)
	);

	initial begin
		// Initialize Inputs
		in = 0;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here

	end
	
	integer i;
	// Check at all possible values of input
	initial begin
		for (i = 0; i < 256; i=i+1) begin
			in = i;
			#50;
		end
	end
      
endmodule

