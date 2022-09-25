#ifndef _feiyun_h                    //条件编译，编译过就不再向下编译
#define _feiyun_h
#include<reg52.h>
#include<intrins.h>
#include "Lcd1602.h"
#include "DS18B20.h"
#include "Key.h"
#include "Timer.h"
#include "Time.h"
/////////宏定义类型
#define uchar unsigned char
#define uint  unsigned int
#define	String uchar*
/////////宏定义命令
////////宏定义常量
#define du  0xdf			//定义°
#define TH0_value 0x18
#define TL0_value 0x18
#ifndef true 
  #define true 1
#endif
sbit buzz=P3^0;
#define BuzzOpen   buzz=0
#define BuzzClose  buzz=1
void delay(uint z);          ///延时函数,大约是一毫秒/z
void TempShow();

#endif 
