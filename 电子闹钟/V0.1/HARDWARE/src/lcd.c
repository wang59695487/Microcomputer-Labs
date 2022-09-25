#include"lcd.h"
#include"ds1302.h"
#include"temp.h"
#include"51it.h"

/*******************************************************************************
* 函 数 名         : LcdWriteCom
* 函数功能		   : 向LCD写入一个字节的命令
* 输    入         : com
* 输    出         : 无
*******************************************************************************/
#ifndef 	LCD1602_4PINS	 //当没有定义这个LCD1602_4PINS时
void LcdWriteCom(uchar com)	  //写入命令
{
	LCD1602_E = 0;     //使能
	LCD1602_RS = 0;	   //选择发送命令
	LCD1602_RW = 0;	   //选择写入
	
	LCD1602_DATAPINS = com;     //放入命令
	Delay_ms(1);		//等待数据稳定

	LCD1602_E = 1;	          //写入时序
	Delay_ms(5);	  //保持时间
	LCD1602_E = 0;
}
#else 
void LcdWriteCom(uchar com)	  //写入命令
{
	LCD1602_E = 0;	 //使能清零
	LCD1602_RS = 0;	 //选择写入命令
	LCD1602_RW = 0;	 //选择写入

	LCD1602_DATAPINS = com;	//由于4位的接线是接到P0口的高四位，所以传送高四位不用改
	Delay_ms(1);

	LCD1602_E = 1;	 //写入时序
	Delay_ms(5);
	LCD1602_E = 0;

//	Lcd1602_Delay1ms(1);
	LCD1602_DATAPINS = com << 4; //发送低四位
	Delay_ms(1);

	LCD1602_E = 1;	 //写入时序
	Delay_ms(5);
	LCD1602_E = 0;
}
#endif
/*******************************************************************************
* 函 数 名         : LcdWriteData
* 函数功能		   : 向LCD写入一个字节的数据
* 输    入         : dat
* 输    出         : 无
*******************************************************************************/		   
#ifndef 	LCD1602_4PINS		   
void LcdWriteData(uchar dat)			//写入数据
{
	LCD1602_E = 0;	//使能清零
	LCD1602_RS = 1;	//选择输入数据
	LCD1602_RW = 0;	//选择写入

	LCD1602_DATAPINS = dat; //写入数据
	Delay_ms(1);

	LCD1602_E = 1;   //写入时序
	Delay_ms(5);   //保持时间
	LCD1602_E = 0;
}
#else
void LcdWriteData(uchar dat)			//写入数据
{
	LCD1602_E = 0;	  //使能清零
	LCD1602_RS = 1;	  //选择写入数据
	LCD1602_RW = 0;	  //选择写入

	LCD1602_DATAPINS = dat;	//由于4位的接线是接到P0口的高四位，所以传送高四位不用改
	Delay_ms(1);

	LCD1602_E = 1;	  //写入时序
	Delay_ms(5);
	LCD1602_E = 0;

	LCD1602_DATAPINS = dat << 4; //写入低四位
	Delay_ms(1);

	LCD1602_E = 1;	  //写入时序
	Delay_ms(5);
	LCD1602_E = 0;
}
#endif
/*******************************************************************************
* 函 数 名       : LcdInit()
* 函数功能		 : 初始化LCD屏
* 输    入       : 无
* 输    出       : 无
*******************************************************************************/		   
#ifndef		LCD1602_4PINS
void LcdInit()						  //LCD初始化子程序
{
	u8 i;
	uchar String[] = {"Welcome!"};
 	LcdWriteCom(0x38);  //开显示
	LcdWriteCom(0x0c);  //开显示不显示光标
	LcdWriteCom(0x06);  //写一个指针加1
	LcdWriteCom(0x01);  //清屏
	LcdWriteCom(0x84);  //设置数据指针起点
	
	for(i=0;i<8;i++)
	{
		LcdWriteData(String[i]);	
	}
	Delay_ms(2000);
	LcdWriteCom(0x01);  //清屏
	
	
	
}
#else
void LcdInit()						  //LCD初始化子程序
{
	LcdWriteCom(0x32);	 //将8位总线转为4位总线
	LcdWriteCom(0x28);	 //在四位线下的初始化
	LcdWriteCom(0x0c);  //开显示不显示光标
	LcdWriteCom(0x06);  //写一个指针加1
	LcdWriteCom(0x01);  //清屏
	LcdWriteCom(0x80);  //设置数据指针起点
}
#endif


