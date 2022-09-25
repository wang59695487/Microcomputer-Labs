#ifndef __GLOBALVAR_H_
#define __GLOBALVAR_H_

/**********************************
包含头文件
**********************************/
#include<reg52.h>

//---重定义关键词---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

typedef unsigned int u16;	  //对数据类型进行声明定义
typedef unsigned char u8;


//---加入全局变量--//
extern uchar TIME[7];	//加入全局变量
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
//1为正常显示模式，2为温度湿度显示模式，3为闹钟显示模式
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


