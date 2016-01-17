/*
 * micro_config.h
 *
 * Created: 1/3/2015 11:28:01 PM
 *  Author: Mohamed Tarek
 */ 


#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_


#ifndef F_CPU
#define F_CPU 8000000UL //8MHz Clock frequency
#endif  
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include "std_types.h"
#include "common_macros.h"
#include "uart.h"
#include "uart_messages.h"
#include "password.h"
#include "lcd.h"
#include "keypad.h"
#include "Ex_EEPROM_I2C_24c256.h"
#include "dcmotor.h"
#include "timer0_normal.h"
#endif /* MICRO_CONFIG_H_ */
