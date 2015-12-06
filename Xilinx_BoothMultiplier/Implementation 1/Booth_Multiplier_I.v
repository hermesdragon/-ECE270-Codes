`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:51:58 11/02/2015 
// Design Name: 	Sidharth Sharma
// Module Name:    Booth_Multiplier_1 
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
module Booth_Multiplier_1 (product,
									multiplicand,
									multiplier,
									clock,
									start,
									busy);

	output reg [7:0] product;										// 8 bit product
	output reg busy;													// 1 bit busy
	input [3:0] multiplicand, multiplier;						// 4 bit inputs
	input wire clock, start;										// 1 bit inputs
	
	reg [8:0] A, S, P;
	reg [2:0] index;
	reg temp;
	
	always @(posedge clock or posedge start) begin									// Sensitive to CLOCK only
		if (start) begin
			
			P = {4'b0000, multiplier, 1'b0};							// Setup P
			index = 3'b000;												// Start with Index '0'
			busy = 1'b1;													// Busy = '1' to say calculation has started
			product = 8'b11111111;										// Output stays high untill result is calculated (my implementation)
			A = {multiplicand, 5'b00000};								// Setup ADD and SUBTRACT Values
			S = {~multiplicand + 1'b1, 5'b00000};
		
		end else	if (index < 3'b100) begin
		
			case ({P[1], P[0]})										// Check last two bits of P
				2'b01:	P = (P + A);								// ADD
				2'b10:	P = (P + S);								// SUBTRACT
			endcase
			
			// Signed Right Shift (Tried ">>>" but didn't work)
			temp = P[8];												// Copy MSB
			P = P >> 1;													// Right Shift by 1
			P[8] = temp;												// Set MSB = previous MSB
			
			index = index + 1'b1;									// Increment index
		end else begin
		
			busy = 1'b0;												// Busy = '0' to say calculation has finished
			{product, temp} = P;										// product = leftmost 8 bits of P | temp acts as a temporary buffer
			index = 3'b111;											// Set index to a value at which above clause won't execute for successive clocks
		
		end
	end


endmodule

