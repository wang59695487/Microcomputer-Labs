#include"Feiyun.h"
TIMER timer;
void  TimerInit(void)  ///定时器初始化
{  
   ET0=0;
   TMOD&=0xf0;
   TMOD|=0x02;
   TCON=0x00;
   TL0= TL0_value;
   TH0=	TH0_value;
   ET0=1; 
   EA=1;
   TR0=1; 
}
void  timer0_interrupt() interrupt 1 using 1   //定时器中断
{ 
   static char tick=0;
   TF0=0;
   tick++; 
   if(tick==4)
   {
       timer.iscg|=0x01;
	   tick=0;     
	   timer.count++;
	   if(timer.count==1000)
	   {
	       timer.count=0;
		   timer.iscg|=0x10;
		   TimeCg();	
	   }   
   }
}