/*******************************************************************************
* 函数名         : Lcd_TimeDisplay()
* 函数功能		   : 显示时间函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

void Lcd_TimeDisplay()
{
	u8 Week,i;
	LcdWriteCom(0x80+0X40);
	LcdWriteData('0'+TIME[2]/16);				//时
	LcdWriteData('0'+(TIME[2]&0x0f));				 
	LcdWriteData(':');
	LcdWriteData('0'+TIME[1]/16);				//分
	LcdWriteData('0'+(TIME[1]&0x0f));	
	LcdWriteData(':');
	LcdWriteData('0'+TIME[0]/16);				//秒
	LcdWriteData('0'+(TIME[0]&0x0f));

	LcdWriteCom(0x80);
	LcdWriteData('2');
	LcdWriteData('0');
	LcdWriteData('0'+TIME[6]/16);			//年
	LcdWriteData('0'+(TIME[6]&0x0f));
	LcdWriteData('-');
	LcdWriteData('0'+TIME[4]/16);			//月
	LcdWriteData('0'+(TIME[4]&0x0f));
	LcdWriteData('-');
	LcdWriteData('0'+TIME[3]/16);			//日
	LcdWriteData('0'+(TIME[3]&0x0f));
	LcdWriteCom(0x8B);
	Week=TIME[5]&0x07;
	switch(Week)
	{
		case(1):
		{
			for(i=0;i<5;i++)
			{
				LcdWriteData(Monday[i]);	
			}
			break;//显示秒个位
		}
		case(2):
		{
			for(i=0;i<5;i++)
			{
				LcdWriteData(Tuesday[i]);	
			}
			break;//显示秒个位
		}
		case(3):
		{
			for(i=0;i<5;i++)
			{
				LcdWriteData(Wednesday[i]);	
			}
			break;//显示秒个位
		}
		case(4):
		{
			for(i=0;i<5;i++)
			{
				LcdWriteData(Thursday[i]);	
			}
			break;//显示秒个位
		}
		case(5):
		{
			for(i=0;i<5;i++)
			{
				LcdWriteData(Friday[i]);	
			}
			break;//显示秒个位
		}
		case(6):
		{
			for(i=0;i<5;i++)
			{
				LcdWriteData(Saturday[i]);	
			}
			break;//显示秒个位
		}
		case(7):
		{
			for(i=0;i<5;i++)
			{
				LcdWriteData(Sunday[i]);	
			}
			break;//显示秒个位
		}
	
	}
	LcdWriteCom(0x8E+0X40);
	if(Alarm_SetState)
	LcdWriteData('O');
	else
	LcdWriteData('C');	
}

/*******************************************************************************
* 函数名         : Lcd_AlarmDisplay()
* 函数功能		   : 显示闹钟时间函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void Lcd_AlarmDisplay(void)
{
	u8 Week,i;
	LcdWriteCom(0x80+0X40);
	LcdWriteData('0'+ALARM[2]/16);				//时
	LcdWriteData('0'+(ALARM[2]&0x0f));				 
	LcdWriteData(':');
	LcdWriteData('0'+ALARM[1]/16);				//分
	LcdWriteData('0'+(ALARM[1]&0x0f));	
	LcdWriteData(':');
	LcdWriteData('0'+ALARM[0]/16);				//秒
	LcdWriteData('0'+(ALARM[0]&0x0f));

	LcdWriteCom(0x80);
	LcdWriteData('2');
	LcdWriteData('0');
	LcdWriteData('0'+ALARM[6]/16);			//年
	LcdWriteData('0'+(ALARM[6]&0x0f));
	LcdWriteData('-');
	LcdWriteData('0'+ALARM[4]/16);			//月
	LcdWriteData('0'+(ALARM[4]&0x0f));
	LcdWriteData('-');
	LcdWriteData('0'+ALARM[3]/16);			//日
	LcdWriteData('0'+(ALARM[3]&0x0f));
	LcdWriteCom(0x8B);
	Week=ALARM[5]&0x07;
	switch(Week)
	{
		case(1):
		{
			for(i=0;i<5;i++)
			{
				LcdWriteData(Monday[i]);	
			}
			break;//显示秒个位
		}
		case(2):
		{
			for(i=0;i<5;i++)
			{
				LcdWriteData(Tuesday[i]);	
			}
			break;//显示秒个位
		}
		case(3):
		{
			for(i=0;i<5;i++)
			{
				LcdWriteData(Wednesday[i]);	
			}
			break;//显示秒个位
		}
		case(4):
		{
			for(i=0;i<5;i++)
			{
				LcdWriteData(Thursday[i]);	
			}
			break;//显示秒个位
		}
		case(5):
		{
			for(i=0;i<5;i++)
			{
				LcdWriteData(Friday[i]);	
			}
			break;//显示秒个位
		}
		case(6):
		{
			for(i=0;i<5;i++)
			{
				LcdWriteData(Saturday[i]);	
			}
			break;//显示秒个位
		}
		case(7):
		{
			for(i=0;i<5;i++)
			{
				LcdWriteData(Sunday[i]);	
			}
			break;//显示秒个位
		}	
	}
	LcdWriteCom(0x8B+0X40);
	for(i=0;i<1;i++)
	{
		LcdWriteData(LCD_Alarm[i]);	
	}
	LcdWriteCom(0x8E+0X40);
	if(Alarm_SetState)
	LcdWriteData('O');
	else
	LcdWriteData('C');
}



/*******************************************************************************
* 函数名         : Lcd_TempDisplay()
* 函数功能		   : 显示温度读取函数
* 输入           : temp
* 输出         	 : 无
*******************************************************************************/
void Lcd_TempDisplay(int temp) 	 
{
	uchar i;
	float tp; 
	LcdWriteCom(0x80);
	for(i=0;i<5;i++)
	{
		LcdWriteData(LCD_Temp[i]);	
	}
	   	 
	if(temp< 0)				//当温度值为负数
  	{
		Tmep_Data[0]=0xb0;	 	  //   -
		//因为读取的温度是实际温度的补码，所以减1，再取反求出原码
		temp=temp-1;
		temp=~temp;
		tp=temp;
		temp=tp*0.0625*100+0.5;	
		//留两个小数点就*100，+0.5是四舍五入，因为C语言浮点数转换为整型的时候把小数点
		//后面的数自动去掉，不管是否大于0.5，而+0.5之后大于0.5的就是进1了，小于0.5的就
		//算加上0.5，还是在小数点后面。
 
  	}
 	else
  	{			
		Tmep_Data[0]=0x2b;	 	  //   +
		tp=temp;//因为数据处理有小数点所以将温度赋给一个浮点型变量
		//如果温度是正的那么，那么正数的原码就是补码它本身
		temp=tp*0.0625*100+0.5;	
		//留两个小数点就*100，+0.5是四舍五入，因为C语言浮点数转换为整型的时候把小数点
		//后面的数自动去掉，不管是否大于0.5，而+0.5之后大于0.5的就是进1了，小于0.5的就
		//算加上0.5，还是在小数点后面。
	}
//	value=temp / 10000;
	Tmep_Data[1] = (temp / 10000)        | 0x30;
	Tmep_Data[2] = (temp % 10000 / 1000) | 0x30;
	Tmep_Data[3] = (temp % 1000 / 100)   | 0x30;
	Tmep_Data[5] = (temp % 100 / 10)     | 0x30;
	Tmep_Data[6] = (temp % 10)           | 0x30;
	
	Tmep_Data[4] = 0x2e;  //0010 1110  .
	Tmep_Data[7] = 0xdf ; //   1101  1111  。
	Tmep_Data[8] = 0x43;// 0100  0011  C
	
	

	for(i=0;i<9;i++)
	{
		LcdWriteData(Tmep_Data[i]);	
	}	

}

/*******************************************************************************
* 函数名         : LcdDisplay()
* 函数功能		   : 显示函数
* 输入           : temp
* 输出         	 : 无
*******************************************************************************/
void LcdDisplay(void) 	 
{
	if(SetState==0)
	{
		Ds1302ReadTime();
	}
	switch(LCD_MODE)
	{
		case TIME_MODE: 
			 Lcd_TimeDisplay();
		break;
		
		case TEMP_MODE: 
			 Lcd_TempDisplay(Ds18b20ReadTemp());
		break;
		
		case ALARM_MODE: 
			 Lcd_AlarmDisplay();
		break;
	}
}