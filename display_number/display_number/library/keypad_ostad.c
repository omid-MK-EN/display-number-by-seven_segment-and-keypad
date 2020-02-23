#include <avr/io.h>
#include "../library/global.h"
#include <util/delay.h>
#include <inttypes.h>
#include "../library/keypad.h"


/*****************global variables declaration***************************/
//static uint8_t keypad[4][3] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}, {'*', '0', '#'} };
//static uint8_t keypad[4][3] = { {'*', '0', '#'}, {'7', '8', '9'}, {'4', '5', '6'}, {'1', '2', '3'} };
#if KEYPAD43
	static uint8_t keypad[4][3] = { {7, 8, 9},
									{4, 5, 6},
									{1, 2, 3},
									{'*', 0, '#'} };
#else
	static uint8_t keypad[4][4] = { {7, 8, 9, 'A'},
									{4, 5, 6, 'B'},
									{1, 2, 3, 'C'},
									{'*', 0, '#', 'D'} };
#endif

/****************functions prototypes*************************************/
//static uint8_t keyReleased(void);
//static uint8_t keyPressed(void);

/***********************************************************************/
void keypadInit(void){
	#if KEYPAD43	
		KEY_DDR = 0x0f;
		KEY_PORT = 0x70;
	#else
		KEY_DDR = 0x0f;
		KEY_PORT = 0xf0;
	#endif // KEYPAD43
}
/***********************************************************************/
static uint8_t keyReleased(void) {
	#if KEYPAD43
		KEY_PORT = 0x70;
		_delay_ms(Delay);
		if((KEY_PIN & 0x70) == 0x70)
			return 1;
		else
			return 0;
	#else
		KEY_PORT = 0xf0;
		_delay_ms(Delay);
		if((KEY_PIN & 0xf0) == 0xf0)
			return 1;
		else
			return 0;		
	#endif	
}
/***********************************************************************/
static uint8_t keyPressed(void) {
	#if KEYPAD43
		KEY_PORT = 0x70;
		_delay_ms(Delay);
		if( (KEY_PIN & 0x70) != 0x70 ) {
			_delay_ms(20);
			if( (KEY_PIN & 0x70) != 0x70)
				return 1;
		}
		return 0;
	#else
		KEY_PORT = 0xf0;
		_delay_ms(Delay);
		if( (KEY_PIN & 0xf0) != 0xf0 ) {
			_delay_ms(20);
			if( (KEY_PIN & 0xf0) != 0xf0)
				return 1;
		}
		return 0;
	#endif
	
}
/***********************************************************************/
uint8_t keyScan(void) {

	uint8_t key = 0;

	if( keyPressed() ) {

		for(uint8_t row_num = 0; row_num < 4; row_num++) {

			KEY_PORT = 0xFF;
			cbi(KEY_PORT, row_num);
			_delay_ms(Delay);

			if(! CHECKBIT(KEY_PIN, 4)) 			
				key = keypad[row_num][0];

			else if(! CHECKBIT(KEY_PIN, 5)) 	
				key = keypad[row_num][1];

			else if(! CHECKBIT(KEY_PIN, 6)) 	
				key = keypad[row_num][2];

		#if !KEYPAD43
			else if(! CHECKBIT(KEY_PIN, 7)) 	
				key = keypad[row_num][3];				
		#endif			
		}
		while(!keyReleased());
		return key;
	}
	else
	return NOKEY;
}
