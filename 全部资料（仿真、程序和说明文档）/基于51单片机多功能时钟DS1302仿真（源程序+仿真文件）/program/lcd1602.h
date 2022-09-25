#ifndef _LCD1602_H
#define _LCD1602_H

#include <reg51.h>

sbit rs = P2^0;
sbit rw = P2^1;
sbit lcde = P2^2;

void lcd1602delay1ms(unsigned char ms);
void lcdwritecom(unsigned char com);
void lcdwritedata(unsigned char dat);
void lcdinit();

#endif
