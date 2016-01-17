/*
 * password.c
 *
 *  Created on: Sep 27, 2015
 *      Author: Hazza3
 */
#define BUTTON_DELAY 250
#include "password.h"
#include <util/delay.h>
void getPassword(uint8 array[]) {
	sint8 i;
	uint8 key;
	for (i = 0; i < 5; i++) {
		key = KeyPad_getPressedKey();
		if (key == '*') {
			LCD_displayStringRowColumn(1, 0, "                ");
			i = -1;
			continue;
		} else if ((key >= 0) && (key <= 9)) {
			array[i] = key;
		} else {
			i -= 1;
			continue;
		}
		_delay_ms(BUTTON_DELAY);
		LCD_goToRowColumn(1, i + 3);
		LCD_displayCharacter('*');

		if (i == 4) {
			key = KeyPad_getPressedKey();
			if (key == 13) {
				break;
			} else if (key == '*') {
				LCD_displayStringRowColumn(1, 0, "                ");
				i = -1;
				continue;
			}
		}
	}

}

uint8 compareTwoPasswords(uint8 arr1[], uint8 arr2[]) {
	uint8 count = 0;
	sint8 i;
	for (i = 0; i < 5; i++) {
		if (arr1[i] == arr2[i]) {
			count++;
		}
	}
	return count;
}

void prepareToSend(uint8 array[], uint8 array2[]) {
	sint8 i = 0;
	for (i = 0; i < 6; i++) {
		array2[i] = array[i];
		if (i == 5) {
			array2[5] = '#';
			//break;
		}
	}
}

