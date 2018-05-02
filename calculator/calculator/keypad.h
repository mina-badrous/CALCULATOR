/*
 * keypad.h
 *
 * Created: 4/28/2018 1:11:21 PM
 */ 
//---------------------------------------------------------
#ifndef KEYPAD_H_
#define KEYPAD_H_
//----------------------------------------------------------
#include "int.h"
#include "keypad-config.h"
//--------------------------------------------------------
#define NO_VALID_INPUT		0xFF
//------------------------------------------------------
#define LINE0_CHECK			(LINE0_INPUT & (1U<<LINE0))
#define LINE1_CHECK			(LINE1_INPUT & (1U<<LINE1))
#define LINE2_CHECK			(LINE2_INPUT & (1U<<LINE2))
#define LINE3_CHECK			(LINE3_INPUT & (1U<<LINE3))
#define IS_VALID			0
#define IS_STILL_VALID		0
#define ALL_INPUTS_CHECK	(LINE0_CHECK \
							&& LINE1_CHECK \
							&& LINE2_CHECK \
							&& LINE3_CHECK)
//-------------------------------------------------------
void vKeypadInit(void);
unsigned char ucKeypadScan(void);
#ifdef NO_KEYPAD_WAIT
unsigned char ucKeypadScanDebounce(void);
#endif
//---------------------------------------------------
#endif /* KEYPAD_H_ */