`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:05:24 10/20/2015 
// Design Name: 
// Module Name:    GateLevel_PE 
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
module GateLevel_PE(
    output wire out1,
    output wire out0,
    input wire in2,
    input wire in1,
    input wire in0
    );

	wire _in1;								// Inverted in1
	not not_1 (_in1, in1);
	
	or or_1 (out1, in2, in1);			// out1 = in2 + in1
	
	wire temp1;
	and and_1 (temp1, _in1, in0);		// temp1 = _in1.in0
	or or_2 (out0, temp1, in2);		// out0 = _in1.in0 + in2

endmodule
