#include"Feiyun.h"
uchar hour=0;
uchar min=0;
uchar sec=0;
uchar year=0;
uchar month=0;
uchar day=0;
uchar ahour=0;
uchar amin=0;
void TimeDateInit()	 //时间和日期的初始化
{
	year=11;
	month=6;
	day=19;
	hour=23;
	min=0;
	sec=0;
	ahour=23;
	amin=1;
}
uchar isleep(y)
{
  return !(y%4);
}
uchar GetMDM(y,m)
{
    uchar mon[]={31,28,31,30,31,30,31,31,30,31,30,31};
	if(m==2) 
		return mon[1]+isleep(y);
	else  		 
		return mon[m-1];
}
uint GetMDY(y)
{
    if(isleep(y))
		return 366;
	else 
		return 365;
}
uchar GetWeek()
{
   	uint num=0;
	uchar i,week;
	for(i=1;i<year;i++)
	   num+=GetMDY(i);
	for(i=1;i<month;i++)
	   num+=GetMDM(year,i);
	num+=day; 
	week=num%7;
	return week;		   
}
void DateCg()
{
   if(hour==24)
   hour=0,day++;
   if(day>GetMDM(year,month))
   day=1,month++;
   if(month>12)
   month=1,year++;
}
void TimeCg()                //时间模块
{
   sec++;
   if(sec==60)
   sec=0,min++;
   if(min==60)
   min=0,hour++;  
}
String TimetoStr()       
{
	uchar time[6];
	uchar buf[6];
	uchar i;
	time[0]=hour/10-1+'1';
	time[1]=hour%10-1+'1';
	time[2]=min/10-1+'1';
	time[3]=min%10-1+'1';
	time[4]=sec/10-1+'1';
	time[5]=sec%10-1+'1';
	for(i=0;i<6;i++)
		buf[i]=time[i];
	return buf;
}
void TimeShow()		         //用LCD1602显示时间 
{
	String time;	
	time=TimetoStr();
	LcdStr(0x04,"Time");
	LcdData(0x08,hour);
	LcdChar(0x0a,'-');
	LcdData(0x0b,min);
	LcdChar(0x0d,'-');
	LcdData(0x0e,sec);
}
String DatetoStr()			 //日期模块
{
	uchar Date[6];
	uchar buf[6];
	uchar i;
	Date[0]=year/10+'1'-1;
	Date[1]=year%10+'1'-1;
	Date[2]=month/10+'1'-1;
	Date[3]=month%10+'1'-1;
	Date[4]=day/10+'1'-1;
	Date[5]=day%10+'1'-1;
	for(i=0;i<6;i++)
		buf[i]=Date[i];
	return buf;
}									
void WeekShow()
{
    uchar wk[]="Sun Mon Tue Wed Thu Fri Sat Erro";
    uchar  D[]="Date 20";
	uchar week=0;
	uchar i;
	pd(0x00);
	week=GetWeek();
	for(i=0;i<4;i++)
	write_data(wk[week*4+i]);
	pd(0x40);
	for(i=0;i<7;i++)
	write_data(D[i]);
}
void DateShow()
{
	String date;
	WeekShow();
	date=DatetoStr();
	write_data(date[0]);
	write_data(date[1]);
	write_data('-');
	write_data(date[2]);
	write_data(date[3]);
	write_data('-');
	write_data(date[4]);
	write_data(date[5]);
	pd(0x50);
}
void Loadbuf(uchar p,String buf)
{
   if(p==0x08)
	{
		buf[0]=hour/10;
		buf[1]=hour%10;
		buf[2]=min/10;
		buf[3]=min%10;
		buf[4]=sec/10;
		buf[5]=sec%10;
	}
   if(p==0x47)
	{
		buf[0]=year/10;
		buf[1]=year%10;
		buf[2]=month/10;
		buf[3]=month%10;
		buf[4]=day/10;
		buf[5]=day%10;
	}	
}
void Save(uchar p,String buf)
{
	if(p==0x08)
	{
		hour=buf[0]*10+buf[1];
		min=buf[2]*10+buf[3];
		sec=buf[4]*10+buf[5];
	}
	if(p==0x47)
	{
		year=buf[0]*10+buf[1];
		month=buf[2]*10+buf[3];
		day=buf[4]*10+buf[5];
	}
}
void Set(uchar p)
{
   uchar i=0;
   uchar tmp[8]={0,1,1,2,3,3,4,5};
   uchar imr[8]={1,3,4,4,6,6,7,0};
   uchar iml[8]={7,0,1,1,3,4,4,6};
   uchar buf[6]={0,0,0,0,0,0};
   uchar dat=0x10;	   
   Loadbuf(p,buf);							 
   while((dat!=0x0f)&&(dat!=0x0e))
   {
       if(KeyDown) dat=scankey();
	   if(dat<0x10)
	   {
	   	   if(dat<0x0a)
	       {
		   buf[tmp[i]]=dat;
		   write_data(buf[tmp[i]]+'1'-1);
		   dat=0x10;
		   i=imr[i];
		   }
		   else
		   {
		  	switch (dat)
			{
			   case 12:
			           {
					    dat=0x10;
		                i=iml[i];
						break;
						}
			   case 13:{
			            dat=0x10;
		                i=imr[i];
						break;
			            }
			   case 14:
			            { 
						Save(p,buf);
						break;
						}
			   case 15:break; 
			}
		    }
	    }
	    pd(p+i);
   }
   pd(0x50);   
}

void setahour()
{
   	uchar dat=0xff,state;
	pd(0x45);
	while(dat!=0x0e) 
	{ 
		if(dat<0x10)
		{
		  	if(state==0)
			{
				 state++;
				 ahour=ahour%10;
				 ahour=ahour+dat*10;
				 LcdData(0x45,ahour);
				 pd(0x46);
			}
			else
			{
			     state=0;
				 ahour=ahour/10;
				 ahour=ahour*10;
				 ahour=ahour+dat;
				 LcdData(0x45,ahour);
				 pd(0x45);
			}
		}
		if(KeyDown) dat=scankey();
		else dat=0xff;	
	} 
	pd(0x50);
}
void setamin()
{
   	uchar dat=0xff,state;
	pd(0x4c);
	while(dat!=0x0e) 
	{
		if(dat<0x10)
		{
		  	if(state==0)
			{
				 state++;
				 amin=amin%10;
				 amin=amin+dat*10;
				 LcdData(0x4c,amin);
				 pd(0x4d);
			}
			else
			{
			     state=0;
				 amin=amin/10;
				 amin=amin*10;
				 amin=amin+dat;
				 LcdData(0x4c,amin);
				 pd(0x4c);
			}
		}
		if(KeyDown) dat=scankey();
		else dat=0xff;	
	} 
	pd(0x50);
}
void AlarmClock()
{
   	uchar dat;
	LcdStr(0x00,"The Alarm Clock:");
	LcdStr(0x40,"Hour");
	LcdData(0x45,ahour);
	LcdStr(0x48,"Min");
	LcdData(0x4c,amin);
	while((dat!=0x0f)&&(dat!=0x0e))
	{
	     if(KeyDown) dat=scankey();
		 else dat=0xff;
		 if(dat==0x0c) setahour();
		 if(dat==0x0d) setamin(); 
	}
}
uchar CheckTime()
{
   if(hour==ahour&&min==amin)
   return 1;
   else return 0;
}
