/*
 * UART.c
 *
 * Created: 2/19/2014 8:07:58 PM
 * Author: Mohamed Tarek
 */

#include "uart.h"

extern volatile uint8 g_choice;
void UART_init(void) {
	UCSRA = (1 << U2X); /* U2X = 1 for double transmission speed */
	/************************** UCSRB Description **************************
	 * RXCIE = 1 Enable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = 0 For 8-bit data mode
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/
	UCSRB = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);

	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = 00 Disable parity bit
	 * USBS    = 0 One stop bit
	 * UCSZ1:0 = 11 For 8-bit data mode
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/
	UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);

	/* baud rate=9600 & Fosc=8MHz -->  UBBR=( Fosc / (8 * baud rate) ) - 1 = 103 */
	UBRRH = 0;
	UBRRL = 103;
}

void UART_sendByte(const uint8 data) {
	/* UDRE flag is set when the Tx buffer (UDR) is empty and ready for 
	 * transmitting a new byte so wait until this flag is set to one */
	while (BIT_IS_CLEAR(UCSRA, UDRE)) {
	}
	/* Put the required data in the UDR register and it also clear the UDRE flag as 
	 * the UDR register is not empty now */
	UDR = data;
	/************************* Another Method *************************
	 UDR = data;
	 while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transimission is complete TXC = 1
	 SET_BIT(UCSRA,TXC); // Clear the TXC flag
	 *******************************************************************/
}

uint8 UART_recieveByte(void) {
	/* RXC flag is set when the UART receive data so wait until this 
	 * flag is set to one */
	while (BIT_IS_CLEAR(UCSRA, RXC)) {
	}
	/* Read the received data from the Rx buffer (UDR) and the RXC flag 
	 will be cleared after read this data */
	return UDR;
}

void UART_sendString(const uint8 *Str) {
	uint8 i = 0;
	while (Str[i] != '\0') {
		UART_sendByte(Str[i]);
		i++;
	}
	/************************* Another Method *************************
	 while(*Str != '\0')
	 {
	 UART_sendByte(*Str);
	 Str++;
	 }
	 *******************************************************************/
}

void UART_receiveString(uint8 *Str) {
	uint8 i = 0;
	Str[i] = UART_recieveByte();
	while (Str[i] != '#') {
		i++;
		Str[i] = UART_recieveByte();
	}
	Str[i] = '\0';
}

ISR(USART_RXC_vect) {
	uint8 key = UART_recieveByte();
	if (key == CORRECT_PASSWORD) {
		g_choice = 1;

	} else if (key == WRONG_PASSWORD) {
		g_choice = 2;
	}
	else if(key == PRECEDE_CHANGE)
	{
		g_choice = 3;
	}
	else if(key == DONT_CHANGE)
	{
		g_choice = 4;
	}

}
