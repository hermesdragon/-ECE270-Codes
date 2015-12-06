/*			group 30 :: Embedded Logic Design :: Assignment 2
 *			Members:
 *				@author: Sidharth Sharma __ 2014163
 *				
 *			Blinking LED using AVR
 */
 
/*	This code makes the LED at pin 13 of the Arduino blink continuously at a frequency of
 *	1 Hz.
 */

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
	DDRB = 0b11111111;
	while (1)
	{
		PORTB ^= 0b00100000;
		_delay_ms (1000);
	}
	return 0;
}
