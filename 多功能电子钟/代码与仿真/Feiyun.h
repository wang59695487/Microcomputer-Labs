#ifndef _feiyun_h                    //�������룬������Ͳ������±���
#define _feiyun_h
#include<reg52.h>
#include<intrins.h>
#include "Lcd1602.h"
#include "DS18B20.h"
#include "Key.h"
#include "Timer.h"
#include "Time.h"
/////////�궨������
#define uchar unsigned char
#define uint  unsigned int
#define	String uchar*
/////////�궨������
////////�궨�峣��
#define du  0xdf			//�����
#define TH0_value 0x18
#define TL0_value 0x18
#ifndef true 
  #define true 1
#endif
sbit buzz=P3^0;
#define BuzzOpen   buzz=0
#define BuzzClose  buzz=1
void delay(uint z);          ///��ʱ����,��Լ��һ����/z
void TempShow();

#endif 
