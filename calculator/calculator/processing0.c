/*
 * processing.c
 *
 * Created: 29/04/2018 22:31:08
 *  Author: BADROUS
 */ 
#include "processing.h"
//----------------------------------------------------------
static void	SvAsciiToInt(char * array);
static void	SvInfixToPostfix(void);
static s32	S32EvaluatePostfix(void);
s32 s32operation(s32 op1,s32 op2,s32 temp);
//-------------------------------------------------------------
ARR_STACK g_ascii_to_int_temp_stck={255,0,{0}};
ARR_STACK g_ascii_to_int_stck={255,0,{0}};
s32 g_post_fix_array[MAX_INPUT_CHAR];
u8 g_post_fix_index;	
s32 final_answer=0;
//--------------------------------------------------------------
u8 u8ProcessingCalculate(char * dump_array)
{
	//ascii char to int
	SvAsciiToInt(dump_array);
	//infix to postfix
	SvInfixToPostfix();  //error change operators to well defined data
	//evaluate postfix
	final_answer=S32EvaluatePostfix();
	//set output or error
}
//---------------------------------------------------------------
static void	SvAsciiToInt(char * array)
{
	u8 temp=0,index;
	u32 ten_power=1;
	u32 accumelator=0;
	for(index=0;index<MAX_INPUT_CHAR;index++)  //traverse the array
	{
		temp=array[index];
		if(temp==0)
		{
			break;
		}
		else if(temp=='=') //if last char
		{
			while(!(u8StackIsEmpty(&g_ascii_to_int_temp_stck)))  //while stack not empty
			{
							
				accumelator +=((u8StackPop(&g_ascii_to_int_temp_stck))-'0')*ten_power;
				ten_power *=10;
			}
			vStackPush(&g_ascii_to_int_stck,accumelator);//last input
			vStackPush(&g_ascii_to_int_stck,SIGN_MASK - temp);  //push = sign
			break;
		}
		else if((temp== '+') || (temp== '-') || (temp== '*') || (temp== '/'))
		{
			while(!(u8StackIsEmpty(&g_ascii_to_int_temp_stck)))  //while stack not empty
			{
				
				accumelator +=((u8StackPop(&g_ascii_to_int_temp_stck))-'0')*ten_power;
				ten_power *=10;
			}
			vStackPush(&g_ascii_to_int_stck,accumelator);
			vStackPush(&g_ascii_to_int_stck,SIGN_MASK - temp);   //push sign
			accumelator=0;  //reset acc and ten power
			ten_power=1;
		}
		else
		{
			vStackPush(&g_ascii_to_int_temp_stck,temp);
		}
	}
}
//---------------------------------------------------------------
static void	SvInfixToPostfix(void)
{
	s32 index,temp,op;
	ARR_STACK operators_stack={255,0,{0}} ;
	//loop the array if = pop last operator and save it in the array
	for(index=0;index<MAX_INPUT_CHAR;index++)
	{
		temp=g_ascii_to_int_stck.arr[index];
		if(temp== EQUEL_OPERATOR)
		{
			//pop last element
			while(!(u8StackIsEmpty(&operators_stack)))
			{
				g_post_fix_array[g_post_fix_index]=u8StackPop(&operators_stack);  //save it in post fix
				g_post_fix_index++;
			}
			g_post_fix_array[g_post_fix_index]=temp;  //save = it in post fix
			g_post_fix_index=0; //reset index 
			break;
		}
		//if + - check the top of stack if * / pop them first then add + - to stck
		//else push them to stack
		else if((temp == PLUS_OPERATOR) || (temp == MINUS_OPERATOR) )
		{
			if(!(u8StackIsEmpty(&operators_stack)))
			{
				op=u8StackTop(&operators_stack);
				if( op== MULTIPLY_OPERATOR || op == DIVISOIN_OPERATOR)       //if high precedence
				{
					while(!(u8StackIsEmpty(&operators_stack)))
					{
						g_post_fix_array[g_post_fix_index]=u8StackPop(&operators_stack);  //save it in post fix
						g_post_fix_index++;
					}
					vStackPush(&operators_stack,temp);
				}
				else
				{					
					vStackPush(&operators_stack,temp);
				}
			}
			else  //if stack is empty
			{
				vStackPush(&operators_stack,temp);
			}
			
		}
		// if * / check top of stack if * / pop them first then add * / to stack
		// else if - + push to stack
		else if((temp == MULTIPLY_OPERATOR) || (temp == DIVISOIN_OPERATOR))
		{
			if(!(u8StackIsEmpty(&operators_stack)))
			{
				op=u8StackTop(&operators_stack);
				if( op== MULTIPLY_OPERATOR || op == DIVISOIN_OPERATOR)       //if high precedence
				{
					while(!(u8StackIsEmpty(&operators_stack)))
					{
						g_post_fix_array[g_post_fix_index]=u8StackPop(&operators_stack);  //save it in post fix
						g_post_fix_index++;
					}
					vStackPush(&operators_stack,temp);
				}
				else
				{
					vStackPush(&operators_stack,temp);
				}
			}
			//if stack is empty push to stack
			else
			{
				vStackPush(&operators_stack,temp);
			}
			
		}
		//if number save it in array 
		else  //if it is an operand
		{
			g_post_fix_array[g_post_fix_index]=temp;  //save it in post fix
			g_post_fix_index++;
		}
	}
}
//-------------------------------------------------------------------
static s32	S32EvaluatePostfix(void)
{
	//loop the array if operand push to stack
	//else if operator pop op2 and op1 accumelate
	s32 index,temp,op1,op2;
	s32 accumelator=0;
	ARR_STACK operand_stack={255,0,{0}} ;
	for(index=0;index<MAX_INPUT_CHAR;index++)
	{
		temp=g_post_fix_array[index];
		//exit condition
		if(temp == EQUEL_OPERATOR)
		{
			break;
		}
		else if((temp == PLUS_OPERATOR) || (temp == MINUS_OPERATOR) || (temp == MULTIPLY_OPERATOR) || (temp == DIVISOIN_OPERATOR))
		{
			op2=u8StackPop(&operand_stack);
			op1=u8StackPop(&operand_stack);
			accumelator= s32operation(op1,op2,temp);
			vStackPush(&operand_stack,accumelator);//push it to stack
		}
		else
		{
			vStackPush(&operand_stack,temp);
		}
	}
	return u8StackTop(&operand_stack);	
}
//----------------------------------------------------------------
s32 s32operation(s32 op1,s32 op2,s32 temp)
{
	switch(temp)
	{
		case PLUS_OPERATOR :return op1 + op2 ;
		case MINUS_OPERATOR :return op1 - op2 ;
		case MULTIPLY_OPERATOR :return op1 * op2 ;
		case DIVISOIN_OPERATOR :return op1 / op2 ;
		default:break;		
	}
	return 0;
}

