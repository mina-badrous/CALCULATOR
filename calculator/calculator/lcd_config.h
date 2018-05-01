/*
 * lcd_config.h
 *
 * Created: 29/04/2018 11:47:51
 *  Author: BADROUS
 */ 
//-------------------------------------------------------------------
#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_
//-------------------------------------------------------------------
#define LCD_MODE 4
//------------------------------------------------------
#define LCD_D4 4
#define LCD_D4_DDR DDRA
#define LCD_D4_OUTPUT PORTA
//----------------------------------------------------
#define LCD_D5 5
#define LCD_D5_DDR DDRA
#define LCD_D5_OUTPUT PORTA
//----------------------------------------------------
#define LCD_D6 6
#define LCD_D6_DDR DDRA
#define LCD_D6_OUTPUT PORTA
//--------------------------------------------------
#define LCD_D7 7
#define LCD_D7_DDR DDRA
#define LCD_D7_OUTPUT PORTA
//-----------------------------------------------
#define LCD_RS 1
#define LCD_RS_DDR DDRA
#define LCD_RS_OUTPUT PORTA
//---------------------------------------------------
#define LCD_E 0
#define LCD_E_DDR DDRA
#define LCD_E_OUTPUT PORTA
//-------------------------------------------------------
#endif /* LCD_CONFIG_H_ */