#ifndef _lcd1602_h                    //条件编译，编译过就不再向下编译
#define _lcd1602_h
#include<reg52.h>
#define uchar unsigned char	
#define uint  unsigned int
#define	String uchar*
/////////宏定义命令
#define	cls	write_com(0x01)	//清屏
#define dr  write_com(0x16) //光标右移一位
#define dl  write_com(0x10)	//光标左移一位 
#define ir	write_com(0x18)	//显示右移一位
#define il  write_com(0x1c) //显示左移一位
#define pd(x)  write_com(0x80+x) //指定数据RAM的地址

/////////宏定义接口
sbit lcden=P2^7;
sbit lcdrw=P2^5;
sbit lcdrs=P2^6;


void write_com(uchar com);
void write_data(uchar date);
void LcdChar(uchar p,uchar dat);
void LcdStr(uchar p,String str);
void LcdData(uchar p,uchar dat);
void LcdInit(void);
#endif