#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

void setupADC ()
{
	/*	REFS1:0 = 00			External Reference [AREF]
	 *	ADLAR = 0
	 *	MUX3:0 = 0000			Pin ADC0
	 */
	ADMUX = 0b00000000;

	/*	ADEN = 1
	 *	ADSC = 0			Will be enabled after setting up
	 *	ADATE = 0			Disable AutoTriggering
	 *	ADIF = 0			Dont Care
	 *	ADIE = 1			ADC Conversion Enable
	 *	ADPS2:0 = 111			Prescalar 1024 | eff. clock = 15625 MHz
	 */
	ADCSRA = 0b10001111;

	/*	ACME = 0			AC Multiplex Input Disable
	 *	ADTS = 000			Dont Care
	 */
	ADCSRB = 0b00000000;

	/*	ADC5:2D = 1
	 */
	DIDR0 = 0b00111100;	
}

void setupTimer1 ()
{
	cli ();

	/*	COM1A:B1:0 = 00
	 *	WGM11:0 = 00			CTC for ICR1
	 */
	TCCR1A = 0b00000000;

	/*	ICNC1 = 0
	 *	ICES1 = 0
	 *	WGM13:2 = 11			CTC for ICR1
	 *	CS12:0 = 101			Prescalar 1024 | eff clock = 15625
	 */
	TCCR1B = 0b00001101;

	/*	FOC1A:B = 0
	 */
	TCCR1C = 0b00000000;

	TCNT1 = 0x00;

	OCR1A = 200;				// 13 miliSec

	TIMSK1 = 0b00000010;			// Set up Interrrupt for OCR1A
	
	sei ();
}

void powerReduction ()
{
	SMCR = 0b00000010;			// ADC Noise Reduction

	MCUCR = 0b01100000;
	MCUCR = 0b01000000;			// BOD Disable
	
	/*	PRTWI = 1
	 *	PRTIM2 = 1
	 *	PRTIM0 = 1
	 *	PRTIM1 = 0
	 *	PRSPI = 1
	 *	PRUSART0 = 1
	 *	PRADC = 0
	 */
	PRR = 0b11100110;
}

int main ()
{
	DDRB |= 0b00000011;

	setupADC ();
	powerReduction ();
	setupTimer1 ();

	while (1)
	{
		sei ();
		sleep_cpu ();
	}

	return 0;
}

ISR (TIMER1_COMPA_vect)
{
	cli ();

	ADCSRA |= 0b01000000;			// Start Conversion

	sei ();
}

ISR (ADC_vect)
{
	cli ();

	uint16_t valueADC, valL, valH;
	valL = ADCL;
	valH = ADCH;
	valueADC = (valH << 8) + valL;		// Get Value from ADC

	ADCSRA &= 0b10111111;			// Start bit to 0 (not necessary)

	if (ADMUX == 0x00)
	{
		ADMUX = 0b00000001;		// Next Conversion for THERMISTOR

		/*
		 *	LDR Setup
		 *	Darkness:		Resistance Increases / ADC Val Decreases
		 *	Brightness:		Resistance Decreases / ADC Val Increases
		 */

		if (valueADC <= 0x000A)
			PORTB |= 0b00000001;
		else
			PORTB &= 0b11111110;
	}
	else
	{
		ADMUX = 0b00000000;		// Next Conversion for LDR

		/*
		 *	THERMISTOR Setup
		 *	Cold:			Resistance Increases / ADC Val Decreases
		 *	Heat:			Resistance Decreases / ADC Val Increases
		 */

		if (valueADC >= 0x007E)
			PORTB |= 0b00000010;
		else
			PORTB &= 0b11111101;

	}

	TCNT1 = 0;

	sei();
}

