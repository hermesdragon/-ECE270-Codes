/*					ELD Group 30
 *				Submitted by :
 *					Sidharth Sharma __ 2014163
 *					
 */
 
 /*		This code makes the LED at pin 13 blink at freq of approx. 1 Hz
 */

#include <stdint.h>

int main ()
{
	volatile unsigned char *dataDirection_B = (unsigned char *) 0b00100100;
	volatile unsigned char *portB = (unsigned char *) 0b00100101;
	
	*dataDirection_B |= 0b00100000;
	
	while (1)
	{
		*portB ^= 0b00100000;
		uint16_t temp, newtemp;
		for (temp = 0; temp < 1000; temp ++)
			for (newtemp = 0; newtemp < 1000; newtemp ++)
			{}
	}
	return 0;
}
