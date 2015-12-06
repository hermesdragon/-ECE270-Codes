/*			ELD Assignment :: Display Names on LCD
 *			by
 *			Sidharth Sharma : 2014163
 *			
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define	lcd_Clear		0b00000001
#define	lcd_Home		0b00000010
#define	lcd_EntryMode		0b00000110
#define	lcd_DisplayOff		0b00001000
#define	lcd_DisplayOn		0b00001100
#define	lcd_FunctionReset	0b00110000
#define	lcd_FunctionSet4bit	0b00101000

// Names to be Displayed
uint8_t name_1[] = "Gursimran Singh";
uint8_t name_2[] = "Vipin";

//Function Prototypes
void lcd_init (void );
void lcd_write_string (uint8_t *);
void lcd_write_character (uint8_t );
void lcd_write_instruction (uint8_t );
void lcd_write (uint8_t );

/*******************************************************************************************************************************/

int main (void )
{
	// PORTD 7, 6, 5, 4 set as Output for 4 data lines (Arduino pin no :: 7, 6, 5, 4 respectively)
	DDRD |= 0b11110000;

	// PORTB 1, 0 set as Output for Enable, Register Select respectively (Arduino pin no :: 9, 8 respectively)
	DDRB |= 0b00000011;

	lcd_init ();							// Initiate Reset Sequence for LCD Module

	while (1)
	{
		lcd_write_instruction (lcd_Home);
		_delay_ms (4);
		lcd_write_instruction (lcd_Clear);
		_delay_ms (4);

		lcd_write_string (name_1);
		_delay_ms (2000);

		lcd_write_instruction (lcd_Home);
		_delay_ms (4);
		lcd_write_instruction (lcd_Clear);
		_delay_ms (4);

		lcd_write_string (name_2);
		_delay_ms (2000);
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

void lcd_write_string (uint8_t theString[])
{
	volatile int i = 0;
	while (theString[i] != 0)
	{
		lcd_write_character (theString[i]);			// Write the String Character by Character
		i ++;
		_delay_us (80);						// Delay to allow the character to be written
	}
}

void lcd_write_character (uint8_t theData)
{
	PORTB |= 0b00000001;						// Select the Data Register :: [RS = 1]
	PORTB &= 0b11111101;						// Set Enable low to latch data :: [EN = 0]
	
	// ***** Writing the 8-bit Data in two parts *****
	lcd_write (theData);
	lcd_write (theData << 4);
}

void lcd_write_instruction (uint8_t theInstruction)
{
	PORTB &= 0b11111110;						// Setect thr Instruction Register :: [RS = 0]
	PORTB &= 0b11111101;						// Set Enable low to latch data :: [EN = 0]
	
	// ***** Writing the 8-bit Instruction in two parts *****
	lcd_write (theInstruction);
	lcd_write (theInstruction << 4);
}

void lcd_write (uint8_t theByte)
{
	// ***** Writing 4-bit Instruction *****
	// Considering just the upper nibble ie. lower 4 bits are not used

	PORTD &= 0b01111111;						// Set PORTD7 = 0
	if (theByte & 1 << 7)						// If Instruction_bit_3 (msb) is high
		PORTD |= 0b10000000;					// Set PORTD7 = 1

	PORTD &= 0b10111111;						// Set PORTD6 = 0
	if (theByte & 1 << 6)						// If Instruction_bit_2 is high
		PORTD |= 0b01000000;					// Set PORTD6 = 1

	PORTD &= 0b11011111;						// Set PORTD5 = 0
	if (theByte & 1 << 5)						// If Instruction_bit_1 is high
		PORTD |= 0b00100000;					// Set PORTD5 = 1

	PORTD &= 0b11101111;						// Set PORTD4 = 0
	if (theByte & 1 << 4)						// If Instruction_bit_0 (lsb) is high
		PORTD |= 0b00010000;					// Set PORTD4 = 1

	// ***** Giving the Enable Pulse *****
	PORTB |= 0b00000010;
	_delay_us (1);
	PORTB &= 0b11111101;
	_delay_us (1);
}
