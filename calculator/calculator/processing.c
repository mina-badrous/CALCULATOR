/*
 * processing.c
 *
 * Created: 29/04/2018 22:31:08
 *  Author: BADROUS
 */
//-------------------------------------------------------------------
#include "processing.h"
//----------------------------------------------------------
static void	vAsciiToInt(char * array);
static void vclean_up(void);
static void	vInfixToPostfix(void);
static PROCESSING_DATA_TYPE	PDTEvaluatePostfix(void);
static PROCESSING_DATA_TYPE PDTOperation(PROCESSING_DATA_TYPE op1,PROCESSING_DATA_TYPE op2,PROCESSING_DATA_TYPE temp);
//-------------------------------------------------------------
ARR_STACK g_ascii_to_int_temp_stck={255,0,{0}};
ARR_STACK g_ascii_to_int_stck={255,0,{0}};
PROCESSING_DATA_TYPE g_post_fix_array[MAX_INPUT_CHAR];
u8 g_post_fix_index;
PROCESSING_DATA_TYPE final_answer=0;
//--------------------------------------------------------------
u8 u8ProcessingCalculate(char * dump_array)
{
	//ascii char to int
	vAsciiToInt(dump_array);
	//infix to postfix
	vInfixToPostfix();  //error change operators to well defined data
	//evaluate postfix
	final_answer=PDTEvaluatePostfix();
	return 0; //no error
	//set output or error
}
//---------------------------------------------------------------
static void	vAsciiToInt(char * array)
{
	u8 temp=0,index;
	volatile float ten_power=1;
	volatile float accumelator=0;
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

				accumelator +=((SDTStackPop(&g_ascii_to_int_temp_stck))-'0')*ten_power;
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

				accumelator +=((SDTStackPop(&g_ascii_to_int_temp_stck))-'0')*ten_power;
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
static void	vInfixToPostfix(void)
{
	volatile PROCESSING_DATA_TYPE temp,op=0;
	u8 index;//edit
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
				g_post_fix_array[g_post_fix_index]=SDTStackPop(&operators_stack);  //save it in post fix
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
				op=SDTStackTop(&operators_stack);
				if( op== MULTIPLY_OPERATOR || op == DIVISOIN_OPERATOR)       //if high precedence
				{
				    while((!(u8StackIsEmpty(&operators_stack))))
					//while((!(u8StackIsEmpty(&operators_stack))) && ((SDTStackTop(&operators_stack) ==MULTIPLY_OPERATOR) || (SDTStackTop(&operators_stack) ==DIVISOIN_OPERATOR) ))
					{
						g_post_fix_array[g_post_fix_index]=SDTStackPop(&operators_stack);  //save it in post fix
						g_post_fix_index++;
					}
					vStackPush(&operators_stack,temp);
				}
				else
				{
				    while((!(u8StackIsEmpty(&operators_stack))))
					//while((!(u8StackIsEmpty(&operators_stack))) && ((SDTStackTop(&operators_stack) == PLUS_OPERATOR) || (SDTStackTop(&operators_stack) ==MINUS_OPERATOR) ))
					{
						g_post_fix_array[g_post_fix_index]=SDTStackPop(&operators_stack);  //save it in post fix
						g_post_fix_index++;
					}
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

				if( op== MULTIPLY_OPERATOR || op == DIVISOIN_OPERATOR)       //if high precedence
				{
				    //vStackPush(&operators_stack,temp);
					while((!(u8StackIsEmpty(&operators_stack))) && ((SDTStackTop(&operators_stack) ==MULTIPLY_OPERATOR) || (SDTStackTop(&operators_stack) ==DIVISOIN_OPERATOR) ))
                     //while((!(u8StackIsEmpty(&operators_stack))))
					{
						g_post_fix_array[g_post_fix_index]=SDTStackPop(&operators_stack);  //save it in post fix
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
static PROCESSING_DATA_TYPE	PDTEvaluatePostfix(void)
{
	//loop the array if operand push to stack
	//else if operator pop op2 and op1 accumelate
	PROCESSING_DATA_TYPE temp,op1,op2;
	PROCESSING_DATA_TYPE accumelator=0;
	s32 index;
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
			op2=SDTStackPop(&operand_stack);
			op1=SDTStackPop(&operand_stack);
			accumelator= PDTOperation(op1,op2,temp);
			vStackPush(&operand_stack,accumelator);//push it to stack
		}
		else
		{
			vStackPush(&operand_stack,temp);
		}
	}
	return SDTStackTop(&operand_stack);
}
//----------------------------------------------------------------
PROCESSING_DATA_TYPE PDTOperation(PROCESSING_DATA_TYPE op1,PROCESSING_DATA_TYPE op2,PROCESSING_DATA_TYPE temp)
{
	switch((s64)temp)
	{
		case PLUS_OPERATOR :return op1 + op2 ;
		case MINUS_OPERATOR :return op1 - op2 ;
		case MULTIPLY_OPERATOR :return op1 * op2 ;
		case DIVISOIN_OPERATOR :return op1 / op2 ;
		default:break;
	}
	return 0;
}
//---------------------------------------------------------------
u8 u8ProcessingFloatToString(char * dump_array,u8 result_format)
{
	//float to string
	//check format to make configuration state
	//if float format exceed change to E format 
	if(result_format==RESULT_FLOAT_FORMAT)
	{
		if(final_answer > MAX_FLOAT_FORMAT || final_answer < (MAX_FLOAT_FORMAT*(-1)) )
		{
			//convert flaot to string with E notation
			dtostre(final_answer,dump_array,5,DTOSTR_ALWAYS_SIGN | DTOSTR_UPPERCASE);
			//for future use to make it configureable
			/*
			vclean_up();
			return CALCULATOR_ERROR_EXCEED_FLOAT_FORMAT; // 
			*/
		}
		else
		{
			//convert flaot to string
			dtostrf((double)final_answer,1,3,dump_array);
		}
			
	}
	else if(result_format==RESULT_E_FORMAT)
	{
		//convert flaot to string with E notation
		dtostre(final_answer,dump_array,5,DTOSTR_ALWAYS_SIGN | DTOSTR_UPPERCASE);
	}
	else
	{
		//misra rules
	}
	
	vclean_up();
	return NO_PROCESSING_ERROR;

}
//--------------------------------------------------------------------
void vclean_up(void)
{
	//clean up all global variables 
	u8 index;
	for(index=0;index<MAX_INPUT_CHAR;index++)
	{
		g_ascii_to_int_temp_stck.arr[index]=0;
		g_ascii_to_int_stck.arr[index]=0;
		g_post_fix_array[index]=0;
	}	
	g_ascii_to_int_temp_stck.items=0;
	g_ascii_to_int_stck.items=0;
	g_ascii_to_int_temp_stck.top=0;
	g_ascii_to_int_stck.top=0;
	g_post_fix_index=0;
	final_answer=0;
}
//------------------------------------------------------------------