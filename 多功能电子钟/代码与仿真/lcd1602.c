#include"Feiyun.h"
void write_com(uchar com)
{	
	lcdrs=0;
	lcdrw=0;
	P0=com;
	delay(1);
	lcden=1;
	delay(1);
	lcden=0;
}
void write_data(uchar date)
{    
	lcdrs=1;
	lcdrw=0;
	P0=date;
	delay(1);
	lcden=1;
	delay(1);
	lcden=0;
} 
void LcdInit(void)
{
	lcden=0;
	write_com(0x38);
	write_com(0x0f);
	write_com(0x06);
	write_com(0x01);
}
void LcdChar(uchar p,uchar dat)
{
	pd(p);
	write_data(dat);
	pd(0x50);
}
void LcdStr(uchar p,String str)
{
	pd(p);
	while(*str!='\0')
    {
      write_data(*str);
      str++;		         //指向下一个要发送的数据
    }
	pd(0x50);
}
void LcdData(uchar p,uchar dat)
{
	pd(p);
	write_data(dat/10+0x30);
	write_data(dat%10+0x30);
	pd(0x50);
}
