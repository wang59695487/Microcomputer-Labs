#include <reg51.h>
#include "ds1302.h"
#include "lcd1602.h"
bit adjust,init,rulecheck,flag,flagbuz,flagtim,s_tr,t_tr,t_inwork;
sbit buzzer=P2^7; sbit k1=P1^0; sbit k2=P1^1; sbit k3=P1^2; sbit k4=P1^3;
unsigned int countbuz,countbut1;
unsigned long s_time,t_time;
unsigned char i,j,premode,mode,count,countbut;
unsigned char time[7];
unsigned char k[7]={1,2,3,4,5,6,0}; //起始年份为2018年
unsigned char alarm[3][4]={{0x00,0x00,0x12,0},{0x00,0x00,0x12,0},{0x00,0x00,0x12,0}};
unsigned char code string0[]={"alarm"};
unsigned char code string1[]={"stop-watch"};
unsigned char code string2[]={"timer"};
unsigned char code string3[]={"Press any buttonto cancel alarm!"};
void main(void)
{
	unsigned char a;
	TMOD=0x11;
	TH0=0xdc;
	TL0=0x00;
	TH1=0xfc;
	TL1=0x66;
	EA=1;
	ET0=ET1=1;
	TR0=TR1=1;
	countbut1=0;
	s_time=t_time=0;
	adjust=init=rulecheck=flag=flagbuz=flagtim=s_tr=t_tr=t_inwork=0;
	i=j=mode=count=countbut=0;
	lcdinit();
	while(1)
	{
		while(mode==0)
		{	
			if(init==1)
			{
				lcdinit();
				init=0;
			}
			if(rulecheck==1)
			{
				time[i]++;
				if(i==6)
				{
					if((2000+time[6]/16*10+time[6]%16)%4==0)
					{
						for(a=0;a<7;a++)
						{
							k[a]+=2;
							if(k[a]>6)
								k[a]-=7;
						}
					}
					else
					{
						for(a=0;a<7;a++)
						{
							k[a]++;
							if(k[a]>6)
								k[a]-=7;
						}
					}
				}					
				if(time[0]%16>9)
				{
					time[0]&=0xf0;
					time[0]+=0x10;		
				}		
				if(time[0]>0x59)
					time[0]=0;
				if(time[1]%16>9)
				{
					time[1]&=0xf0;
					time[1]+=0x10;		
				}
				if(time[1]>0x59)
					time[1]=0;
				if(time[2]%16>9)
				{
					time[2]&=0xf0;
					time[2]+=0x10;		
				}
				if(time[2]>0x23)
					time[2]=0;
				if(time[3]%16>9)
				{
					time[3]&=0xf0;
					time[3]+=0x10;		
				}	
				if(time[4]==0x01||0x03||0x05||0x07||0x08||0x10||0x12)
				{
					if(time[3]>0x31)
						time[3]=0x01;
				}	
				if(time[4]==0x04||0x06||0x09||0x11)
				{
					if(time[3]>0x30)
						time[3]=0x01;
				}	
				if((2000+time[6]/16*10+time[6]%16)%4==0&&time[4]==0x02)
				{
					if(time[3]>0x29)
						time[3]=0x01;
				}
				else if(time[4]==0x02)
				{
					if(time[3]>0x28)
						time[3]=0x01;
				}		
				if(time[4]%16>9)
				{
					time[4]&=0xf0;
					time[4]+=0x10;		
				}
				if(time[4]>0x12)
					time[4]=0x01;		
				if(time[4]==0x01||time[4]==0x10)
					time[5]=(k[0]+time[3]/16*10+time[3]%16)%7;
				else if(time[4]==0x05)
					time[5]=(k[1]+(time[3]/16*10+time[3]%16))%7;
				else if(time[4]==0x08)
					time[5]=(k[2]+(time[3]/16*10+time[3]%16))%7;
				else if(time[4]==0x02||time[4]==0x03||time[4]==0x11)
					time[5]=(k[3]+(time[3]/16*10+time[3]%16))%7;
				else if(time[4]==0x06)
					time[5]=(k[4]+(time[3]/16*10+time[3]%16))%7;
				else if(time[4]==0x09||time[4]==0x12)
					time[5]=(k[5]+(time[3]/16*10+time[3]%16))%7;
				else if(time[4]==0x04||time[4]==0x07)
					time[5]=(k[6]+(time[3]/16*10+time[3]%16))%7;
				if(time[5]==0)
					time[5]=7;
				if(time[6]%16>9)
				{
					time[6]&=0xf0;
					time[6]+=0x10;		
				}	
				if(time[6]>0x99)
					time[6]=0;
				rulecheck=0;
			}
			
			if(adjust==1)
				ds1302writetime();
			ds1302readtime();
			
			if(rulecheck==0)
			{
				lcdwritecom(0x81);
				if(adjust==1&&flag==1&&i==6)
				{
					lcdwritedata(' ');
					lcdwritedata(' ');
					lcdwritedata(' ');
					lcdwritedata(' ');
				}
				else
				{
					lcdwritedata('2');
					lcdwritedata('0');
					lcdwritedata('0'+time[6]/16);
					lcdwritedata('0'+time[6]%16);
				}
				lcdwritedata('-');
				if(adjust==1&&flag==1&&i==4)
				{
					lcdwritedata(' ');
					lcdwritedata(' ');
				}
				else
				{
					lcdwritedata('0'+time[4]/16);
					lcdwritedata('0'+time[4]%16);
				}
				lcdwritedata('-');
				if(adjust==1&&flag==1&&i==3)
				{
					lcdwritedata(' ');
					lcdwritedata(' ');
				}
				else
				{
					lcdwritedata('0'+time[3]/16);
					lcdwritedata('0'+time[3]%16);
				}
				lcdwritedata('(');
				switch(time[5])
				{
					case 1: lcdwritedata('s');lcdwritedata('u');lcdwritedata('n'); break;
					case 2: lcdwritedata('m');lcdwritedata('o');lcdwritedata('n'); break;
					case 3: lcdwritedata('t');lcdwritedata('u');lcdwritedata('e'); break;
					case 4: lcdwritedata('w');lcdwritedata('e');lcdwritedata('d'); break;
					case 5: lcdwritedata('t');lcdwritedata('h');lcdwritedata('u'); break;
					case 6: lcdwritedata('f');lcdwritedata('r');lcdwritedata('i'); break;
					case 7: lcdwritedata('s');lcdwritedata('a');lcdwritedata('t'); break;
				}
				lcdwritedata(')');
				
				lcdwritecom(0x80+0x44);
				if(adjust==1&&flag==1&&i==2)
				{
					lcdwritedata(' ');
					lcdwritedata(' ');			
				}
				else
				{
					lcdwritedata('0'+time[2]/16);
					lcdwritedata('0'+time[2]%16);
				}
				lcdwritedata(':');
				if(adjust==1&&flag==1&&i==1)
				{
					lcdwritedata(' ');
					lcdwritedata(' ');			
				}
				else
				{
					lcdwritedata('0'+time[1]/16);
					lcdwritedata('0'+time[1]%16);
				}
				lcdwritedata(':');
				if(adjust==1&&flag==1&&i==0)
				{
					lcdwritedata(' ');
					lcdwritedata(' ');			
				}
				else
				{
					lcdwritedata('0'+time[0]/16);
					lcdwritedata('0'+time[0]%16);
				}
				if(alarm[0][3]==1||alarm[1][3]==1||alarm[2][3]==1)
					lcdwritedata(1);
			}
		}
		while(mode==1)
		{
			if(init==1)
			{
				lcdinit();
				init=0;
			}
			if(rulecheck==1)
			{
				alarm[j][i]++;
				if(alarm[j][0]%16>9)
				{
					alarm[j][0]+=0x10;
					alarm[j][0]&=0xf0;
				}
				if(alarm[j][0]>0x59)
					alarm[j][0]=0;
				if(alarm[j][1]%16>9)
				{
					alarm[j][1]&=0xf0;
					alarm[j][1]+=0x10;
				}
				if(alarm[j][1]>0x59)
					alarm[j][1]=0;
				if(alarm[j][2]%16>9)
				{
					alarm[j][2]&=0xf0;
					alarm[j][2]+=0x10;
				}
				if(alarm[j][2]>0x23)
					alarm[j][2]=0;
				rulecheck=0;
			}
			else
			{
				lcdwritecom(0x85);
				for(a=0;a<5;a++)
					lcdwritedata(string0[a]);
				lcdwritedata('0'+j);
				
				lcdwritecom(0x80+0x44);
				if(adjust==1&&flag==1&&i==2)
				{
					lcdwritedata(' ');
					lcdwritedata(' ');
				}
				else
				{
					lcdwritedata('0'+alarm[j][2]/16);
					lcdwritedata('0'+alarm[j][2]%16);
				}
				lcdwritedata(':');
				if(adjust==1&&flag==1&&i==1)
				{
					lcdwritedata(' ');
					lcdwritedata(' ');
				}
				else
				{
					lcdwritedata('0'+alarm[j][1]/16);
					lcdwritedata('0'+alarm[j][1]%16);
				}
				lcdwritedata(':');
				if(adjust==1&&flag==1&&i==0)
				{
					lcdwritedata(' ');
					lcdwritedata(' ');
				}
				else
				{
					lcdwritedata('0'+alarm[j][0]/16);
					lcdwritedata('0'+alarm[j][0]%16);
				}
				if(alarm[j][3]==1)
					lcdwritedata(0);
				else
					lcdwritedata(' ');
			}
		}
		while(mode==2)
		{
			if(init==1)
			{
				lcdinit();
				init=0;
			}
			if(s_time%10000/100>59)
			{
				s_time-=6000;
				s_time+=10000;
			}
			if(s_time%1000000/10000>59)
			{
				s_time-=600000;
				s_time+=1000000;
			}
			lcdwritecom(0x83);
			for(a=0;a<10;a++)
				lcdwritedata(string1[a]);
			
			lcdwritecom(0x80+0x42);
			lcdwritedata('-');
			lcdwritedata('0'+s_time/10000000);
			lcdwritedata('0'+s_time%10000000/1000000);
			lcdwritedata(':');
			lcdwritedata('0'+s_time%1000000/100000);
			lcdwritedata('0'+s_time%100000/10000);
			lcdwritedata(':');
			lcdwritedata('0'+s_time%10000/1000);
			lcdwritedata('0'+s_time%1000/100);
			lcdwritedata(':');
			lcdwritedata('0'+s_time%100/10);
			lcdwritedata('0'+s_time%10);
		}
		while(mode==3)
		{
			if(init==1)
			{
				lcdinit();
				init=0;
			}
			if(rulecheck==1)
			{
				if(i==0)
					t_time++;
				else if(i==1)
					t_time+=100;
				else if(i==2)
					t_time+=10000;
				else if(i==3)
					t_time+=1000000;
				if(t_time%10000/100>59)
				{
					t_time-=6000;
					t_time+=10000;
				}
				if(t_time%1000000/10000>59)
				{
					t_time-=600000;
					t_time+=1000000;
				}
				if(t_time/1000000>99)
					t_time-=100000000;
				rulecheck=0;
			}
			else
			{
				if(t_time%10000/100>59)
					t_time-=4000;
				if(t_time%1000000/10000>59)
					t_time-=400000;
				lcdwritecom(0x85);
				for(a=0;a<5;a++)
					lcdwritedata(string2[a]);
				
				lcdwritecom(0x80+0x42);
				lcdwritedata('-');
				
				if(adjust==1&&flag==1&&i==3)
				{
					lcdwritedata(' ');
					lcdwritedata(' ');
				}
				else
				{
					lcdwritedata('0'+t_time/10000000);
					lcdwritedata('0'+t_time%10000000/1000000);
				}
				lcdwritedata(':');
				if(adjust==1&&flag==1&&i==2)
				{
					lcdwritedata(' ');
					lcdwritedata(' ');
				}
				else
				{
					lcdwritedata('0'+t_time%1000000/100000);
					lcdwritedata('0'+t_time%100000/10000);
				}
				lcdwritedata(':');
				if(adjust==1&&flag==1&&i==1)
				{
					lcdwritedata(' ');
					lcdwritedata(' ');
				}
				else
				{
					lcdwritedata('0'+t_time%10000/1000);
					lcdwritedata('0'+t_time%1000/100);
				}
				lcdwritedata(':');
				if(adjust==1&&flag==1&&i==0)
				{
					lcdwritedata(' ');
					lcdwritedata(' ');
				}
				else
				{
					lcdwritedata('0'+t_time%100/10);
					lcdwritedata('0'+t_time%10);
				}
			}
		}
		while(mode==4)
		{
			if(init==1)
			{
				lcdinit();
				init=0;
			}
			lcdwritecom(0x80);
			for(a=0;a<16;a++)
				lcdwritedata(string3[a]);
			lcdwritecom(0x80+0x40);
			for(a=16;a<32;a++)
				lcdwritedata(string3[a]);
		}
	}
}
void timer0() interrupt 1
{
	TH0=0xdc;
	TL0=0x00;
	if(flagbuz==1)
	{
		count++;
		if(count==100&&mode!=3)
		{
			flag=~flag;
			init=1;
			count=0;
		}
	}	
	else if(adjust==1)
	{
		count++;
		if((count==10&&mode==0)||(count==60&&(mode==1||(mode==3&&flagbuz==0))))
		{
			flag=~flag;
			count=0;
		}
	}
	else
	{
		count=0;
		flag=0;
		i=0;
	}
	if(s_tr==1)
	{
		s_time++;
		if(s_time==99595900)
		{
			s_tr=0;
			s_time=0;
		}
	}
	if(t_tr==1)
	{
		t_time--;
		if(t_time==0)
		{
			t_tr=0;
			flagbuz=1;
			flagtim=1;
		}
	}
	if(mode==3&&t_inwork==0)
	{
		if(adjust==0)
			adjust=1;
	}
	if(flagbuz==1)
	{
		if(flagtim==1)
		{
			buzzer=0;
			countbuz++;
		}
		else
		{
			countbuz++;
			if(countbuz==1)
				premode=mode;
			if(flag==1)
			{
				mode=4;		
				buzzer=0;
			}
			else
			{
				mode=premode;
				buzzer=1;
			}
		}
		if(countbuz==500&&flagtim==1)
		{
			t_inwork=0;
			flagbuz=0;
			flagtim=0;
			buzzer=1;
			countbuz=0;
		}
		else if(countbuz==3000)
		{
			flagbuz=0;
			mode=premode;
			init=1;
			buzzer=1;
			countbuz=0;
		}
	}
}
void timer1() interrupt 3
{
	TR1=0;
	if(k1==0)
	{
		if(countbut<=20)
			countbut++;
		if(countbut==20)
		{
			if(flagbuz==1&&mode!=3)
			{
				flagbuz=0;
				mode=premode;
				init=1;
				buzzer=1;
			}
			else if(mode==0&&adjust==1)
			{
				if(i==4)
					i+=2;
				else
					i++;
				if(i>6)
					i=0;
			}
			else if(mode==1&&adjust==1)
			{
				if(i==2)
					i=0;
				else
					i++;			
			}
			else if(1)
			{
				init=1;
				if(mode==3)
				{
					mode=0;
					adjust=0;
				}
				else
					mode++;		
			}
		}
	}
	else if(k2==0)
	{
		if(countbut<=20)
			countbut++;
		if(countbut==20)
		{
			if(flagbuz==1&&mode!=3)
			{
				flagbuz=0;
				mode=premode;
				init=1;
				buzzer=1;
			}
			else if(mode==0||mode==1)
				adjust=~adjust;
			else if(mode==2&&s_time==0)
				s_tr=1;
			else if(mode==3&&adjust==1)
			{
				if(i==3)
					i=0;
				else
					i++;
			}
		}
	}
	else if(k3==0)
	{
		if(countbut<=20)
			countbut++;
		else if(countbut>20)
			countbut1++;
		if(countbut==20)
		{
			if(flagbuz==1&&mode!=3)
			{
				flagbuz=0;
				mode=premode;
				init=1;
				buzzer=1;
			}
			else if(mode==0&&adjust==1)
				rulecheck=1;
			else if(mode==1&&adjust==0)
			{
				if(j<2)
					j++;
				else
					j=0;
			}
			else if(mode==1&&adjust==1)
				rulecheck=1;
			else if(mode==2&&s_time!=0)
				s_tr=~s_tr;
			else if(mode==3&&t_inwork==0)
				rulecheck=1;
			else if(mode==3&&t_inwork==1)
				t_tr=~t_tr;
		}
		else if(countbut1==320)
		{
			if(mode==0&&adjust==1)
				rulecheck=1;
			else if(mode==1&&adjust==1)
				rulecheck=1;
			else if(mode==3&&t_inwork==0)
				rulecheck=1;
			countbut1=0;
		}
	}
	else if(k4==0)
	{
		if(countbut<=20)
			countbut++;
		if(countbut==20)
		{
			if(flagbuz==1&&mode!=3)
			{
				flagbuz=0;
				mode=premode;
				init=1;
				buzzer=1;
			}
			else if(mode==1&&adjust==0)
				alarm[j][3]=!alarm[j][3];
			else if(mode==2&&s_tr==0)
				s_time=0;
			else if(mode==3&&t_inwork==0&&t_time!=0)
			{
				t_tr=1;
				t_inwork=1;
				adjust=0;
			}
			else if(mode==3&&t_tr==0)
			{	
				t_time=0;
				t_inwork=0;
			}
		}
	}
	else if(1)
	{
		countbut=0;
		countbut1=0;
	}
	
	if(alarm[0][3]==1&&adjust==0)
	{
		if(alarm[0][2]==time[2])
			if(alarm[0][1]==time[1])
				if(alarm[0][0]==time[0])
					if(countbuz==0)
						flagbuz=1;
	}
	if(alarm[1][3]==1&&adjust==0)
	{
		if(alarm[1][2]==time[2])
			if(alarm[1][1]==time[1])
				if(alarm[1][0]==time[0])
					if(countbuz==0)
						flagbuz=1;
	}
	if(alarm[2][3]==1&&adjust==0)
	{
		if(alarm[2][2]==time[2])
			if(alarm[2][1]==time[1])
				if(alarm[2][0]==time[0])
					if(countbuz==0)
						flagbuz=1;
	}
	TH1=0xfc;
	TL1=0x66;
	TR1=1;
}