#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

void WDTsetup ()
{
	cli ();				// Disable Interrupts
	wdt_reset ();			// Reset WatchDog Timer
	
	// Another Way to achieve this using inbuilt functions
	// wdt_enable (WDTO_1S);	// Set WatchDog prescalar for a delay of 1000ms
	// WDTCSR |= 0b01000000;
	
	MCUSR &= 0b11110111;		// Set MCUSR - WDRF to 0 so it doesnt override WDE in WDTCSR
	
	WDTCSR |= 0b00011000;
	WDTCSR = 0b01000110;		// WDIE = 1, WDP3:0 = 0110, W
	
	sei ();
}

void powerReductionMode ()
{
	cli ();

	SMCR = 0b00000100;					// Setting power down mode | SM2:0 = 010

	PRR |= 0b11101111;					// Power Reduction :: TWI .. timer2 .. timer0 .. R .. timer1 .. SPI .. USART .. ADC

	MCUCR |= 0b01100000;					// Starting BOD Configuration Cycle
	MCUCR &= 0b11011111;					// Setting BODSE = 0 and BODS = 1 | Only 4 cycles to sleep

	SMCR |= 0b00000001;					// Setting Sleep Enable (SE) = 1 | Only 4 cycles to sleep

	sei ();

	sleep_cpu ();
}

int main ()
{
	DDRB |= 0b00100000;
	WDTsetup ();
	powerReductionMode ();
	while (1);
	return 0;
}

ISR (WDT_vect)
{
	cli ();
	SMCR &= 0b11111110;					// Unsetting Sleep Enable
	PORTB ^= 0b00100000;
	wdt_reset ();
	sei ();
	powerReductionMode ();
}
