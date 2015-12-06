`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   23:14:31 10/16/2015
// Design Name:   TFF
// Module Name:   /home/sidharth/IIIT-Delhi/ELD/Assignments/Verilog/Assignment_1/Assign1/test_TFF.v
// Project Name:  Assign1
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: TFF
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module test_TFF;

	// Inputs
	reg in_T;
	reg clk;
	reg reset;

	// Outputs
	wire out_Q;
	wire out_QBar;

	// Instantiate the Unit Under Test (UUT)
	TFF uut (
		.in_T(in_T), 
		.clk(clk), 
		.reset(reset), 
		.out_Q(out_Q), 
		.out_QBar(out_QBar)
	);

	initial begin
		// Initialize Inputs
		in_T = 1;
		clk = 0;
		reset = 0;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here

	end
	
	always begin
		#10 clk = ~clk;
	end
	
	always begin
		#100 reset = 1'b1;
		#1 reset = 1'b0;
	end
      
endmodule

