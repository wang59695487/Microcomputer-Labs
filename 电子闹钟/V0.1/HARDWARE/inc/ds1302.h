#ifndef __DS1302_H_
#define __DS1302_H_

//---����ͷ�ļ�---//
#include<reg52.h>
#include<intrins.h>
#include"globalvar.h"


//---����ds1302ʹ�õ�IO��---//
sbit DSIO=P2^4;   //���ݿ�
sbit RST=P2^3;   //��λ��
sbit SCLK=P2^5;  //ʱ�ӿ�

//---����ȫ�ֺ���---//
void Ds1302Write(uchar addr, uchar dat);
uchar Ds1302Read(uchar addr);
void Ds1302Init();
void Ds1302ReadTime();
void Alarm_Ring();

#endif