/*
 * processing.c
 *
 * Created: 29/04/2018 22:31:08
 *  Author: BADROUS
 */
//----------------------------------------------------------
#include "stack.h"
//---------------------------------------------------------
u8 u8StackIsEmpty(ARR_STACK* stk)
{
    if(stk->items==0)
        return 1;
    else
        return 0;
}
//------------------------------------------------------
u8 u8StackIsFull(ARR_STACK* stk)
{
	if(stk->items==STACK_SIZE)
	return 1;
	else
	return 0;
}
//--------------------------------------------------------
void vStackPush(ARR_STACK* stk,STACK_DATA_TYPE data)
{
    stk->top +=1;
    if(stk->top==STACK_SIZE)
    {
        stk->top -=1;
        return;
    }
    stk->arr[stk->top]=data;
    stk->items +=1;
}
//------------------------------------------------------------
STACK_DATA_TYPE SDTStackPop(ARR_STACK* stk)
{
    if(stk->items)
    {
            STACK_DATA_TYPE temp=stk->arr[stk->top];
            stk->top -=1;
            stk->items -=1;
              if(stk->top==255)
            {
                stk->items=0;
            }
            return temp;
    }
    else
    {
        return 0;   /*garbage value*/
    }

}
//--------------------------------------------------------------------
STACK_DATA_TYPE SDTStackTop(ARR_STACK* stk)
{
    return stk->arr[stk->top];
}
//------------------------------------------------------------------




