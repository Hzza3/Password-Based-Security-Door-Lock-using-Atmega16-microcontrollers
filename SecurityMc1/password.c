/* ---------------------------------------------------------------------------------------------------
 [FILE NAME]: <password.h>
 [AUTHOR(S)]: <Ahmed Hazza'>
 [DATE CREATED]: <Sep 27, 2015>
 [DESCRIPTION]: <Contains functions implementation to handle the operation of taking 5 digit password from the user>
 ---------------------------------------------------------------------------------------------------*/

#include "password.h"
#include <util/delay.h>

#define BUTTON_DELAY 400 /*define a time value of each button press */

void getPassword(uint8 array[])
{
	sint8 i;
	uint8 key;
	for (i = 0; i < 5; i++)
	{
		key = KeyPad_getPressedKey();
		if (key == '*')
		{
			LCD_displayStringRowColumn(1, 0, "                ");
			i = -1;
			continue;
		}
		else if ((key >= 0) && (key <= 9))
		{
			array[i] = key;
		}
		else
		{
			i -= 1;
			continue;
		}
		_delay_ms(BUTTON_DELAY);
		LCD_goToRowColumn(1, i + 3);
		LCD_displayCharacter('*');

		if (i == 4)
		{
			key = KeyPad_getPressedKey();
			if (key == 13)
			{
				break;
			}
			else if (key == '*')
			{
				LCD_displayStringRowColumn(1, 0, "                ");
				i = -1;
				continue;
			}
		}
	}

}

void prepareToSend(uint8 array[], uint8 array2[])
{
	sint8 i = 0;
	for (i = 0; i < 6; i++)
	{
		array2[i] = array[i];
		if (i == 5)
		{
			array2[i] = '#';
			//break;
		}
	}
}
