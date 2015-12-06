`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:11:59 11/11/2015 
// Design Name: 
// Module Name:    LEDWorm 
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
module LEDWorm (clk1, clk2, clk3, SSLED, LEDSEL, inClk, buttonA, buttonB, reset);

	input inClk, buttonA, buttonB, reset;
	output clk1, clk2, clk3;
	output [3:0] LEDSEL;
	output [6:0] SSLED;
	
	reg [2:0] clockSelect;
	wire rotClk, I1, I2, I3;
	
	clockGen_50MHz_to_3Hz prescale_1 (clk1, inClk);				// clk1 --> 3Hz
	clockGen_divBy2 prescale_2 (clk2, clk1);						// clk2 --> 3Hz / 2 = 1.5Hz
	clockGen_divBy4 prescale_3 (clk3, clk1);						// clk3 --> 3Hz / 4 = 0.75Hz
	
	LEDRotator L1 (SSLED, LEDSEL, rotClk, reset);				// Keeps rotating SSLED @rotClk
	
	// Clock Selection Logic
	and sel_1 (I1, clk1, clockSelect[2]);				
	and sel_2 (I2, clk2, clockSelect[1]);
	and sel_3 (I3, clk3, clockSelect[0]);
	or sel_4 (rotClk, I1, I2, I3);
	
	// Input Signal Handling Logic
	always @(posedge buttonA or posedge buttonB or posedge reset) begin
		if (reset) begin
			clockSelect = 3'b100;						// Choose 3Hz Clock on Reset
		end else
		if (buttonA) begin
			// Shift clockwise in set {clk1, clk2, clk3}
			case (clockSelect)
				3'b100: clockSelect = 3'b010;			// clk1 --> clk2
				3'b010: clockSelect = 3'b001;			// clk2 --> clk3
				3'b001: clockSelect = 3'b100;			// clk3 --> clk1
				default: clockSelect = 3'b100;		// Any arbitrary selection goes to a valid selection
			endcase
		end
		else begin
			// Shift counter-clockwise in set {clk1, clk2, clk3}
			case (clockSelect)
				3'b100: clockSelect = 3'b001;			// clk1 --> clk3
				3'b001: clockSelect = 3'b010;			// clk3 --> clk2
				3'b010: clockSelect = 3'b100;			// clk2 --> clk1
				default: clockSelect = 3'b100;		// Any arbitrary selection goes to a valid selection
			endcase
		end
	end

endmodule
