/*
 * processing.h
 *
 * Created: 29/04/2018 22:30:47
 *  Author: BADROUS
 */ 


#ifndef PROCESSING_H_
#define PROCESSING_H_
//------------------------------------------------------------
#include "project.h"
#include "stack.h"
//------------------------------------------------------------
#define SIGN_MASK 0xFFFFFFFF
#define EQUEL_OPERATOR (SIGN_MASK -'=')
#define PLUS_OPERATOR (SIGN_MASK -'+')
#define MINUS_OPERATOR (SIGN_MASK -'-')
#define MULTIPLY_OPERATOR (SIGN_MASK -'*')
#define DIVISOIN_OPERATOR (SIGN_MASK -'/')
u8 u8ProcessingCalculate(char * dump_array);


//---------------------------------------------------------------------
#endif /* PROCESSING_H_ */