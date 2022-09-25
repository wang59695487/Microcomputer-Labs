/*******************************************************************************
* 实验名			   : 万年历实验
* 使用的IO	     : 
* 实验效果       :1602显示时钟，按K3进入时钟设置，按K1选择设置的时分秒日月，按K2选择
*选择设置加1。 
*	注意					 ：
*******************************************************************************/

#include<reg52.h>
#include"lcd.h"
#include"ds1302.h"
#include"globalvar.h"
#include"key.h"
#include"51it.h"
#include"temp.h"

/*******************************************************************************
* 函数名         : main
* 函数功能		   : 主函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/



void main()
{
	LcdInit();    	//显示屏初始化
	Ds1302Init();   //时钟芯片初始化
	Global_Init();
	while(1)
	{	
		KEY_Press();		
		LcdDisplay();
		Alarm_Ring();	
		
	}	
}


