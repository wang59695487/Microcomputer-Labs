#ifndef __DS1302_H_
#define __DS1302_H_

//---包含头文件---//
#include<reg52.h>
#include<intrins.h>
#include"globalvar.h"


//---定义ds1302使用的IO口---//
sbit DSIO=P2^4;   //数据口
sbit RST=P2^3;   //复位口
sbit SCLK=P2^5;  //时钟口

//---定义全局函数---//
void Ds1302Write(uchar addr, uchar dat);
uchar Ds1302Read(uchar addr);
void Ds1302Init();
void Ds1302ReadTime();
void Alarm_Ring();

#endif