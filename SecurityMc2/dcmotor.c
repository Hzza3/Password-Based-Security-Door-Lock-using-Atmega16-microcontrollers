/*
 * dcmotor.c
 *
 *  Created on: Oct 2, 2015
 *      Author: Hazza3
 */

#include "dcmotor.h"
#include <avr/io.h>
void DCMOTOR_Init()
{
	MOTOR_DIRECTION |= (1 << IN1); /* configure IN1 pin as output pin*/
	MOTOR_DIRECTION |= (1 << IN2); /* configure IN1 pin as output pin*/

	/*Motor is stop at the beginning*/
	MOTOR_OUTPUT &= ~((1 << IN1) | (1 << IN2));
}
void DCMOTOR_onClockWise(uint16 duty_cycle)
{
	/* Direction of the DC Motor*/
	MOTOR_OUTPUT |= (1 << IN1);
	MOTOR_OUTPUT &= ~(1 << IN2);

	/* Timer 1 Fast PWM mode*/
	TCNT1 = 0; //initial timer value
	ICR1 = 60000; //top value
	OCR1A = duty_cycle;

	DDRD = DDRD | (1 << PD5); //set OC1A as output pin --> pin where the PWM signal is generated from MC.

	/* Pin Description:
	 * FOC0 = 0 for PWM Mode
	 * WGM10=1 for Fast PWM Mode
	 * WGM11=1 for Fast PWM Mode
	 * WGM12=1 for Fast PWM Mode
	 * WGM13=1 for Fast PWM Mode
	 * COM1A0=0 Clear OC0 on compare match(Non-Inverting Mode)
	 * COM1A1=1 Clear OC0 on compare match(Non-Inverting Mode)
	 * CS10=1freq=F_CPU
	 * CS11=0 freq=F_CPU
	 * CS12=0 freq=F_CPU
	 */
	TCCR1A = (1 << WGM11) | (1 << COM1A1);
	TCCR1A &= ~(1 << FOC1A);
	TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10);
}

void DCMOTOR_onAntiClockWise(uint16 duty_cycle)
{
	/* Direction of the DC Motor*/
	MOTOR_OUTPUT &= ~(1 << IN1);
	MOTOR_OUTPUT |= (1 << IN2);

	/* Timer 1 Fast PWM mode*/
	TCNT1 = 0; //initial timer value
	ICR1 = 60000; //top value
	OCR1A = duty_cycle;

	DDRD = DDRD | (1 << PD5); //set OC1A as output pin --> pin where the PWM signal is generated from MC.

	/* Pin Description:
	 * FOC0 = 0 for PWM Mode
	 * WGM10=1 for Fast PWM Mode
	 * WGM11=1 for Fast PWM Mode
	 * WGM12=1 for Fast PWM Mode
	 * WGM13=1 for Fast PWM Mode
	 * COM1A0=0 Clear OC0 on compare match(Non-Inverting Mode)
	 * COM1A1=1 Clear OC0 on compare match(Non-Inverting Mode)
	 * CS10=1freq=F_CPU
	 * CS11=0 freq=F_CPU
	 * CS12=0 freq=F_CPU
	 */
	TCCR1A = (1 << WGM11) | (1 << COM1A1);
	TCCR1A &= ~(1 << FOC1A);
	TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10);
}

void DCMOTOR_stop()
{
	MOTOR_OUTPUT &= ~((1 << IN1) | (1 << IN2));
}
