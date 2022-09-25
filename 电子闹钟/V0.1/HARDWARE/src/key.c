#include"key.h"
#include"51it.h"
#include"ds1302.h"
#include"lcd.h"

/*******************************************************************************
* 函 数 名         : KEY_Scan
* 函数功能		   : 检测有按键按下并读取键值
* 输    入         : 无
* 输    出         : 无
* 模式             : mode=1，连按     mode=0，单按
*******************************************************************************/
char KEY_Scan(char mode)
{

	static char keyl1=1;
	static char keyl2=1;
	static char keyl3=1;

	//第1列扫描
	KEY_L1_SetL;
	KEY_L2_SetH;
	KEY_L3_SetH;
	if(keyl1==1&&(KEY_H1==0||KEY_H2==0||KEY_H3==0))
	{
		Delay_ms(10);
		keyl1=0;
		if(KEY_H1==0)
		{
			return KEY1_PRESS;
		}
		else if(KEY_H2==0)
		{
			return KEY4_PRESS;
		}
		else if(KEY_H3==0)
		{
			return KEY7_PRESS;
		}
	}
	else if(KEY_H1==1&&KEY_H2==1&&KEY_H3==1)
	{
		keyl1=1;
	}
	if(mode)
		keyl1=1;


	//第2列扫描
	KEY_L2_SetL;
	KEY_L1_SetH;
	KEY_L3_SetH;
	if(keyl2==1&&(KEY_H1==0||KEY_H2==0||KEY_H3==0))
	{
		Delay_ms(10);
		keyl2=0;
		if(KEY_H1==0)
		{
			return KEY2_PRESS;
		}
		else if(KEY_H2==0)
		{
			return KEY5_PRESS;
		}
		else if(KEY_H3==0)
		{
			return KEY8_PRESS;
		}
	}
	else if(KEY_H1==1&&KEY_H2==1&&KEY_H3==1)
	{
		keyl2=1;
	}
	if(mode)
		keyl2=1;


	//第3列扫描
	KEY_L3_SetL;
	KEY_L1_SetH;
	KEY_L2_SetH;
	if(keyl3==1&&(KEY_H1==0||KEY_H2==0||KEY_H3==0))
	{
		Delay_ms(10);
		keyl3=0;
		if(KEY_H1==0)
		{
			return KEY3_PRESS;
		}
		else if(KEY_H2==0)
		{
			return KEY6_PRESS;
		}
		else if(KEY_H3==0)
		{
			return KEY9_PRESS;
		}
	}
	else if(KEY_H1==1&&KEY_H2==1&&KEY_H3==1)
	{
		keyl3=1;
	}
	if(mode)
		keyl3=1;

	return KEY_UNPRESS;
}

