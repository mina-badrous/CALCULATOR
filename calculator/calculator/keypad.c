/*
 * keypad.c
 *
 * Created: 4/28/2018 1:11:10 PM
 *  Author: Ramy Elfouly
 */ 
 #include "keypad.h"
//---------------------------------------------------------------------
  const static unsigned char s_keypad_mapping[4][4]= {{'7','8','9','/'},
													  {'4','5','6','*'},
											          {'1','2','3','-'},
									                  {'C','0','=','+'}};
//-----------------------------------------------------------------------
 void vKeypadInit(void)
 {
 //set rows as output
 ROW0_DIR |=(1U<<ROW0);
 ROW1_DIR |=(1U<<ROW1);
 ROW2_DIR |=(1U<<ROW2);
 ROW3_DIR |=(1U<<ROW3);
  //set lines as input
  LINE0_DIR &=~(1U<<LINE0);
  LINE1_DIR &=~(1U<<LINE1);
  LINE2_DIR &=~(1U<<LINE2);
  LINE3_DIR &=~(1U<<LINE3);
 //set rows output to no output state(1)
 ROW0_OUTPUT |=(1U<<ROW0);
 ROW1_OUTPUT |=(1U<<ROW1);
 ROW2_OUTPUT |=(1U<<ROW2);
 ROW3_OUTPUT |=(1U<<ROW3);
 //pull the line up
 LINE0_PULLRIG |=(1U<<LINE0);
 LINE1_PULLRIG |=(1U<<LINE1);
 LINE2_PULLRIG |=(1U<<LINE2);
 LINE3_PULLRIG |=(1U<<LINE3);

 }
//--------------------------------------------------------------------
 unsigned char ucKeypadScan(void)
 {
	//pseudo code
	uint8_t row=0;
	uint8_t line = NO_VALID_INPUT;
	unsigned char result = NO_VALID_INPUT;
	
	//loop on rows
	for (row=0;row<4;row++)
	{
		//set rows output to no output state(1)
		ROW0_OUTPUT |=(1U<<ROW0);
		ROW1_OUTPUT |=(1U<<ROW1);
		ROW2_OUTPUT |=(1U<<ROW2);
		ROW3_OUTPUT |=(1U<<ROW3);
		
		//set certain row to output state (0)
		switch(row)
		{
		case 0:ROW0_OUTPUT &=~(1U<<ROW0);break;
		case 1:ROW1_OUTPUT &=~(1U<<ROW1);break;
		case 2:ROW2_OUTPUT &=~(1U<<ROW2);break;
		case 3:ROW3_OUTPUT &=~(1U<<ROW3);break;
		default:break;
		}
		//check on lines
		if (LINE0_CHECK==IS_VALID){line=0;}
		else if (LINE1_CHECK==IS_VALID){line=1;}
		else if (LINE2_CHECK==IS_VALID){line=2;}
		else if (LINE3_CHECK==IS_VALID){line=3;}
		else {/* MISRA */}
		//check for input validity
		if (line != NO_VALID_INPUT) 
		{
			//wait till the input is gone
			while(ALL_INPUTS_CHECK == IS_STILL_VALID);
			//save the mapped key[row][line]
			result = s_keypad_mapping[row][line];
			//break from the loop
			break;
		}
		
	}
	//return the mapped key	 
	return result;
 }
 //-----------------------------------------------------------------