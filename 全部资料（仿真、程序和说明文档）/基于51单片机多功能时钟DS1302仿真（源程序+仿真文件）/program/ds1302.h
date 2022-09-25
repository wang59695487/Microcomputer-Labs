#ifndef _DS1302_H_
#define _DS1302_H_

#include <reg51.h>
#include <intrins.h>

sbit dsio = P2^5;
sbit ce = P2^3;
sbit sclk = P2^4;

unsigned char ds1302read(unsigned char addr);
void ds1302write(unsigned char addr,unsigned char dat);
void ds1302init();
void ds1302readtime();
void ds1302writetime();

extern unsigned char time[7];
#endif