/*-------------------------DS1302.h-------------------------*/
#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit RST=P3^4;	  //DS1302??
sbit IO=P3^5;	  //DS1302????/??
sbit SCLK=P3^6;	  //DS1302??????
uchar DateTime[7];			//??????
 
 /*-------DS1302????-------*/
 
//?DS1302????
void Write_To_DS1302(uchar x)	
{
	uchar i;
	for(i=0;i<8;i++)
	{
		IO=x & 0x01; SCLK=1; SCLK=0; x>>=1;
    }
}

//?DS1302?????
uchar Get_From_DS1302()			 
{
	uchar i,b,t;
	for(i=0;i<8;i++)
	{
		b>>=1; t=IO; b|=t<<7; SCLK=1; SCLK=0;
	}
	return b / 16*10+b%16;		 //??BCD?
}

//?DS1302????????
uchar Read_Data(uchar addr)		 
{
	uchar dat;
	RST=0; SCLK=0; RST=1;
	Write_To_DS1302(addr);
	dat=Get_From_DS1302();
	SCLK=1; RST=0;
	return dat;
}

//?DS1302????????
void Write_DS1302(uchar addr,uchar dat)		
{
	SCLK=0; RST=1;
	Write_To_DS1302(addr);
	Write_To_DS1302(dat);
	SCLK=0; RST=0;
}

//????
void SET_DS1302()			  
{
	uchar i;
	Write_DS1302(0x8e,0x00);  //????
	for(i=0;i<7;i++)
	{
		Write_DS1302(0x80+2*i,(DateTime[i]/10<<4)| (DateTime[i]%10));
	}
	Write_DS1302(0x8e,0x80);  //???
}

//??????							  
void GetTime()				  
{
	uchar i;
	for(i=0; i<7; i++)
	{
		DateTime[i]= Read_Data(0x81+2*i);
	}
}