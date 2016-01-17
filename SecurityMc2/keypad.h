/*
 * Keypad.h
 *
 * Created: 4/3/2014 3:02:56 PM
 *  Author: Mohamed Tarek
 */ 

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

#define N_col 4
#define N_row 4

/* Keypad Port Configurations */
#define KEYPAD_PORT_OUT PORTC
#define KEYPAD_PORT_IN  PINC
#define KEYPAD_PORT_DIR DDRC

/*
 * Function responsible for getting the pressed keypad key
 */
uint8 KeyPad_getPressedKey(void);

/*
 * Function responsible for mapping the switch number in the keypad to 
 * its corresponding functional number in the proteus for 4x3 keypad 
 */
uint8 KeyPad_4x3_adjustKeyNumber(uint8 button_number);

/*
 * Function responsible for mapping the switch number in the keypad to 
 * its corresponding functional number in the proteus for 4x4 keypad  
 */
uint8 KeyPad_4x4_adjustKeyNumber(uint8 button_number);

#endif /* KEYPAD_H_ */
