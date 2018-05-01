/*
 * calculator.c
 *
 * Created: 29/04/2018 11:34:44
 *  Author: BADROUS
 */ 
//-------------------------------------------------------------------------
#include "project.h"
#include "lcd.h"
#include "keypad.h"
#include "processing.h"
//------------------------------------------------------------
static void vMainInitCalculator(void);
static void vMainInputCalculator(void);
static void vMainProcessCalculator(void);
static void vMainOutputCalculator(void);
static void vMainErrorCalculator(void);
//---------------------------------------------------------------
static u8 g_result_format=RESULT_FLOAT_FORMAT;   //carry the format of output for future config use
static u8 g_error_flag=CALCULATOR_NO_INPUT_ERROR; //global error flag
static volatile CALCULATOR_STATE g_e_calculator_state=INIT_STATE;  //global enum states
static char g_dump_input_array[MAX_INPUT_CHAR];       //the user input array as expression
static const char g_error_string[MAX_ERROR][MAX_ERROR_STRING]={{"NO ERROR"},
														  {"MATH ERROR"},
														  {"F FORMAT ERROR"},
														  {"NO OPERATION"}};
//-------------------------------------------------------------
int main(void)
{
    while(1)
    {
		switch(g_e_calculator_state)
		{
			case INIT_STATE :
				vMainInitCalculator();		
						break;
			case INPUT_STATE :
				vMainInputCalculator();
						break;
			case PROCESS_STATE :
				vMainProcessCalculator();	
						break;
			case OUTPUT_STATE :
				vMainOutputCalculator();
						break;
			case ERROR_STATE :
				vMainErrorCalculator();
						break;
			default:break;												
		}
    }
}
//--------------------------------------------------------------
static void vMainInitCalculator( void )
{
	vLcdInit();  
	vKeypadInit();
	g_e_calculator_state=INPUT_STATE;
}
//------------------------------------------------------------
static void vMainInputCalculator(void)
{
	//input 16 char 
	u8 input_count=0;
	u8 input_char=0;
	u8 index=0;
	u8 operator_count=0;
	//claen up
	g_error_flag=CALCULATOR_NO_INPUT_ERROR;  //reset flag
	
	for(index=0;index<MAX_INPUT_CHAR;index++)
	{
		g_dump_input_array[index]=0;
	}
	index=0;
	//end clean up
	while(1)
	{
		input_char=ucKeypadScan();  //read input
		if(input_char == NO_VALID_INPUT)
		{
			continue;   //skip
		}
		else if(input_char == 'C')    //reset
		{
			vLcdClearDisplay();  //clear display
			//clear array
			for(index=0;index<=input_count;index++)
			{
				g_dump_input_array[index]=0;
			}
			input_count=0;
			g_error_flag=CALCULATOR_NO_INPUT_ERROR;
			continue;				
		}
		else if(input_char== '=')  // if equel
		{
			
			//check if no operation 
			if(operator_count ==0)
			{
				g_error_flag=CALCULATOR_ERROR_NO_OPERATION;
				g_e_calculator_state=OUTPUT_STATE;
				break;
			}
			//save the = sign
			g_dump_input_array[input_count]=input_char;  //save = as last char number index 16 or less
			//check last char is not operator
			if((g_dump_input_array[input_count-1] == '+') || (g_dump_input_array[input_count-1] == '-') || (g_dump_input_array[input_count-1] == '*') || (g_dump_input_array[input_count-1] == '/'))
			{
				g_error_flag=CALCULATOR_MATH_ERROR;
			}
			if(g_error_flag ==CALCULATOR_NO_INPUT_ERROR)
			{
				g_e_calculator_state=PROCESS_STATE;
				break;	
			}
			else
			{
				g_e_calculator_state=ERROR_STATE;
				break;
			}
			
		}
		else   //if any valid char 
		{
			
			if(input_count<MAX_INPUT_CHAR-1)
			{
				//count number of operator
				if((input_char == '+') || (input_char == '-') || (input_char == '*') || (input_char == '/'))
				{
				//check if * or / sign placed first
					if (input_count==0 && ((input_char == '*') || (input_char == '/')))
					{
						g_error_flag=CALCULATOR_MATH_ERROR;
					}
					//check if 2 operation signs 
					if((g_dump_input_array[input_count-1] == '+') || (g_dump_input_array[input_count-1]== '-') || (g_dump_input_array[input_count-1]== '*') || (g_dump_input_array[input_count-1]== '/'))
					{
						g_error_flag=CALCULATOR_MATH_ERROR;
					}
					operator_count++;
				}
			
				g_dump_input_array[input_count]=input_char;   //save char
				u8LcdPrint(input_char,LCD_FIRST_LINE,input_count); //print char
				input_count++;
				if(input_count==MAX_INPUT_CHAR-1)  //to save = sign
				{
					continue;  //to wait for '=' or 'C'
				}
			}				
		}
	}
}
//-------------------------------------------------------------
static void vMainProcessCalculator(void)
{
	u8 result=0;
	if(g_error_flag==CALCULATOR_ERROR_NO_OPERATION)
	{
		g_e_calculator_state=OUTPUT_STATE;
		return;  //break 
	}
	else
	{
		//calculate the expresion
		result=u8ProcessingCalculate(g_dump_input_array);
		if(result==0)
		{
			g_e_calculator_state=OUTPUT_STATE;
		}
		else
		{
			g_e_calculator_state=ERROR_STATE;
		}
	}	
}
//-------------------------------------------------------------
static void vMainOutputCalculator( void )
{
	u8 processing_error=0;
	u8 input_char=0;
	char output_string[MAX_INPUT_CHAR]={0};
	//check if no operation
	if(g_error_flag==CALCULATOR_ERROR_NO_OPERATION)
	{
		u8LcdGoToXy(LCD_SECOND_LINE,0);
		u8LcdSendString(g_dump_input_array);  //print the input value
		g_error_flag=CALCULATOR_NO_INPUT_ERROR;
		
	}
	else //output if operation 
	{
		processing_error=u8ProcessingFloatToString(output_string,g_result_format);
		if(processing_error==NO_PROCESSING_ERROR)
		{//print answer 
			u8LcdGoToXy(LCD_SECOND_LINE,0);
			u8LcdSendString(output_string);
		}
		else if(processing_error==CALCULATOR_ERROR_EXCEED_FLOAT_FORMAT)
		{
			u8LcdGoToXy(LCD_SECOND_LINE,0);
			u8LcdSendString((char *)g_error_string[CALCULATOR_ERROR_EXCEED_FLOAT_FORMAT]);  //print the input value
			g_error_flag=CALCULATOR_NO_INPUT_ERROR;
		}
		else
		{
			
		}
	}	
	//wait till enter 'C'	
	while(1)
	{
		input_char=ucKeypadScan();  //read input
		if(input_char == 'C') break;
	}
	g_e_calculator_state=INPUT_STATE;
}
//-----------------------------------------------------------------
static void vMainErrorCalculator(void)
{
	char input_char=0;
	u8LcdGoToXy(LCD_SECOND_LINE,0);
	u8LcdSendString((char *)g_error_string[CALCULATOR_MATH_ERROR]);
	while(1)
	{
		input_char=ucKeypadScan();  //read input
		if(input_char == 'C') break;
	}
	g_e_calculator_state=INPUT_STATE;
	g_error_flag=CALCULATOR_NO_INPUT_ERROR;
}
//--------------------------------------------------------
