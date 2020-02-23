/******************************************************************************************
 *
 * this library helps you using different keypads like 3x4 or 4x4
 * there is a little delay between each scan that must be considered
 * keypad[][] array should be changed based on your keypad style and characters that you have on it.
 * there are two example of this array that can help you.
 * always consider two important simple functions based on your keypad and hard-wire.
 * key_pressed() and key_released().
 * connect rows to low nibble
 * connect colums to high nibble
*******************************************************************************************/
#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <avr/io.h>

#define KEY_PORT	PORTC
#define KEY_DDR		DDRC
#define KEY_PIN		PINC

#define NOKEY 0xff
#define Delay 3

#define KEYPAD43	1

void keypadInit(void);

uint8_t keyScan(void);

#endif /* KEYPAD_H_ */
