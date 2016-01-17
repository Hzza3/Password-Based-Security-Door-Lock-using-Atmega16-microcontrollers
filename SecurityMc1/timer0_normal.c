/* ---------------------------------------------------------------------------------------------------
 [FILE NAME]: <timer0_normal.h>
 [AUTHOR(S)]: <Ahmed Hazza'>
 [DATE CREATED]: <Oct 3, 2015>
 [DESCRIPTION]: <Contains functions implementation to handle the timer0 in normal mode>
 ---------------------------------------------------------------------------------------------------*/

#include "micro_config.h"
#include "timer0_normal.h"

#define NUMBER_OF_OVERFLOWS_PER_SECOND 32 /* holds the number of timer overflows each 1 second */

volatile uint8 g_tick = 0; /* counts the number of overflows starting when the timer starts, incremented and setted back to zero in the ISR*/
extern volatile uint8 second; /* counts the number of seconds starting when the timer starts, incremented and resetted back to zero in the ISR */

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
