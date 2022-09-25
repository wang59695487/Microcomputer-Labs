#include"lcd.h"
#include"ds1302.h"
#include"temp.h"
#include"51it.h"

/*******************************************************************************
* �� �� ��         : LcdWriteCom
* ��������		   : ��LCDд��һ���ֽڵ�����
* ��    ��         : com
* ��    ��         : ��
*******************************************************************************/
#ifndef 	LCD1602_4PINS	 //��û�ж������LCD1602_4PINSʱ
void LcdWriteCom(uchar com)	  //д������
{
	LCD1602_E = 0;     //ʹ��
	LCD1602_RS = 0;	   //ѡ��������
	LCD1602_RW = 0;	   //ѡ��д��
	
	LCD1602_DATAPINS = com;     //��������
	Delay_ms(1);		//�ȴ������ȶ�

	LCD1602_E = 1;	          //д��ʱ��
	Delay_ms(5);	  //����ʱ��
	LCD1602_E = 0;
}
#else 
void LcdWriteCom(uchar com)	  //д������
{
	LCD1602_E = 0;	 //ʹ������
	LCD1602_RS = 0;	 //ѡ��д������
	LCD1602_RW = 0;	 //ѡ��д��

	LCD1602_DATAPINS = com;	//����4λ�Ľ����ǽӵ�P0�ڵĸ���λ�����Դ��͸���λ���ø�
	Delay_ms(1);

	LCD1602_E = 1;	 //д��ʱ��
	Delay_ms(5);
	LCD1602_E = 0;

//	Lcd1602_Delay1ms(1);
	LCD1602_DATAPINS = com << 4; //���͵���λ
	Delay_ms(1);

	LCD1602_E = 1;	 //д��ʱ��
	Delay_ms(5);
	LCD1602_E = 0;
}
#endif
/*******************************************************************************
* �� �� ��         : LcdWriteData
* ��������		   : ��LCDд��һ���ֽڵ�����
* ��    ��         : dat
* ��    ��         : ��
*******************************************************************************/		   
#ifndef 	LCD1602_4PINS		   
void LcdWriteData(uchar dat)			//д������
{
	LCD1602_E = 0;	//ʹ������
	LCD1602_RS = 1;	//ѡ����������
	LCD1602_RW = 0;	//ѡ��д��

	LCD1602_DATAPINS = dat; //д������
	Delay_ms(1);

	LCD1602_E = 1;   //д��ʱ��
	Delay_ms(5);   //����ʱ��
	LCD1602_E = 0;
}
#else
void LcdWriteData(uchar dat)			//д������
{
	LCD1602_E = 0;	  //ʹ������
	LCD1602_RS = 1;	  //ѡ��д������
	LCD1602_RW = 0;	  //ѡ��д��

	LCD1602_DATAPINS = dat;	//����4λ�Ľ����ǽӵ�P0�ڵĸ���λ�����Դ��͸���λ���ø�
	Delay_ms(1);

	LCD1602_E = 1;	  //д��ʱ��
	Delay_ms(5);
	LCD1602_E = 0;

	LCD1602_DATAPINS = dat << 4; //д�����λ
	Delay_ms(1);

	LCD1602_E = 1;	  //д��ʱ��
	Delay_ms(5);
	LCD1602_E = 0;
}
#endif
/*******************************************************************************
* �� �� ��       : LcdInit()
* ��������		 : ��ʼ��LCD��
* ��    ��       : ��
* ��    ��       : ��
*******************************************************************************/		   
#ifndef		LCD1602_4PINS
void LcdInit()						  //LCD��ʼ���ӳ���
{
	u8 i;
	uchar String[] = {"Welcome!"};
 	LcdWriteCom(0x38);  //����ʾ
	LcdWriteCom(0x0c);  //����ʾ����ʾ���
	LcdWriteCom(0x06);  //дһ��ָ���1
	LcdWriteCom(0x01);  //����
	LcdWriteCom(0x84);  //��������ָ�����
	
	for(i=0;i<8;i++)
	{
		LcdWriteData(String[i]);	
	}
	Delay_ms(2000);
	LcdWriteCom(0x01);  //����
	
	
	
}
#else
void LcdInit()						  //LCD��ʼ���ӳ���
{
	LcdWriteCom(0x32);	 //��8λ����תΪ4λ����
	LcdWriteCom(0x28);	 //����λ���µĳ�ʼ��
	LcdWriteCom(0x0c);  //����ʾ����ʾ���
	LcdWriteCom(0x06);  //дһ��ָ���1
	LcdWriteCom(0x01);  //����
	LcdWriteCom(0x80);  //��������ָ�����
}
#endif


