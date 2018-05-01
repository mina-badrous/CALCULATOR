/*
 * processing.h
 *
 * Created: 29/04/2018 22:30:47
 *  Author: BADROUS
 */
//------------------------------------------------------------
#ifndef PROCESSING_H_
#define PROCESSING_H_
//------------------------------------------------------------
#include <stdlib.h>
#include "project.h"
#include "stack.h"
//------------------------------------------------------------
#define PROCESSING_DATA_TYPE STACK_DATA_TYPE
//-------------------------------------------------------------
#define SIGN_MASK 0x00
#define EQUEL_OPERATOR (SIGN_MASK -'=')
#define PLUS_OPERATOR (SIGN_MASK -'+')
#define MINUS_OPERATOR (SIGN_MASK -'-')
#define MULTIPLY_OPERATOR (SIGN_MASK -'*')
#define DIVISOIN_OPERATOR (SIGN_MASK -'/')
//---------------------------------------------------------------
#define MAX_FLOAT_FORMAT 9999999.9f
//--------------------------------------------------------
u8 u8ProcessingCalculate(char * dump_array);
u8 u8ProcessingFloatToString(char * dump_array,u8 result_format);
//--------------------------------------------------------------




//---------------------------------------------------------------------
#endif /* PROCESSING_H_ */
