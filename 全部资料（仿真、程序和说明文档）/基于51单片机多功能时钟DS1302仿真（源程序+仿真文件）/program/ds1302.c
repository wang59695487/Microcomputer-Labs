#include "ds1302.h"
unsigned char code read_rtc_addr[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d}; 
unsigned char code write_rtc_addr[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};

unsigned char ds1302read(unsigned char addr)
{
	unsigned char i,dat,dat1;
	ce=0;
	_nop_();
	
	sclk=0;
	_nop_();
	ce=1;
	_nop_();
	
	for(i=0;i<8;i++)
	{
		dsio=addr&0x01;
		addr=addr>>1;
		sclk=1;
		_nop_();
		sclk=0;
		_nop_();
	}
	_nop_();
	
	for(i=0;i<8;i++)
	{
		dat1=dsio;
		dat=((dat>>1)|(dat1<<7));
		sclk=1;
		_nop_();
		sclk=0;
		_nop_();
	}
	
	ce=0;
	_nop_();
	sclk=1;
	_nop_();
	dsio=0;
	_nop_();
	dsio=1;
	_nop_();
	
	return(dat);
}
void ds1302write(unsigned char addr,unsigned char dat)
{
	unsigned char i;
	ce=0;
	_nop_();
	
	sclk=0;
	_nop_();
	ce=1;
	_nop_();
	
	for(i=0;i<8;i++)
	{
		dsio = addr&0x01;
		addr=addr>>1;
		sclk=1;
		_nop_();
		sclk=0;
		_nop_();
	}

	for(i=0;i<8;i++)
	{
		dsio=dat&0x01;
		dat=dat>>1;
		sclk=1;
		_nop_();
		sclk=0;
		_nop_();
	}
	
	ce=0;
	_nop_();
}
void ds1302writetime()
{
	unsigned char i;
	ds1302write(0x8e,0x00);
	for(i=0;i<7;i++)
	{
		ds1302write(write_rtc_addr[i],time[i]);
	}
	ds1302write(0x8e,0x80);
}
void ds1302readtime()
{
	unsigned char i;
	for(i=0;i<7;i++)
	{
		time[i]=ds1302read(read_rtc_addr[i]);
	}
}