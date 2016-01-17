/*
 * Application2.c
 *
 *  Created on: Sep 27, 2015
 *      Author: Hazza3
 */

#include "micro_config.h"

#define EEPROMSTART 0x0A

volatile uint8 g_choice = 0;
volatile uint8 recived_new[6];
volatile uint8 recived_open[6];
volatile uint8 recived_change[6];
volatile uint8 second = 0;
int main(void)
{

	sint8 i = 0;
	uint8 buffer[6];
	uint8 compare;
	uint8 write = 0, read = 0;
	uint8 wrong_counter = 0;

	UART_init();
	EEPROM_Init();
	DCMOTOR_Init();
	sei();

	DDRD |= (1 << PD2);
	while (1)
	{
		while (g_choice == 0)
			;
		compare = 5;
		if (g_choice == 1)
		{
			g_choice = 0;
			while (recived_new[i] != '\0')
			{
				write = recived_new[i];
				EEPROM_Write_Byte(0xAE, EEPROMSTART + i, write);
				_delay_ms(50);
				i++;
			}
			/*for (i = 0; i < 5; i++) {
			 EEPROM_Read_Byte(0xAE, EEPROMSTART + i, &read);
			 buffer[i] = read;
			 }
			 buffer[5] = '\0';
			 compare = strcmp(buffer, recived_new);
			 if(compare == 0) PORTB = 0b00001111;*/
		}
		else if (g_choice == 2)
		{
			g_choice = 0;
			for (i = 0; i < 5; i++)
			{
				EEPROM_Read_Byte(0xAE, EEPROMSTART + i, &read);
				buffer[i] = read;
			}
			buffer[5] = '\0';
			compare = strcmp(recived_open, buffer);
			if (compare == 0)
			{
				UART_sendByte(CORRECT_PASSWORD);
				//Open the door
				DCMOTOR_onAntiClockWise(30000);
				timer0_init_normal_mode();
				while (second != 6)
					;
				second = 0;

				DCMOTOR_onClockWise(30000);
				while (second != 6)
					;
				second = 0;

				DCMOTOR_stop();
				wrong_counter = 0;
			}
			else
			{
				UART_sendByte(WRONG_PASSWORD);
				wrong_counter++;
				if (wrong_counter == 3)
				{
					PORTD |= (1 << PD2);
					timer0_init_normal_mode();
					while (second != 45)
						;
					second = 0;
					PORTD &= ~(1 << PD2);
					wrong_counter = 0;
				}
			}

		}
		else if (g_choice == 3)
		{
			g_choice = 0;
			for (i = 0; i < 5; i++)
			{
				EEPROM_Read_Byte(0xAE, EEPROMSTART + i, &read);
				buffer[i] = read;
			}
			buffer[5] = '\0';
			compare = strcmp(recived_change, buffer);
			if (compare == 0)
			{
				UART_sendByte(PRECEDE_CHANGE);
			}
			else
			{
				UART_sendByte(DONT_CHANGE);
			}
		}
		else if (g_choice == 4)
		{
			g_choice = 0;
			i = 0;
			while (recived_change[i] != '\0')
			{
				write = recived_change[i];
				EEPROM_Write_Byte(0xAE, EEPROMSTART + i, write);
				_delay_ms(50);
				i++;
			}
		}
	}

	return 0;
}
