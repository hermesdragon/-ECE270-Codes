`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:35:45 11/11/2015 
// Design Name: 
// Module Name:    LEDRotator 
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
module LEDRotator (SSLED, LEDSEL, inClk, reset);

	output reg [6:0] SSLED;
	output reg [3:0] LEDSEL;
	input inClk, reset;
	
	always @(posedge inClk or posedge reset) begin
		if (reset) begin
			SSLED = 7'b1110111;									// Reset --> D
			LEDSEL = 3'b0111;										// LED1 = ON, LED2 = OFF, LED3 = OFF, LED4 = OFF
		end
		else begin
			case (SSLED)
				7'b0111111: SSLED = 7'b1111101;				// A --> F
				7'b1111101: SSLED = 7'b1111011;				// F --> E
				7'b1111011: SSLED = 7'b1110111;				// E --> D
				7'b1110111: SSLED = 7'b1101111;				// D --> C
				7'b1101111: SSLED = 7'b1011111;				// C --> B
				7'b1011111: SSLED = 7'b0111111;				// B --> A
				default: SSLED = 7'b0111111;					// Any Arbitrary State goes to a valid State
			endcase
		end
	end

endmodule