void KEY_Press(void)
{

	key=KEY_Scan(1);
	switch(key)
	{
		case KEY1_PRESS: 
			 LED=~LED;
			 SetState=~SetState;
			 SetPlace=0;
			 Ds1302Init();	
		break;
		
		case KEY2_PRESS:
			LED=~LED;
			if(SetState)
			{
				 TIME[SetPlace]++;
				 if((TIME[SetPlace]&0x0f)>9)					 //换成BCD码。
				 {
					 TIME[SetPlace]=TIME[SetPlace]+6;
				 }
				 if((TIME[SetPlace]>=0x60)&&(SetPlace<2))		//分秒只能到59
				 {
					 TIME[SetPlace]=0;
				 }
				 if((TIME[SetPlace]>=0x24)&&(SetPlace==2))		//小时只能到23
				 {
					 TIME[SetPlace]=0;
				 }
				 if((TIME[SetPlace]>=0x32)&&(SetPlace==3))		//日只能到31
				 {
					 TIME[SetPlace]=1;	
				 }
				 if((TIME[SetPlace]>=0x13)&&(SetPlace==4))		//月只能到12
				 {
					 TIME[SetPlace]=1;
				 }	
				 if((TIME[SetPlace]>=0x08)&&(SetPlace==5))		//周只能到7
				 {
					 TIME[SetPlace]=1;
				 }
			}
			else
			if(Alarm_SetState)
			{
				 ALARM[SetPlace]++;
				 if((ALARM[SetPlace]&0x0f)>9)					 //换成BCD码。
				 {
					 ALARM[SetPlace]=ALARM[SetPlace]+6;
				 }
				 if((ALARM[SetPlace]>=0x60)&&(SetPlace<2))		//分秒只能到59
				 {
					 ALARM[SetPlace]=0;
				 }
				 if((ALARM[SetPlace]>=0x24)&&(SetPlace==2))		//小时只能到23
				 {
					 ALARM[SetPlace]=0;
				 }
				 if((ALARM[SetPlace]>=0x32)&&(SetPlace==3))		//日只能到31
				 {
					 ALARM[SetPlace]=1;	
				 }
				 if((ALARM[SetPlace]>=0x13)&&(SetPlace==4))		//月只能到12
				 {
					 ALARM[SetPlace]=1;
				 }	
				 if((ALARM[SetPlace]>=0x08)&&(SetPlace==5))		//周只能到7
				 {
					 ALARM[SetPlace]=1;
				 }
			}
		break;
		
		case KEY3_PRESS:
			 LED=~LED;
			if(SetState)
			{
				 TIME[SetPlace]--;
				 if((TIME[SetPlace]&0x0f)>9)					 //换成BCD码。
				 {
					 TIME[SetPlace]=TIME[SetPlace]-6;
				 }
				 if((TIME[SetPlace]>=0x60)&&(SetPlace<2))		//分秒只能到59
				 {
					 TIME[SetPlace]=0x59;
				 }
				 if((TIME[SetPlace]>=0x24)&&(SetPlace==2))		//小时只能到23
				 {
					 TIME[SetPlace]=0x23;
				 }
				 if((TIME[SetPlace]>=0x32 || TIME[SetPlace]==0)&&(SetPlace==3))		//日只能到31
				 {
					 TIME[SetPlace]=0x31;	
				 }
				 if((TIME[SetPlace]>=0x13 || TIME[SetPlace]==0)&&(SetPlace==4))		//月只能到12
				 {
					 TIME[SetPlace]=0x12;
				 }	
				 if((TIME[SetPlace]>=0x08)&&(SetPlace==5))		//周只能到7
				 {
					 TIME[SetPlace]=0x7;
				 }
			}
			else
			if(Alarm_SetState)
			{
				 ALARM[SetPlace]--;
				 if((ALARM[SetPlace]&0x0f)>9)					 //换成BCD码。
				 {
					 ALARM[SetPlace]=ALARM[SetPlace]-6;
				 }
				 if((ALARM[SetPlace]>=0x60)&&(SetPlace<2))		//分秒只能到59
				 {
					 ALARM[SetPlace]=0x59;
				 }
				 if((ALARM[SetPlace]>=0x24)&&(SetPlace==2))		//小时只能到23
				 {
					 ALARM[SetPlace]=0x23;
				 }
				 if((ALARM[SetPlace]>=0x32)&&(SetPlace==3))		//日只能到31
				 {
					 ALARM[SetPlace]=0x31;	
				 }
				 if((ALARM[SetPlace]>=0x13)&&(SetPlace==4))		//月只能到12
				 {
					 ALARM[SetPlace]=0x12;
				 }	
				 if((ALARM[SetPlace]>=0x08)&&(SetPlace==5))		//周只能到7
				 {
					 ALARM[SetPlace]=0x7;
				 }
			 }
		break;
			
		case KEY4_PRESS:
			 LED=~LED;
//			 if(SetState)
//			 {
				  SetPlace++;
				  if(SetPlace>=7)
				  SetPlace=0;
//			 }	
//			else
//			if(Alarm_SetState)
//			{	
//				  SetPlace++;
//				  if(SetPlace>=7)
//				  SetPlace=0;			
//			}		 
		break;
			 
		
		case KEY5_PRESS: 
			  LED=~LED;
			  LcdWriteCom(0x01);  //清屏
			  LCD_MODE++;
		      if(LCD_MODE>=4)
			  {
				LCD_MODE=TIME_MODE;
			  }
		break;
		
		case KEY6_PRESS:
			  LED=~LED;
			  if(LCD_MODE==ALARM_MODE)
			  {
				Alarm_SetState=~Alarm_SetState;
				SetPlace=0;
				LcdWriteCom(0x8E+0X40);
				if(Alarm_SetState)
				LcdWriteData('O');
				else
				LcdWriteData('C');
				break;
			  } 
			  
		
		
		
		
		case KEY7_PRESS: 
			  LED=~LED;
		break;
		
		case KEY8_PRESS:
			  LED=~LED;
		break;
		
		case KEY9_PRESS: 
			  LED=~LED;
		break;
		
		
	}

}
