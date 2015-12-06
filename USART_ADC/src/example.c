/*
 * Demonstration on how to redirect stdio to UART. 
 */

#include <stdio.h>

#include "uartLibrary.h"

int main(void) {    

	uart_init();
	stdout = &uart_output;
	stdin  = &uart_input;

	DDRB |= 0x20;
	PORTB |= 0x20;

	char input;

	while(1) {
		puts("Hello world!");
		input = getchar();
		printf("You wrote %c\n", input);        
	}

	return 0;
}

