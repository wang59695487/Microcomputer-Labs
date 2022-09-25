/*---------------------LCD1602.h--------------------*/
#include<reg52.h>
#include<intrins.h>
#include<string.h>
#define uchar unsigned char
#define uint unsigned int

sbit RS=P2^6;	  //LCD1602?????
sbit RW=P2^5;	  //LCD1602????
sbit EN=P2^7;	  //LCD1602???

Delay(uint ms)  //??
{
	uchar i;
	while(ms--); for(i=0;i<120;i++);
}

/*------LCD1602????------*/
 
//??LCD???
uchar Read_LCD_State()		 
{
	uchar state;
	RS=0; RW=1; EN=1; 
	_nop_();
	state=P0; EN=0;
	_nop_();
	return state;
}

//??LCD1602???
void LCD_Busy_Wait()		 
{
	while((Read_LCD_State()&0x80)==0x80);
	Delay(5);
}

//?LCD1602????
void Write_LCD_Data(uchar dat)
{
	LCD_Busy_Wait();		//???
	RS=1; RW=0; EN=0;
	P0=dat; EN=1;
	_nop_(); _nop_();
	EN=0;
}

//?LCD1602????
void Write_LCD_Command(uchar cmd)
{
	LCD_Busy_Wait();
	RS=0; RW=0; EN=0; 
	P0=cmd; EN=1;
	_nop_(); _nop_();
	EN=0;
}

//LCD1602???
void Init_LCD()
{
	Write_LCD_Command(0x38); Delay(1);		  /*????,????8?,????*/
	Write_LCD_Command(0x08); Delay(1);		  //????
    Write_LCD_Command(0x01); Delay(1);        //??
	Write_LCD_Command(0x06); Delay(1);	     /*??????,????,????*/
	Write_LCD_Command(0x0c); Delay(1);		  //???,???
}

//?????
void ShowString(uchar x,uchar y,uchar *str)
{	unsigned char i = 0; 
	if(y == 0)							//????????
		Write_LCD_Command(0x80 | x);
	if(y == 1)
		Write_LCD_Command(0xc0 | x);
	for(i=0;i<16;i++)					//?????
	{
	 	Write_LCD_Data(str[i]);	
	}
}  
