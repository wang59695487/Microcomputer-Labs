#ifndef __TEMP_H_
#define __TEMP_H_

#include<reg52.h>
#include"globalvar.h"

//--定义使用的IO口--//
sbit DSPORT=P1^3;

//--声明全局函数--//
uchar Ds18b20Init();
void Ds18b20WriteByte(uchar com);
uchar Ds18b20ReadByte();
void  Ds18b20ChangTemp();
void  Ds18b20ReadTempCom();
int Ds18b20ReadTemp();

#endif
