/*					ELD Assignment :: Debounce 4 Buttons
 *					by
 *					Sidharth Sharma : 2014163
 *					
 */

#define F_CPU 16000000UL

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#define	lcd_Clear		0b00000001
#define	lcd_Home		0b00000010
#define	lcd_EntryMode		0b00000110
#define	lcd_DisplayOff		0b00001000
#define	lcd_DisplayOn		0b00001100
#define	lcd_FunctionReset	0b00110000
#define	lcd_FunctionSet4bit	0b00101000
#define lcd_SetCursor		0b10000000
#define lcd_line_One		0b00000000
#define lcd_Line_Two		0b01000000

// Counters
char counter1[4] = "0";
char counter2[4] = "0";
uint8_t flag = -1;

//Function Prototypes
void lcd_init (void );
void lcd_write_string (char *);
void lcd_write_character (char );
void lcd_write_instruction (char );
void lcd_write (char );
void externalInterruptSetup ();
void pinchangeInterrupSetup ();

/*******************************************************************************************************************************/

int main (void )
{
	uint8_t bInput;
	// PORTD 7, 6, 5, 4 set as Output for 4 data lines (Arduino pin no :: 7, 6, 5, 4 respectively)
	DDRD |= 0b11110000;

	// PORTB 1, 0 set as Output for Enable, Register Select respectively (Arduino pin no :: 9, 8 respectively)
	DDRB |= 0b00000011;

	lcd_init ();							// Initiate Reset Sequence for LCD Module
	externalInterruptSetup ();					// Setup for INT0, INT1
	pinchangeInterrupSetup ();					// Setup for PCINT0, PCINT1

	while (1)
	{
		sei ();

		lcd_write_instruction (lcd_Home);
		_delay_ms (4);
		lcd_write_instruction (lcd_Clear);
		_delay_ms (4);

		lcd_write_string (counter1);				// Write counter 1
		_delay_ms (4);

		lcd_write_instruction (lcd_SetCursor | lcd_Line_Two);	// Change to Line 2
		_delay_ms (4);

		lcd_write_string (counter2);				// Write counter 2
		_delay_ms (4);
	}

	return 0;
}

/*******************************************************************************************************************************/

void lcd_init (void )
{
	_delay_ms (100);						// Initial PowerOn delay :: [min 40ms]		
	
	PORTB &= 0b11111110;						// Initially select Instruction Register :: [RS = 0]
	PORTB &= 0b11111101;						// Initially keep Enable low :: [EN = 0] (latch data)

	// ***** Starting the Reset Sequence for LCD Module *****

	// First Part
	lcd_write_instruction (lcd_FunctionReset);
	_delay_ms (10);							// Required Delay :: [min 4.1ms]

	// Second Part
	lcd_write_instruction (lcd_FunctionReset);
	_delay_us (200);						// Required Delay :: [min 100us]

	// Third Part
	lcd_write_instruction (lcd_FunctionReset);
	_delay_us (200);						// Required Delay :: [min 100us]

	// ***** Reset Sequence Complete *****

	// ***** Setting the LCD Module to 4-bit operation mode *****
	
	lcd_write_instruction (lcd_FunctionSet4bit);			// Set 4-bit mode
	_delay_us (80);							// Required Delay :: [min 40us]

	lcd_write_instruction (lcd_FunctionSet4bit);			// Set Mode, lines and Font
	_delay_us (80);							// Required delay :: [min 40us]

	// ***** Done Setting the LCD Module to 4-bit operation mode *****

	lcd_write_instruction (lcd_DisplayOff);				// Turn Display Off
	_delay_ms (80);							// Required delay :: [min 40us]

	lcd_write_instruction (lcd_Clear);				// Clear Display RAM
	_delay_ms (4);							// Required delay :: [min 1.64ms]

	lcd_write_instruction (lcd_EntryMode);				// Set Shift Characteristics
	_delay_us (80);							// Required delay :: [min 40us]

	lcd_write_instruction (lcd_DisplayOn);				// Turn Display Back On
	_delay_us (80);							// Required delay :: [min 40us]
}

void lcd_write_string (char theString[])
{
	volatile int i = 0;
	while (theString[i] != '\0')
	{
		lcd_write_character (theString[i]);			// Write the String Character by Character
		i ++;
		_delay_us (80);						// Delay to allow the character to be written
	}
}

void lcd_write_character (char theData)
{
	PORTB |= 0b00000001;						// Select the Data Register :: [RS = 1]
	PORTB &= 0b11111101;						// Set Enable low to latch data :: [EN = 0]
	
	// ***** Writing the 8-bit Data in two parts *****
	lcd_write (theData);
	lcd_write (theData << 4);
}

void lcd_write_instruction (char theInstruction)
{
	PORTB &= 0b11111110;						// Setect thr Instruction Register :: [RS = 0]
	PORTB &= 0b11111101;						// Set Enable low to latch data :: [EN = 0]
	
	// ***** Writing the 8-bit Instruction in two parts *****
	lcd_write (theInstruction);
	lcd_write (theInstruction << 4);
}

void lcd_write (char theByte)
{
	// ***** Writing 4-bit Instruction *****
	// Considering just the upper nibble ie. lower 4 bits are not used

	PORTD &= theByte & (0b11110000);		// Setting the PD7, PD6, PD5, PD4 as upper nibble of theByte
	PORTD |= theByte & (0b11110000);		// Setting the PD7, PD6, PD5, PD4 as upper nibble of theByte

	// ***** Giving the Enable Pulse *****
	PORTB |= 0b00000010;
	_delay_us (1);
	PORTB &= 0b11111101;
	_delay_us (1);
}

