#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

void timerSetup ()
{
	/* 
	 * ***** Setting up the Timer in CTC Mode *****
	 * Using Timer 1
	 */

	cli();							// Disable Interrupts

	TIMSK1 = 0b00000010;					// Enable OCIE1A Interrupt and none other | OCIEA ==> Bit_1 = 1
	TCCR1A = 0b00000000;					// COM1A1:0, COM1B1:0, RR, WGM11:10 set to 0

	TCCR1B = 0;
	TCCR1B |= 0b00001000;					// Set Mode = CTC | WGM12 ==> Bit_3 = 1
	TCCR1B |= 0b00000101;					// CS12:10 ==> Bits_2:0 = 101 | Set prescaler = 1024 | Ck = 16 MHz / 1024 = 15625

	OCR1A = 15624;						// Setting TOP = 15624

	sei();							// Enable Interrupts
}

void powerReductionMode ()
{
	cli ();

	SMCR = 0b00000110;					// Setting power save mode | SM2:0 = 011

	PRR |= 0b11100111;					// Power Reduction :: TWI .. timer2 .. timer0 .. R .. SPI .. USART .. ADC

	MCUCR |= 0b01100000;					// Starting BOD Configuration Cycle
	MCUCR &= 0b11011111;					// Setting BODSE = 0 and BODS = 1 | Only 4 cycles to sleep

	SMCR |= 0b00000001;					// Setting Sleep Enable (SE) = 1 | Only 4 cycles to sleep

	sei ();

	sleep_cpu ();
}

int main ()
{
	DDRB |= 0b00100000;					// Set PB5 as output | ArduinoPIN : 13
	timerSetup ();
	while (1);						// Infinite loop
	return 0;
}

ISR (TIMER1_COMPA_vect)
{
	cli ();
	SMCR &= 0b11111110;					// Unsetting Sleep Enable
	PORTB ^= 0b00100000;
	sei ();
	// powerReductionMode ();
}