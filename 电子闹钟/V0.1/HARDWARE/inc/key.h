#ifndef __KEY_H_
#define __KEY_H_

/**********************************
包含头文件
**********************************/
#include<reg52.h>
#include"globalvar.h"

#define GPIO_KEY P3
/**********************************
    key PIN口定义
**********************************/
sbit KEY_L1=P3^2;
sbit KEY_L2=P3^3;
sbit KEY_L3=P3^4;

sbit KEY_H1=P3^5;
sbit KEY_H2=P3^6;
sbit KEY_H3=P3^7;

#define KEY_L1_SetL			(KEY_L1=0)
#define KEY_L2_SetL			(KEY_L2=0)
#define KEY_L3_SetL			(KEY_L3=0)

#define KEY_L1_SetH			(KEY_L1=1)
#define KEY_L2_SetH			(KEY_L2=1)
#define KEY_L3_SetH			(KEY_L3=1)


#define KEY1_PRESS		1
#define KEY2_PRESS		2
#define KEY3_PRESS		3
#define KEY4_PRESS		4
#define KEY5_PRESS		5
#define KEY6_PRESS		6
#define KEY7_PRESS		7
#define KEY8_PRESS		8
#define KEY9_PRESS		9
#define KEY_UNPRESS		0


char KEY_Scan(char mode);
void KEY_Press(void);


#endif


