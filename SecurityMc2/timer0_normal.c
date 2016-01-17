/*
 * timer0_normal.c
 *
 *  Created on: Oct 3, 2015
 *      Author: Hazza3
 */

#include "timer0_normal.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "micro_config.h"
#define NUMBER_OF_OVERFLOWS_PER_SECOND 32

volatile uint8 g_tick = 0;
extern volatile uint8 second;
/* Description :
 * For clock = 8Mhz and prescaler F_CPU/1024 every count will take 128 microsecond
 * so put initial timer counter=0  0 --> 255 (32ms per overflow)
 * so we need timer to overflow 31 times to get a 1 second
 */

void timer0_init_normal_mode(void)
{
	TCNT0 = 0; //timer initial value
	TIMSK |= (1 << TOIE0); //enable overflow interrupt
	/* Configure the timer control register
	 * 1. Non PWM mode FOC0=1
	 * 2. Normal Mode WGM01=0 & WGM00=0
	 * 3. Normal Mode COM00=0 & COM01=0
	 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
	 */
	TCCR0 = (1 << FOC0) | (1 << CS02) | (1 << CS00);
	second = 0;
}

ISR(TIMER0_OVF_vect)
{
	g_tick++;
	if (g_tick == NUMBER_OF_OVERFLOWS_PER_SECOND)
	{
		second++;
		g_tick = 0; //clear the tick counter again to count a new 0.5 second
	}
}
