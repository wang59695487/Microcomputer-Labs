/*-----------------clock.c------------------*/
#include<reg52.h>
#include<string.h>
#include<LCD1602.h>
#include<DS1302.h>
#include<18B20.h>
#define uchar unsigned char
#define uint unsigned int

sbit K1=P2^3;	  //??????
sbit K2=P2^2;	  //????
sbit K3=P2^1;	  //????
sbit K4=P2^0;	  //??
sbit Bell=P3^3;
uchar *WEEK[]={"SUN","MON","TUS","WEN","THU","FRI","SAT"};	/*????*/
uchar MonthsDays[]={0,31,0,31,30,31,30,31,31,30,31,30,31};	/*???,2??????*/
uchar LCD_DSY_BUFFER1[]={"DATE 00-00-00   "};	 //??????
uchar LCD_DSY_BUFFER2[]={"   C 00:00:00   "};
uchar a[]={"00"};
uchar DateTime[7];			//??????
char Adjust_Index=-1;
uchar Change_Flag[]="-MHDM-Y";uint p=0; 
void Format_DateTime(uchar d, uchar *a)		/*?????????????*/
{ a[0]=d/10+'0';a[1]=d%10+'0';}
uchar isLeapYear(uint y)  //???????
{	
return (y%4==0 && y%100!=0) || (y%400==0);}
//??????,?2000.1.1???? ,??1999.12.31???
void RefreshWeekDay()
{	uint i,d,w=5;
	for(i=2000;i<2000+DateTime[6]; i++)
	{	d=isLeapYear(i) ? 366 : 365;
		w=(w+d)%7;}	//?????12.31???	
	d=0;
	for(i=1; i<DateTime[4]; i++)
	d+=MonthsDays[i];  //??????
	d+=DateTime[3];
	DateTime[5]=(w+d)%7+1;}
//??????????
void DateTime_Adjust(char x)
{
	switch(Adjust_Index)
	{
		case 6: if(x==1 && DateTime[6]<99) DateTime[6]++;			   //?,???00-99
				if(x==-1 && DateTime[6]>0) DateTime[6]--;
				MonthsDays[2]=isLeapYear(2000+DateTime[6])?29:28;
				RefreshWeekDay();									   //????
				break;
		case 4: if(x==1) DateTime[4]++;			  //?,???1-12
				if(DateTime[4]>12) DateTime[4]=1;		 /*????,???????*/
				if(x==-1 ) DateTime[4]--;
				if(DateTime[4]<1) DateTime[4]=12;
				MonthsDays[2]=isLeapYear(2000+DateTime[6])?29:28;
				if(DateTime[3]!=MonthsDays[DateTime[4]])
					DateTime[3]=MonthsDays[DateTime[4]];
				RefreshWeekDay();
				break;
		case 3: MonthsDays[2]=isLeapYear(2000+DateTime[6])?29:28; //?
				if(x==1) DateTime[3]++;
				if(DateTime[3]>MonthsDays[DateTime[4]])	 DateTime[3]=1;		//????,????????
				if(x==-1) DateTime[3]--;
				if(DateTime[3]<1) DateTime[3]=MonthsDays[DateTime[4]];
				RefreshWeekDay();
				break;
		case 2: if(x==1) DateTime[2]++;	 //??
				if(DateTime[2]>23) DateTime[2]=0;			 //????
				if(x==-1 && DateTime[2]>0) DateTime[2]--;
				break;
		case 1: if(x==1) DateTime[1]++;	 //??
				if(DateTime[1]>59) DateTime[1]=0;
				if(x==-1 && DateTime[1]>0) DateTime[1]--;
				break;
	}
}
void T0_INT0() interrupt 1	 //???0??,??????
{	Bell=~Bell;
	p++;
	if(p<400)			  //??
	{		TH0=(8192-700)/32;
		     TL0=(8192-700)%32;
	}
	else if(p<800)		  //??
	{
		TH0=(8192-1000)/32;
		TL0=(8192-1000)%32;
	}
	else
	{   TR0=0;			   //?????,??????
		p=0;
	}	
}
void EX_INT0() interrupt 0	 //????0,??????
{	if(K1==0)
	{	while(K1==0);
		if(Adjust_Index==-1 || Adjust_Index==1) 
		Adjust_Index=7;	         //??K1????????
		Adjust_Index--;			  /*??????????????*/
		if(Adjust_Index==5) Adjust_Index=4;	  /*????????*/
		LCD_DSY_BUFFER2[13]='[';
		LCD_DSY_BUFFER2[14]=Change_Flag[Adjust_Index];
		LCD_DSY_BUFFER2[15]=']';
	}
	else if(K2==0)						
		{	while(K2==0); DateTime_Adjust(1);		
	}
	else if(K3==0)
	{		while(K3==0); DateTime_Adjust(-1);	   //???
	}
	else if(K4==0)
	{		while(K4==0); 
		SET_DS1302();			 //????????DS1302,????
		LCD_DSY_BUFFER2[13]=' ';
		LCD_DSY_BUFFER2[14]=' ';
		LCD_DSY_BUFFER2[15]=' ';
		Adjust_Index=-1;
	}
} 
  
//???  
void main()
{	Init_LCD();
	IE=0x83;     //??INT0?T0??
	IP=0x01;	 //???????
	IT0=0x01;	 //???????
	TMOD=0x00;	 //????????0
	TH0=(8192-700)/32;
	TL0=(8192-700)%32;
	while(1)
	{
		Format_DateTime(DateTime[6],LCD_DSY_BUFFER1+5);	  /*??????????*/
		Format_DateTime(DateTime[4],LCD_DSY_BUFFER1+8);
		Format_DateTime(DateTime[3],LCD_DSY_BUFFER1+11);
		strcpy(LCD_DSY_BUFFER1+13,WEEK[DateTime[5]-1]);	   /*????*/
		Format_DateTime(DateTime[2],LCD_DSY_BUFFER2+5);
		Format_DateTime(DateTime[1],LCD_DSY_BUFFER2+8);
		Format_DateTime(DateTime[0],LCD_DSY_BUFFER2+11);	
		ShowString(0x00,0,LCD_DSY_BUFFER1); //?LCD?????
		ShowString(0x00,1,LCD_DSY_BUFFER2);
		if(DateTime[1]==0&DateTime[0]==0)  //???? ,????
		{			
TR0=1;	
}				 //?????0
		if(Adjust_Index==-1)
 GetTime();
		wendu=Readtemperature();
     temp_g=wendu%100/10+'0';//??????????%100????
     temp_d=wendu%10+'0';
    w_dat(temp_g);   
 	 Delay(5);
     w_dat(temp_d);   
	 Delay(6);
		
	}
}
