`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Create Date:    23:09:55 10/16/2015 
// Module Name:    TFF
// Creator    :	   GROUP 30 __ ELD 
//////////////////////////////////////////////////////////////////////////////////
module TFF(
    input in_T,
    input clk,
    input reset,
    output reg out_Q,
    output reg out_QBar
    );
	 
	initial begin
		out_Q = 1'b0;
		out_QBar = 1'b1;
		$display ("T FLIP FLOP Running");
	end
	
	always @(posedge clk) begin
		if (in_T == 1'b1) begin
			out_Q = ~out_Q;
			out_QBar = ~out_QBar;
		end else begin
			out_Q = out_Q;
			out_QBar = out_QBar;
		end
	end
	
	always @(posedge reset) begin
		out_Q = 1'b0;
		out_QBar = 1'b1;
	end

endmodule
