#include"globalvar.h"

//---DS1302ʱ�ӳ�ʼ��2013��1��1�����ڶ�12��00��00�롣---//
//---�洢˳�����롢�֡�ʱ���ա��¡����ڡ���,�洢��ʽ����BCD��---//
uchar TIME[7] = {0, 0, 0x08, 0x08, 0x01, 0x03, 0x20};  //BCD�루ʮ���ƣ�
uchar ALARM[7] = {0, 1, 0x08, 0x08, 0x01, 0x03, 0x20};  //BCD�루ʮ���ƣ�
uchar Tmep_Data[9];  //�¶�����


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
//1Ϊ������ʾģʽ��2Ϊ�¶�ʪ����ʾģʽ��3Ϊ������ʾģʽ
char LCD_MODE;
char Alarm_Open;




void Global_Init(void)
{
	key=0;//û������
	SetState=0;//��ʾ״̬
	SetPlace=0;//���õ�Ϊ0
	Alarm_SetState=0;//��ʾ״̬
	Alarm_SetPlace=0;//���õ�Ϊ0	
	LCD_MODE=1;//��ʾʱ��
	Alarm_Open=0;//��������
}