/* ---------------------------------------------------------------------------------------------------
 [FILE NAME]: <Application1.c>
 [AUTHOR(S)]: <Ahmed Hazza'>
 [DATE CREATED]: <Sep 27, 2015>
 [DESCRIPTION]: <Contains the main function of the program>
 ---------------------------------------------------------------------------------------------------*/

#include "micro_config.h"

volatile uint8 g_choice = 0; /*  holds a value depends on the message recived using UART from the Microcontroller 2
, Modified in the ISR in uart.c file */

volatile uint8 second = 0; /*holds the number of seconds counted by the Timer0, Modified in the ISR*/

int main(void)
{

	/*------------------------------------------------All Variables---------------------------------------------------*/

	uint8 flag = 0;
	uint8 val; /*to read the value from EEPROM in it*/
	uint8 a_firstPass[6]; /*Holds the first entered password*/
	uint8 a_secondPass[6]; /*Holds the second entered password*/
	uint8 compare = 0; /* holds the return value of "strcmp" function when comparing 2 password  */
	uint8 a_message[7];/* contains the string to be sent by UART_sendString() */
	uint8 inputChoise; /* Contains the user choice to open the door or change the password */
	uint8 state = 0; /**/
	uint8 wrong_Counter = 0;/*Contains the number of wrong password trials by the user*/

	/*------------------------------------------------Modules Initialization------------------------------------------*/

	LCD_init(); /* initialize LCD */
	UART_init(); /* initialize UART */
	sei();
	/*Enable global interrupts */
	/*-----------------------------------------------------------------------------------------------------------------*/

	val = eepromReadByte(0x0D); //Read a value (0x05) from address (0x0D) in Internal EEPROM to check if the first time
	if (val != 0x05)
	{
		flag = 0;
	}
	else if (val == 0x05)
	{
		flag = 1;
	}

	while (1)
	{

		if (flag == 0)
		{

			LCD_displayStringRowColumn(0, 0, "Enter New pass:");
			LCD_displayStringRowColumn(1, 0, "ON:ENTER X:CLEAR");
			_delay_ms(2000);
			LCD_displayStringRowColumn(1, 0, "                ");
			getPassword(a_firstPass);

			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "ReEnter The pass");
			getPassword(a_secondPass);

			compare = strcmp(a_firstPass, a_secondPass);

			if (compare == 0)
			{

				eepromWriteByte(0x0D, 0x05);
				flag = 1;

				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 3, "password");
				LCD_displayStringRowColumn(1, 4, "Match");
				_delay_ms(2000);
				prepareToSend(a_firstPass, a_message);
				UART_sendByte(NEW_PASSWORD);
				UART_sendString(a_message);

			}
			else
			{

				flag = 0;
				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 0, "pass NOT MATCH");
				LCD_displayStringRowColumn(1, 0, "Please ReEnter");
				_delay_ms(2000);

			}

		}
		else if (flag == 1)
		{

			if (state == 0)
			{

				LCD_displayStringRowColumn(0, 0, "- : Open Door   ");
				LCD_displayStringRowColumn(1, 0, "+ : Change pass");
				inputChoise = KeyPad_getPressedKey();

				if (inputChoise == '+')
				{

					state = 1;

					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 0, "Current pass: ");
					getPassword(a_firstPass);

					prepareToSend(a_firstPass, a_message);
					UART_sendByte(CHANGE_PASSWORD);
					UART_sendString(a_message);

				}
				else if (inputChoise == '-')
				{

					state = 1;

					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 0, "Enter pass: ");
					getPassword(a_firstPass);

					prepareToSend(a_firstPass, a_message);
					UART_sendByte(OPEN_DOOR);
					UART_sendString(a_message);

				}

			}
			else if (state == 1)
			{

				if (g_choice == 1)
				{

					g_choice = 0;

					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 0, "Door Is Opening");
					timer0_init_normal_mode();
					while (second < 6)
						;
					second = 0;
					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 0, "Door Is Closing");
					timer0_init_normal_mode();
					while (second < 6)
						;
					second = 0;
					state = 0;

				}
				else if (g_choice == 2)
				{

					g_choice = 0;

					wrong_Counter++;
					if (wrong_Counter == 3)
					{
						LCD_clearScreen();
						LCD_displayStringRowColumn(0, 0, "     ERROR      ");
						timer0_init_normal_mode();
						while (second != 45)
							;
						second = 0;
						wrong_Counter = 0;
						state = 0;
						continue;
					}

					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 0, "Wrong password    ");
					_delay_ms(2000);

					state = 0;

				}
				else if (g_choice == 3)
				{

					g_choice = 0;

					LCD_displayStringRowColumn(0, 0, "New password: ");
					LCD_displayStringRowColumn(1, 0, "                ");
					getPassword(a_firstPass);

					LCD_displayStringRowColumn(0, 0, "Reenter password   ");
					LCD_displayStringRowColumn(1, 0, "                ");
					getPassword(a_secondPass);

					compare = strcmp(a_firstPass, a_secondPass);

					if (compare == 0)
					{
						LCD_displayStringRowColumn(0, 0, "password Match   ");
						LCD_displayStringRowColumn(1, 0, "                ");
						_delay_ms(2000);

						prepareToSend(a_firstPass, a_message);
						UART_sendByte(CHANGED_PASSWORD);
						UART_sendString(a_message);

						state = 0;

					}
					else
					{

						LCD_displayStringRowColumn(0, 0, "pass NOT Match  ");
						LCD_displayStringRowColumn(1, 0, "                ");
						_delay_ms(2000);

						state = 0;
					}

				}
				else if (g_choice == 4)
				{

					g_choice = 0;

					LCD_displayStringRowColumn(0, 0, "Wrong password  ");
					LCD_displayStringRowColumn(1, 0, "                ");
					_delay_ms(2000);

					state = 0;

				}
			}
		}

	}

}
