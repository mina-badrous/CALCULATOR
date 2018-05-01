/*
 * project.h
 *
 * Created: 29/04/2018 12:08:41
 *  Author: BADROUS
 */ 


#ifndef PROJECT_H_
#define PROJECT_H_
//----------------------------------------------------------------
#include "int.h"
#include "bitwise.h"
#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
//----------------------------------------------------------
#define MAX_INPUT_CHAR 17
//---------------------------------------------------------------
typedef enum 
{
	INIT_STATE=0,
	INPUT_STATE,
	PROCESS_STATE,
	OUTPUT_STATE,
	ERROR_STATE
} CALCULATOR_STATE;
//------------------------------------------------------------
#define MAX_ERROR 4
#define MAX_ERROR_STRING 16
#define CALCULATOR_NO_INPUT_ERROR 0
#define CALCULATOR_MATH_ERROR 1
#define CALCULATOR_ERROR_EXCEED_FLOAT_FORMAT 2
#define CALCULATOR_ERROR_NO_OPERATION 3
#define NO_PROCESSING_ERROR 0
#define RESULT_FLOAT_FORMAT 0
#define RESULT_E_FORMAT 1
//---------------------------------------------------------------
#endif /* PROJECT_H_ */