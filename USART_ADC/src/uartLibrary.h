/**
 * This library contains the interaction with the UART interface.
 * 
 * Usage:
 * 	1) In your program include "uartLibrary.h"
 * 	2) In your main function, redefine stdout and stdin:
 * 	   		stdout = &uart_output;
 * 	   		stdin  = &uart_input;
 * 	3) If you successfully implemented the functions below,
 * 	   you will be able to use
 * 	   		puts(string s);
 * 	   		printf(string, parameters);
 * 	   to print data into the UART interface. With
 * 	   		char c = getChar();
 *     you can read from the terminal.
 *
 * For further information have a look at the example code that is
 * included.
 */


#ifndef UART_LIBRARY_INCLUDED
#define UART_LIBRARY_INCLUDED

#define F_CPU 16000000UL		// CPU Clock Speed
#define BAUD 9600			// BAUD Rate
#define UBRR_VAL ((F_CPU/16/BAUD)-1)	// Value for USART BAUD RATE REGISTER

//#include <util/setbaud.h>		// Required For 
#include <avr/io.h>
#include <stdio.h>

/**
 * Configures the UART port
 * Put all parameters that need to be set regarding the UART here.
 */
void uart_init()
{
	/*	RXC0 = 0	Receive Flag
	 *	TXC0 = 0	Transmit Flag
	 *	UDRE0 = 0	Buffer Empty Flag
	 *	FE0 = 0		Frame Error Flag
	 *	DOR0 = 0	Data OverRun Flag
	 *	UPE0 = 0	Parity Error Flag
	 *	U2X0 = 0	NORMAL Transmission Bit
	 *	MPCM0 = 0	Single Processor Comm. Mode
	 */
	UCSR0A |= 0b00000000;

	/*	RXCIE0 = 1	Enable Receive Interrupt
	 *	TXCIE0 = 0	Disable Transmit Interrupt
	 *	UDRIE0 = 0
	 *	RXEN0 = 1	Enable Receiver
	 *	TXEN0 = 1	Enable Transmitter
	 *	UCSZ02 = 0	For 8 bit Data
	 *	RXB80 = 0	Dont Care
	 *	TXB80 = 0	Dont Care
	 */
	UCSR0B |= 0b10011000;

	/*	UMSEL01:0 = 00	Asynchronous USART
	 *	UPM01:0 = 00	Disable Parity
	 *	USBS0 = 0	1 Stop Bit
	 *	UCSZ01:11	8 Bit Data
	 *	UCPOL0 = 0	Dont Care in Asynch.
	 */
	UCSR0C |= 0b00000110;

	/*	Setting UBBR0
	 */
	UBRR0H = UBRR_VAL >> 8;
	UBRR0L = UBRR_VAL;
}

/**
 * Prints a character to the UART interface
 * @params c: the character to be printed
 * @params *stream: The file stream. Do not worry what
 * 		    is put there. It is used internally by puts
 * 		    or printf.
 */
void uart_putchar(char c, FILE *stream) {
	if (c == '\n') {		// format the string nicely for display on the serial terminal
		uart_putchar('\r', stream);
	}

	// Wait till Data Buffer is Empty
	while (1)
	{
		if (UCSR0A & 0b00100000)	// check UDRE0
			break;
	}
	UDR0 = c;
}


/**
 * Get a character from the UART interface
 * @params *stream: The file stream. Do not worry what
 * 		    is put there. It is used internally by puts
 * 		    or printf.
 */
char uart_getchar (FILE *stream)
{
	// Wait till Data is available in Data Buffer
	while (1)
	{
		if (UCSR0A & 0b10000000)	// check RXC0
			break;
	}
	return UDR0;
}


/**
 * Allows you to use printf, puts as commands to print something through the UART
 * on your serial console. It then can be displayed using HyperTerminal, minicom etc.
 */
FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

/**
 * Allows you to use getChar() to get a character from the user through UART
 */
FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);


#endif
