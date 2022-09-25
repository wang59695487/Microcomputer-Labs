#include "lcd1602.h"
unsigned char table0[7]={0x00,0x04,0x0e,0x1f,0x0e,0x04,0x00};
unsigned char table1[7]={0x00,0x08,0x14,0x1c,0x14,0x00,0x00};
void lcd1602delay1ms(unsigned char ms)
{
    unsigned char a,b;
		for(;ms>0;ms--)
		{
			for(b=4;b>0;b--)
        for(a=113;a>0;a--);
		}
}
void lcdwritecom(unsigned char com)
{
	lcde=0;
	rs=0;
	rw=0;
	
	P0 = com;
	lcd1602delay1ms(1);
	
	lcde=1;
	lcd1602delay1ms(5);
	lcde=0;
}
void lcdwritedata(unsigned char dat)
{
	lcde=0;
	rs=1;
	rw=0;
	
	P0 = dat;
	lcd1602delay1ms(1);
	
	lcde=1;
	lcd1602delay1ms(5);
	lcde=0;
}
void lcdinit()
{
	unsigned char a;
	lcdwritecom(0x38);
	lcdwritecom(0x0c);
	lcdwritecom(0x06);
	lcdwritecom(0x01);
	lcdwritecom(0x40);
	for(a=0;a<7;a++)
		lcdwritedata(table0[a]);
	for(a=0;a<7;a++)
		lcdwritedata(table1[a]);
}
