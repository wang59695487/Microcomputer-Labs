#include"Feiyun.h"
uchar sws=3;
void Init()
{
	LcdInit();
	TimeDateInit();
	TimerInit();	
}
void KeyPro()
{
	KEY temp;
	ReadKey(&temp);	
	if(temp.c_key==0x0a)
	cls,sws=1;
	if(temp.c_key==0x0b)
	cls,sws=2;
	if(temp.c_key==0x0c)
	Set(0x08);
	if(temp.c_key==0x0d)
	Set(0x47);
	if(temp.c_key==0x0e)
	sws=3;
	if(temp.c_key==0x0f)
	sws=0;
}
void MsgPro()
{
    if(timer.iscg&0xf0)  
	{
        timer.iscg&=0x0f;
		DateCg();
		if(sws==0)
	    {
			BuzzClose;
			TimeShow();
	    	DateShow();
	    }
	    else if(sws==1)
		{	    
			TempShow();
		}
		else if(sws==2)
		{
	    	AlarmClock();
		}
		else if(sws==3)
		{	
			TimeShow();
	    	DateShow();
		    if(CheckTime())
			    BuzzOpen;
		}	 	 
	}	
}
void main()
{
	Init();
	while(1)
	{
	    MsgPro();
		if(KeyDown) 
		KeyPro();	  	 
	}			 
}