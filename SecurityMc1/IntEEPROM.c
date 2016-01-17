/* ---------------------------------------------------------------------------------------------------
 [FILE NAME]: <IntEEPROM.c>
 [AUTHOR(S)]: <Ahmed Hazza'>
 [DATE CREATED]: <Sep 27, 2015>
 [DESCRIPTION]: <Contains functions implementation to Write and Read from the internal EEPROM>
 ---------------------------------------------------------------------------------------------------*/

#include "IntEEPROM.h"

void eepromWriteByte(unsigned short a_addr, unsigned char a_data)
{

	/* Wait for completion of previous write */
	while (EECR & (1 << EEWE))
		;
	/* Set up address and data registers */
	EEAR = a_addr;
	EEDR = a_data;
	/* Write logical one to EEMWE */
	EECR |= (1 << EEMWE);
	/* Start EEPROM write by setting EEWE */
	EECR |= (1 << EEWE);
}

unsigned char eepromReadByte(unsigned short a_addr)
{
	/* Wait for completion of previous write */
	while (EECR & (1 << EEWE))
		;
	/* Set up address register */
	EEAR = a_addr;
	/* Start EEPROM read by writing EERE */
	EECR |= (1 << EERE);
	/* Return data from data register */
	return EEDR;
}
