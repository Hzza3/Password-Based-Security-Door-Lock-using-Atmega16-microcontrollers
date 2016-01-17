/* ---------------------------------------------------------------------------------------------------
 [FILE NAME]: <IntEEPROM.h>
 [AUTHOR(S)]: <Ahmed Hazza'>
 [DATE CREATED]: <Sep 27, 2015>
 [DESCRIPTION]: <Contains functions prototypes to Write and Read from the internal EEPROM>
 ---------------------------------------------------------------------------------------------------*/

#ifndef INT_EEPROM_H_
#define INT_EEPROM_H_

#include <avr/io.h>
#include <util/delay.h>

/* ---------------------------------------------------------------------------------------------------------------
 [Function Name] :eepromWriteByte
 [Description] :This function is responsible for Writting in the internal EEPROM.
 [Args] :
 [in] unsigned short a_addr:
 This Argshall indicate the address of the location to write in in the EEPROM
 [in] unsigned char a_data:
 This Argshall indicate a 1 byte data to be written in the EEPROM
 [Returns] : void
 ---------------------------------------------------------------------------------------------------------------*/
void eepromWriteByte(unsigned short a_addr, unsigned char a_data);

/* ---------------------------------------------------------------------------------------------------------------
 [Function Name] :eepromReadByte
 [Description] :This function is responsible for Reading 1 byte from internal EEPROM.
 [Args] :
 [in] unsigned short a_addr:
 This Argshall indicate the address of the location to Read in the EEPROM
 [Returns] :

 ---------------------------------------------------------------------------------------------------------------*/

unsigned char eepromReadByte(unsigned short a_addr);

#endif /* INT_EEPROM_H_ */
