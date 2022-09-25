#include"globalvar.h"

//---DS1302时钟初始化2013年1月1日星期二12点00分00秒。---//
//---存储顺序是秒、分、时、日、月、星期、年,存储格式是用BCD码---//
uchar TIME[7] = {0, 0, 0x08, 0x08, 0x01, 0x03, 0x20};  //BCD码（十进制）
uchar ALARM[7] = {0, 1, 0x08, 0x08, 0x01, 0x03, 0x20};  //BCD码（十进制）
uchar Tmep_Data[9];  //温度数据


uchar SetState,SetPlace;
uchar Alarm_SetState,Alarm_SetPlace;


uchar Monday[] = {" Mon."};  
uchar Tuesday[] = {"Tues."}; 
uchar Wednesday[] = {" Wed."}; 
uchar Thursday[] = {"Thur."}; 
uchar Friday[] = {" Fri."}; 
uchar Saturday[] = {" Sat."}; 
uchar Sunday[] = {" Sun."}; 



uchar LCD_Temp[] = {"Temp:"}; 
uchar LCD_Alarm[] = {"A"}; 

char key;
//1为正常显示模式，2为温度湿度显示模式，3为闹钟显示模式
char LCD_MODE;
char Alarm_Open;




void Global_Init(void)
{
	key=0;//没按按键
	SetState=0;//显示状态
	SetPlace=0;//设置点为0
	Alarm_SetState=0;//显示状态
	Alarm_SetPlace=0;//设置点为0	
	LCD_MODE=1;//显示时间
	Alarm_Open=0;//不开闹钟
}