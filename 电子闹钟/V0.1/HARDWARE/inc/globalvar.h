#ifndef __GLOBALVAR_H_
#define __GLOBALVAR_H_

/**********************************
����ͷ�ļ�
**********************************/
#include<reg52.h>

//---�ض���ؼ���---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

typedef unsigned int u16;	  //���������ͽ�����������
typedef unsigned char u8;


//---����ȫ�ֱ���--//
extern uchar TIME[7];	//����ȫ�ֱ���
extern uchar ALARM[7];
extern uchar Tmep_Data[];

extern uchar SetState,SetPlace;
extern uchar Alarm_SetState,Alarm_SetPlace;


extern uchar Monday[] ;  
extern uchar Tuesday[] ; 
extern uchar Wednesday[] ; 
extern uchar Thursday[] ; 
extern uchar Friday[] ; 
extern uchar Saturday[] ; 
extern uchar Sunday[] ; 
extern uchar LCD_Alarm[];
extern uchar LCD_Temp[];


extern char key;
//1Ϊ������ʾģʽ��2Ϊ�¶�ʪ����ʾģʽ��3Ϊ������ʾģʽ
extern char LCD_MODE;
extern char Alarm_Open;



sbit LED = P2^0;
sbit BEEP=P2^1;	

#define TIME_MODE		1
#define TEMP_MODE		2
#define ALARM_MODE		3
//#define KEY4_PRESS		4
//#define KEY5_PRESS		5
//#define KEY6_PRESS		6
//#define KEY7_PRESS		7
//#define KEY8_PRESS		8
//#define KEY9_PRESS		9
//#define KEY_UNPRESS		0



void Global_Init(void);

#endif


