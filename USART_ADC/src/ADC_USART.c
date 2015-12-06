#include <stdio.h>
#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "uartLibrary.h"

uint16_t val_LDR, val_NTC;

void setupADC ()
{
	cli ();

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

	sei ();
}

void setupTimer1 ()
{
	cli ();

	/*	COM1A:B1:0 = 00
	 *	WGM11:0 = 00			CTC for COMPA
	 */
	TCCR1A = 0b00000000;

	/*	ICNC1 = 0
	 *	ICES1 = 0
	 *	WGM13:2 = 01			CTC for COMPA
	 *	CS12:0 = 101			Prescalar 1024 | eff clock = 15625
	 */
	TCCR1B = 0b00001101;

	/*	FOC1A:B = 0
	 */
	TCCR1C = 0b00000000;

	TCNT1 = 0x00;

	OCR1A = 46877;				// 3 Sec

	TIMSK1 = 0b00000010;			// Set up Interrrupt for OCR1A
	
	sei ();
}

void powerReduction ()
{
	SMCR = 0b00000000;			// Idle Mode

	MCUCR = 0b01100000;
	MCUCR = 0b01000000;			// BOD Disable
	
	/*	PRTWI = 1
	 *	PRTIM2 = 1
	 *	PRTIM0 = 1
	 *	PRTIM1 = 0
	 *	PRSPI = 1
	 *	PRUSART0 = 0
	 *	PRADC = 0
	 */
	PRR = 0b11100100;
}

int main ()
{
	DDRB |= 0b00000011;

	setupADC ();
	powerReduction ();
	setupTimer1 ();
	uart_init();
	stdout = &uart_output;
	stdin  = &uart_input;

	printf ("STARTING PROGRAM...\n");

	ADCSRA |= 0b01000000;			// Start Conversion

	while (1)
	{
		SMCR |= 0b00000001;
		sei ();
		sleep_cpu ();
	}

	return 0;
}

ISR (TIMER1_COMPA_vect)
{
	cli ();

	SMCR &= 0b11111110;

	bool LED_LDR, LED_NTC;

	if (PORTB & 0b00000001)			// Check LDR_LED Status
		LED_LDR = true;
	else
		LED_LDR = false;

	if (PORTB & 0b00000010)			// Check NTC Th_LED Status
		LED_NTC = true;
	else
		LED_NTC = false;

	printf ("\n");
	printf ("ADC Statistics\n");
	printf ("LDR:\n\tValue = 0x%X\n", val_LDR);
	printf ("\tLED_LDR = %s\n", LED_LDR ? "ON" : "OFF");
	printf ("NTC THERMISTOR:\n\tValue = 0x%X\n", val_NTC);
	printf ("\tLED_NTC = %s\n", LED_NTC ? "ON" : "OFF");
	printf ("\n");

	sei ();
}

ISR (USART_RX_vect)
{
	cli ();

	SMCR &= 0b11111110;

	char input = getchar ();
	bool LED_LDR, LED_NTC;

	if (PORTB & 0b00000001)			// Check LDR_LED Status
		LED_LDR = true;
	else
		LED_LDR = false;

	if (PORTB & 0b00000010)			// Check NTC Th_LED Status
		LED_NTC = true;
	else
		LED_NTC = false;

	if (input == 'a' || input == 'A')	// Show stats if "a" pressed
	{
		printf ("\n");
		printf ("LED Statistics via Interrupt\n");
		printf ("LED_LDR = %s\n", LED_LDR ? "ON" : "OFF");
		printf ("LED_NTC = %s\n", LED_NTC ? "ON" : "OFF");
		printf ("\n");
	}
	else
	{
		printf ("\n");
		printf ("Press \"A\" for LED Statistics\n");
		printf ("\n");
	}

	sei ();
}

ISR (ADC_vect)
{
	cli ();

	SMCR &= 0b11111110;

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

		val_LDR = valueADC;

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

		val_NTC = valueADC;

		if (valueADC >= 0x007E)
			PORTB |= 0b00000010;
		else
			PORTB &= 0b11111101;

	}

	ADCSRA |= 0b01000000;			// Start Conversion

	sei();
}