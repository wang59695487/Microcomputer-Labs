#ifndef __LCD_H_
#define __LCD_H_
/**********************************
��ʹ�õ���4λ���ݴ����ʱ���壬
ʹ��8λȡ���������
**********************************/
//#define LCD1602_4PINS

/**********************************
����ͷ�ļ�
**********************************/
#include<reg52.h>
#include"globalvar.h"





/**********************************
    LCD  PIN�ڶ���
**********************************/
#define LCD1602_DATAPINS P0
sbit LCD1602_E=P1^2;
sbit LCD1602_RW=P1^1;
sbit LCD1602_RS=P1^0;



/**********************************
��������
**********************************/
/*LCD1602д��8λ�����Ӻ���*/
void LcdWriteCom(uchar com);
/*LCD1602д��8λ�����Ӻ���*/	
void LcdWriteData(uchar dat)	;
/*LCD1602��ʼ���ӳ���*/		
void LcdInit();						  
void Lcd_TimeDisplay();
void Lcd_AlarmDisplay(void);
void Lcd_TempDisplay(int temp);
void LcdDisplay(void) ;
#endif
