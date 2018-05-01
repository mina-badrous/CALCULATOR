#ifndef __STACK_H_
#define __STACK_H_
//------------------------------------------------------
#include "int.h"
#define STACK_SIZE 17
#define STACK_DATA_TYPE s32
//-----------------------------------------------------------
typedef struct
{
    u8 top;
    u8 items;
    STACK_DATA_TYPE arr[STACK_SIZE];
} ARR_STACK;
//---------------------------------------------------------------
void vStackPush(ARR_STACK* stk,STACK_DATA_TYPE data);
STACK_DATA_TYPE u8StackPop(ARR_STACK* stk);
STACK_DATA_TYPE u8StackTop(ARR_STACK* stk);
u8 u8StackIsEmpty(ARR_STACK* stk);
u8 u8StackIsFull(ARR_STACK* stk);
//--------------------------------------------------------------
#endif // __STACK_ARRAY_H_
