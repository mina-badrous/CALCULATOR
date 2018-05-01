/*
 * lcd.c
 *
 * Created: 29/04/2018 11:48:01
 *  Author: BADROUS
 */
//------------------------------------------------------------- 
#include "lcd.h"
//----------------------------------------------------------
static void SvLcdSend(u8 type,u8 data);
static void SvLatch_data(void);
//-------------------------------------------------------------
void vLcdInit( void )
{
	//init data as output and E and RS
	set_bit(LCD_E_DDR,LCD_E);
	set_bit(LCD_RS_DDR,LCD_RS);
	
	set_bit(LCD_D4_DDR,LCD_D4);
	set_bit(LCD_D5_DDR,LCD_D5);
	set_bit(LCD_D6_DDR,LCD_D6);
	set_bit(LCD_D7_DDR,LCD_D7);
	//init initial condition
	clear_bit(LCD_E_OUTPUT,LCD_E);
	clear_bit(LCD_RS_OUTPUT,LCD_RS);
	
	clear_bit(LCD_D4_OUTPUT,LCD_D4);
	clear_bit(LCD_D5_OUTPUT,LCD_D5);
	clear_bit(LCD_D6_OUTPUT,LCD_D6);
	clear_bit(LCD_D7_OUTPUT,LCD_D7);
	//delay to reach vcc level
	_delay_ms(20);
	//send init cmds
	SvLcdSend(CMD,LCD_CMD_MODE4_INIT0);
	SvLcdSend(CMD,LCD_CMD_MODE4_INIT1);
	SvLcdSend(CMD,LCD_CMD_MODE4_2LINES);
	SvLcdSend(CMD,LCD_CMD_DISPLAY_ON_CURSOR_OFF);
}
//--------------------------------------------------------------
static void SvLcdSend(u8 type,u8 data)
{
	//make RS =0 as cmd and = 1 as data
	if(type==CMD)
	{
		clear_bit(LCD_RS_OUTPUT,LCD_RS);
	}
	else 
	{
		set_bit(LCD_RS_OUTPUT,LCD_RS);
	}
	
	//high nibble data send
	if(check_bit(data,4))
	{
		set_bit(LCD_D4_OUTPUT,LCD_D4);
	}
	else
	{
		clear_bit(LCD_D4_OUTPUT,LCD_D4);
	} 
	if(check_bit(data,5))
	{
		set_bit(LCD_D5_OUTPUT,LCD_D5);
	}
	else
	{
		clear_bit(LCD_D5_OUTPUT,LCD_D5);
	}
	if(check_bit(data,6))
	{
		set_bit(LCD_D6_OUTPUT,LCD_D6);
	}
	else
	{
		clear_bit(LCD_D6_OUTPUT,LCD_D6);
	}
	if(check_bit(data,7))
	{
		set_bit(LCD_D7_OUTPUT,LCD_D7);
	}
	else
	{
		clear_bit(LCD_D7_OUTPUT,LCD_D7);
	}
	//latch data
	SvLatch_data();
	//delay
	_delay_ms(2);
	//lower nibble data 
		if(check_bit(data,0))
		{
			set_bit(LCD_D4_OUTPUT,LCD_D4);
		}
		else
		{
			clear_bit(LCD_D4_OUTPUT,LCD_D4);
		}
		if(check_bit(data,1))
		{
			set_bit(LCD_D5_OUTPUT,LCD_D5);
		}
		else
		{
			clear_bit(LCD_D5_OUTPUT,LCD_D5);
		}
		if(check_bit(data,2))
		{
			set_bit(LCD_D6_OUTPUT,LCD_D6);
		}
		else
		{
			clear_bit(LCD_D6_OUTPUT,LCD_D6);
		}
		if(check_bit(data,3))
		{
			set_bit(LCD_D7_OUTPUT,LCD_D7);
		}
		else
		{
			clear_bit(LCD_D7_OUTPUT,LCD_D7);
		}
	//latch data
	SvLatch_data();
}
//----------------------------------------------------------
static void SvLatch_data( void )
{
	//make E HIGH
	set_bit(LCD_E_OUTPUT,LCD_E);
	//delay
	_delay_us(20);
	//make E LOw 
	clear_bit(LCD_E_OUTPUT,LCD_E);
	_delay_us(20);
}
//--------------------------------------------------------------------
void vLcdSendChar( char data )
{
	SvLcdSend(DATA,data);
}
//-------------------------------------------------------------
void vLcdSendCmd( char data )
{
	SvLcdSend(CMD,data);
}
//-----------------------------------------------------------
void vLcdClearDisplay( void )
{
	SvLcdSend(CMD,LCD_CMD_CLEAR_DISPLAY);
	_delay_ms(100);
}
//-------------------------------------------------------
u8 u8LcdGoToXy( u8 line,u8 column )
{
	//limit check
	switch(line)
	{
		case LCD_FIRST_LINE :
					if(column >=0 && column <=15)
					{
						SvLcdSend(CMD,FIRST_LINE_ADDRESS + column);
					}
					else
					{
						return LCD_ERROR_COLUMN_OUT_OF_RANGE ;
					}
					break;
		case LCD_SECOND_LINE :
					if(column >=0 && column <=15)
					{
						SvLcdSend(CMD,SECOND_LINE_ADDRESS + column);
					}
					else
					{
						return LCD_ERROR_COLUMN_OUT_OF_RANGE ;
					}
					break;
		default:return LCD_ERROR_ROW_OUT_OF_RANGE ;
			}
			return LCD_NO_ERROR ;
}
//---------------------------------------------------------
u8 u8LcdSendString(char* str_ptr)
{
	//check if no char send 
	if(str_ptr ==NULL)
	{
		return LCD_NO_CHAR_TO_PRINT ;
	}
	else
	{   //print till null char
		while(*str_ptr !='\0')
		{
			SvLcdSend(DATA,*str_ptr);
			str_ptr++;
		}
		return LCD_NO_ERROR ;
	}
	
}
//----------------------------------------------------
u8 u8LcdPrint(u8 data,u8 line,u8 position)
{
	u8 l=0;
	if(line>1 || line<0)
	{
		return LCD_ERROR_ROW_OUT_OF_RANGE;   //error
	}
	if(position>15 || position<0)
	{
		position=position % 16;  //error
	}
	switch (line)
	{
		case 0:
		l=0x80 +position;
		break;
		default:
		l=0xc0+position;
		break;
		
	}
	SvLcdSend(CMD,l);    //position    11
	SvLcdSend(DATA,data);  //data
	return LCD_NO_ERROR;
}
//-----------------------------------------------------
u8 lcd_print_string(u8* str,u8 line,u8 position)
{
	u8 length =(u8)strlen((char*)str);
	if(length > 16-position)
	{
		return LCD_ERROR_COLUMN_OUT_OF_RANGE;    // error
	}
	else
	{
		while(*str !='\0')
		{
			u8LcdPrint(*str,line,position);
			position++;
			str++;
		}
		return LCD_NO_ERROR;
	}
}
//-----------------------------------------------------------