void externalInterruptSetup ()
{
	cli ();

	PORTD |= 0b00001100;

	EIMSK |= 1 << INT0;
	EIMSK |= 1 << INT1;

	EICRA |= 1 << ISC01;
	
	EICRA |= 1 << ISC11;

	sei ();	
}

void pinchangeInterrupSetup ()
{
	// For LED 1

	DDRB &= 0b11111011;
	DDRB |= 0b00001000;
	
	PORTB |= 0b00000100;
	PORTB |= 0b00001000; 

	PCICR |= (1 << PCIE0);
	PCMSK0 |= (1 << PCINT2);

	// // For LED 2

	DDRC &= 0b11111110;
	DDRB |= 0b00010000;

	PORTC |= 0b00000001;
	PORTB |= 0b00010000;

	PCICR |= (1 << PCIE1);
	PCMSK1 |= 1 << PCINT8;

	sei ();
}

ISR (INT0_vect)
{
	cli ();

	flag = 0;

	TIMSK1 = 0b00000010;					// Enable OCIE1A Interrupt and none other | OCIEA ==> Bit_1 = 1
	TCCR1A = 0b00000000;					// COM1A1:0, COM1B1:0, RR, WGM11:10 set to 0

	TCNT1 = 0;
	TCCR1B = 0;
	TCCR1B |= 0b00001000;					// Set Mode = CTC | WGM12 ==> Bit_3 = 1
	TCCR1B |= 0b00000101;					// CS12:10 ==> Bits_2:0 = 101 | Set prescaler = 1024 | Ck = 16 MHz / 1024 = 15625

	OCR1A = 157;

	sei ();

	sleep_cpu ();
}

ISR (INT1_vect)
{
	cli ();

	flag = 1;

	TIMSK1 = 0b00000010;					// Enable OCIE1A Interrupt and none other | OCIEA ==> Bit_1 = 1
	TCCR1A = 0b00000000;					// COM1A1:0, COM1B1:0, RR, WGM11:10 set to 0

	TCNT1 = 0;
	TCCR1B = 0;
	TCCR1B |= 0b00001000;					// Set Mode = CTC | WGM12 ==> Bit_3 = 1
	TCCR1B |= 0b00000101;					// CS12:10 ==> Bits_2:0 = 101 | Set prescaler = 1024 | Ck = 16 MHz / 1024 = 15625

	OCR1A = 157;

	sei ();

	sleep_cpu ();
}

ISR (PCINT0_vect)
{
	cli ();

	flag = 2;

	TIMSK1 = 0b00000010;					// Enable OCIE1A Interrupt and none other | OCIEA ==> Bit_1 = 1
	TCCR1A = 0b00000000;					// COM1A1:0, COM1B1:0, RR, WGM11:10 set to 0

	TCNT1 = 0;
	TCCR1B = 0;
	TCCR1B |= 0b00001000;					// Set Mode = CTC | WGM12 ==> Bit_3 = 1
	TCCR1B |= 0b00000101;					// CS12:10 ==> Bits_2:0 = 101 | Set prescaler = 1024 | Ck = 16 MHz / 1024 = 15625

	OCR1A = 157;

	sei ();

	sleep_cpu ();

	sei ();
}

ISR (PCINT1_vect)
{
	cli ();

	flag = 3;

	TIMSK1 = 0b00000010;					// Enable OCIE1A Interrupt and none other | OCIEA ==> Bit_1 = 1
	TCCR1A = 0b00000000;					// COM1A1:0, COM1B1:0, RR, WGM11:10 set to 0

	TCNT1 = 0;
	TCCR1B = 0;
	TCCR1B |= 0b00001000;					// Set Mode = CTC | WGM12 ==> Bit_3 = 1
	TCCR1B |= 0b00000101;					// CS12:10 ==> Bits_2:0 = 101 | Set prescaler = 1024 | Ck = 16 MHz / 1024 = 15625

	OCR1A = 157;

	sei ();

	sleep_cpu ();

	sei ();
}


ISR (TIMER1_COMPA_vect)
{
	cli ();

	if (flag == 1)
	{
		int integer = atoi (counter2);			// Convert to int

		uint8_t input = PIND;				// Read status of Interrupt pin
		input &= 0b00001000;				// Mask
		if (input == 0)					// If it is still Low
			integer --;				// Decrement

		if (integer == -255)				// If counter reaches limit (set by me)
			integer = 0;				// Turn to 0

		sprintf (counter2, "%d", integer);		// Turn back to string
	}
	else if (flag == 0)
	{
		int integer = atoi (counter1);			// Convert to int

		uint8_t input = PIND;				// Read status of input pin
		input &= 0b00000100;				// Mask
		if (input == 0)					// If it is still low
			integer ++;				// Increment

		if (integer == 256)				// Limit (set by me but no need)
			integer = 0;

		sprintf (counter1, "%d", integer);		// Turn back to String
	}
	else if (flag == 2)
	{
		uint8_t input = PINB;				// Take input again after 10msec
		input &= 0b00000100;				// Mask for Interrupt pin
		if (input == 0)					// If it is still low
			PORTB ^= 0b00001000;			// Toggle
	}
	else if (flag == 3)
	{
		uint8_t input = PINC;				// Take input again after 10msec
		input &= 0b00000001;				// Mask for interrupt pin
		if (input == 0)					// If it is still low
			PORTB ^= 0b00010000;			// Toggle
	}

	TIMSK1 = 0b00000000;					// Resetting timer
	TCCR1A = 0b00000000;
	TCCR1B = 0b00000000;

	sei ();
}
