/*
 * display_number.c
 *
 * Created: 2/23/2020 9:24:34 AM
 *  Author: DELL
 */ 


#include <avr/io.h>
#include "library/global.h"
#include <util/crc16.h>
#include "library/keypad_ostad.h"

int main(void)
{
	uint8_t num;
	keypadInit();
	DDRD = 0xff;
	PORTD = 0; 
    while(1)
    {
		if ( (num = keyScan()) != 255)
		{
			PORTD = num;
		}
         
    }
}