/*******************************************************************************
* ������         : Lcd_TimeDisplay()
* ��������		   : ��ʾʱ�亯��
* ����           : ��
* ���         	 : ��
*******************************************************************************/

void Lcd_TimeDisplay()
{
	u8 Week,i;
	LcdWriteCom(0x80+0X40);
	LcdWriteData('0'+TIME[2]/16);				//ʱ
	LcdWriteData('0'+(TIME[2]&0x0f));				 
	LcdWriteData(':');
	LcdWriteData('0'+TIME[1]/16);				//��
	LcdWriteData('0'+(TIME[1]&0x0f));	
	LcdWriteData(':');
	LcdWriteData('0'+TIME[0]/16);				//��
	LcdWriteData('0'+(TIME[0]&0x0f));

	LcdWriteCom(0x80);
	LcdWriteData('2');
	LcdWriteData('0');
	LcdWriteData('0'+TIME[6]/16);			//��
	LcdWriteData('0'+(TIME[6]&0x0f));
	LcdWriteData('-');
	LcdWriteData('0'+TIME[4]/16);			//��
	LcdWriteData('0'+(TIME[4]&0x0f));
	LcdWriteData('-');
	LcdWriteData('0'+TIME[3]/16);			//��
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
			break;//��ʾ���λ
		}
		case(2):
		{
			for(i=0;i<5;i++)
			{
				LcdWriteData(Tuesday[i]);	
			}
			break;//��ʾ���λ
		}
		case(3):
		{
			for(i=0;i<5;i++)
			{
				LcdWriteData(Wednesday[i]);	
			}
			break;//��ʾ���λ
		}
		case(4):
		{
			for(i=0;i<5;i++)
			{
				LcdWriteData(Thursday[i]);	
			}
			break;//��ʾ���λ
		}
		case(5):
		{
			for(i=0;i<5;i++)
			{
				LcdWriteData(Friday[i]);	
			}
			break;//��ʾ���λ
		}
		case(6):
		{
			for(i=0;i<5;i++)
			{
				LcdWriteData(Saturday[i]);	
			}
			break;//��ʾ���λ
		}
		case(7):
		{
			for(i=0;i<5;i++)
			{
				LcdWriteData(Sunday[i]);	
			}
			break;//��ʾ���λ
		}
	
	}
	LcdWriteCom(0x8E+0X40);
	if(Alarm_SetState)
	LcdWriteData('O');
	else
	LcdWriteData('C');	
}

