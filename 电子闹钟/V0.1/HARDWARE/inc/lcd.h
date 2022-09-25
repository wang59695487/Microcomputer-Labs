#ifndef __LCD_H_
#define __LCD_H_
/**********************************
当使用的是4位数据传输的时候定义，
使用8位取消这个定义
**********************************/
//#define LCD1602_4PINS

/**********************************
包含头文件
**********************************/
#include<reg52.h>
#include"globalvar.h"





/**********************************
    LCD  PIN口定义
**********************************/
#define LCD1602_DATAPINS P0
sbit LCD1602_E=P1^2;
sbit LCD1602_RW=P1^1;
sbit LCD1602_RS=P1^0;



/**********************************
函数声明
**********************************/
/*LCD1602写入8位命令子函数*/
void LcdWriteCom(uchar com);
/*LCD1602写入8位数据子函数*/	
void LcdWriteData(uchar dat)	;
/*LCD1602初始化子程序*/		
void LcdInit();						  
void Lcd_TimeDisplay();
void Lcd_AlarmDisplay(void);
void Lcd_TempDisplay(int temp);
void LcdDisplay(void) ;
#endif
