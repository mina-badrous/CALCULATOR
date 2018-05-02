/*
 * keypad_config.h
 *
 * Created: 4/28/2018 1:11:40 PM
 */ 

//-----------------------------------------------
#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_
//--------------------------------------------------------
#include "avr/io.h"
//-------------------------------------------------------uncomment this to enable no wait
#define NO_KEYPAD_WAIT
#define KEY_PRESSED_TIME 10000  /*configure de bounce time*/
//-------------------------------------------------------------
#define ROW0			0
#define ROW0_DIR		DDRC
#define ROW0_OUTPUT		PORTC
//-------------------------------------------------------------
#define ROW1			1
#define ROW1_DIR		DDRC
#define ROW1_OUTPUT		PORTC
//-------------------------------------------------------------
#define ROW2			2
#define ROW2_DIR		DDRC
#define ROW2_OUTPUT		PORTC
//-------------------------------------------------------------
#define ROW3			3
#define ROW3_DIR		DDRC
#define ROW3_OUTPUT		PORTC
//-------------------------------------------------------------
#define LINE0			4
#define LINE0_DIR		DDRC
#define LINE0_PULLRIG	PORTC
#define LINE0_INPUT		PINC
//-------------------------------------------------------------
#define LINE1			5
#define LINE1_DIR		DDRC
#define LINE1_PULLRIG	PORTC
#define LINE1_INPUT		PINC
//-------------------------------------------------------------
#define LINE2			6
#define LINE2_DIR		DDRC
#define LINE2_PULLRIG	PORTC
#define LINE2_INPUT		PINC
//-------------------------------------------------------------
#define LINE3			7
#define LINE3_DIR		DDRC
#define LINE3_PULLRIG	PORTC
#define LINE3_INPUT		PINC
//-------------------------------------------------------------
#endif /* KEYPAD-CONFIG_H_ */