/*******************************************************************************
* ������         : Lcd_AlarmDisplay()
* ��������		   : ��ʾ����ʱ�亯��
* ����           : ��
* ���         	 : ��
*******************************************************************************/
void Lcd_AlarmDisplay(void)
{
	u8 Week,i;
	LcdWriteCom(0x80+0X40);
	LcdWriteData('0'+ALARM[2]/16);				//ʱ
	LcdWriteData('0'+(ALARM[2]&0x0f));				 
	LcdWriteData(':');
	LcdWriteData('0'+ALARM[1]/16);				//��
	LcdWriteData('0'+(ALARM[1]&0x0f));	
	LcdWriteData(':');
	LcdWriteData('0'+ALARM[0]/16);				//��
	LcdWriteData('0'+(ALARM[0]&0x0f));

	LcdWriteCom(0x80);
	LcdWriteData('2');
	LcdWriteData('0');
	LcdWriteData('0'+ALARM[6]/16);			//��
	LcdWriteData('0'+(ALARM[6]&0x0f));
	LcdWriteData('-');
	LcdWriteData('0'+ALARM[4]/16);			//��
	LcdWriteData('0'+(ALARM[4]&0x0f));
	LcdWriteData('-');
	LcdWriteData('0'+ALARM[3]/16);			//��
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
			break;//��ʾ���λ
		}
		case(2):
		{
			for(i=0;i<5;i++)
			{
				LcdWriteData(Tuesday[i]);	
			}
			break;//��ʾ���λ
		}
		case(3):
		{
			for(i=0;i<5;i++)
			{
				LcdWriteData(Wednesday[i]);	
			}
			break;//��ʾ���λ
		}
		case(4):
		{
			for(i=0;i<5;i++)
			{
				LcdWriteData(Thursday[i]);	
			}
			break;//��ʾ���λ
		}
		case(5):
		{
			for(i=0;i<5;i++)
			{
				LcdWriteData(Friday[i]);	
			}
			break;//��ʾ���λ
		}
		case(6):
		{
			for(i=0;i<5;i++)
			{
				LcdWriteData(Saturday[i]);	
			}
			break;//��ʾ���λ
		}
		case(7):
		{
			for(i=0;i<5;i++)
			{
				LcdWriteData(Sunday[i]);	
			}
			break;//��ʾ���λ
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
* ������         : Lcd_TempDisplay()
* ��������		   : ��ʾ�¶ȶ�ȡ����
* ����           : temp
* ���         	 : ��
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
	   	 
	if(temp< 0)				//���¶�ֵΪ����
  	{
		Tmep_Data[0]=0xb0;	 	  //   -
		//��Ϊ��ȡ���¶���ʵ���¶ȵĲ��룬���Լ�1����ȡ�����ԭ��
		temp=temp-1;
		temp=~temp;
		tp=temp;
		temp=tp*0.0625*100+0.5;	
		//������С�����*100��+0.5���������룬��ΪC���Ը�����ת��Ϊ���͵�ʱ���С����
		//��������Զ�ȥ���������Ƿ����0.5����+0.5֮�����0.5�ľ��ǽ�1�ˣ�С��0.5�ľ�
		//�����0.5��������С������档
 
  	}
 	else
  	{			
		Tmep_Data[0]=0x2b;	 	  //   +
		tp=temp;//��Ϊ���ݴ�����С�������Խ��¶ȸ���һ�������ͱ���
		//����¶���������ô����ô������ԭ����ǲ���������
		temp=tp*0.0625*100+0.5;	
		//������С�����*100��+0.5���������룬��ΪC���Ը�����ת��Ϊ���͵�ʱ���С����
		//��������Զ�ȥ���������Ƿ����0.5����+0.5֮�����0.5�ľ��ǽ�1�ˣ�С��0.5�ľ�
		//�����0.5��������С������档
	}
//	value=temp / 10000;
	Tmep_Data[1] = (temp / 10000)        | 0x30;
	Tmep_Data[2] = (temp % 10000 / 1000) | 0x30;
	Tmep_Data[3] = (temp % 1000 / 100)   | 0x30;
	Tmep_Data[5] = (temp % 100 / 10)     | 0x30;
	Tmep_Data[6] = (temp % 10)           | 0x30;
	
	Tmep_Data[4] = 0x2e;  //0010 1110  .
	Tmep_Data[7] = 0xdf ; //   1101  1111  ��
	Tmep_Data[8] = 0x43;// 0100  0011  C
	
	

	for(i=0;i<9;i++)
	{
		LcdWriteData(Tmep_Data[i]);	
	}	

}

/*******************************************************************************
* ������         : LcdDisplay()
* ��������		   : ��ʾ����
* ����           : temp
* ���         	 : ��
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