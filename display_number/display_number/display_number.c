/*
 * display_number.c
 *
 * Created: 2/23/2020 9:24:34 AM
 *  Author: DELL
 */ 


#include <avr/io.h>
#include <stdlib.h>
#include "library/global.h"
#include <util/crc16.h>
#include "library/keypad_ostad.h"
#include "library/lcd.h"

void lcd_display(uint8_t, uint8_t, uint8_t);
return counter(void);

uint8_t hour = 0, min = 0, sec = 0, day = 0;
int main(void)
{
	uint8_t num;
	keypadInit();
	DDRD = 0xff;
	PORTD = 0; 
	lcd_init(LCD_DISP_ON_CURSOR);
    while(1)
    {
		num = counter();
		PORTD = num;
    }
}

void lcd_display(uint8_t sec, uint8_t min, uint8_t hour)
{
	char str[11];
	lcd_clrscr();
	lcd_gotoxy(0,2);
	itoa(hour, str,10);
	lcd_puts(str);
	lcd_puts(":");
	itoa(min, str,10);
	lcd_puts(str);
	lcd_puts(":");
	itoa(sec, str,10);
	lcd_puts(str);
}
uint8_t counter(void)
{
	
	
	sec++;
	
	if (sec == 59)
	{
		sec = 0;
		min++;
	}
	else if (min == 59)
	{
		min = 0;
		hour++;
	}
	else if (hour == 24)
	{
		day++;
		hour = 0;
		
	}
	lcd_display(sec, min, hour);
	return day;
}