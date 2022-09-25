#include "Feiyun.h" 
uint temp=270;       
void delay_us(uint t)	 ////��ʱ����
{
  for(;t>0;t--);
}    
void reset(void)	         ////DS18B20��λ���� 
{
  uchar state=1;
  while(state)
   {
    while(state)
     {
       DQ=1;
	   _nop_();_nop_();
       DQ=0;
       delay_us(50);
       DQ=1;
       delay_us(6);
       state=DQ;
     }
    delay_us(45);
    state=~DQ;
   }
  DQ=1;
}
void write_byte(uchar val)	//дһ���ֽ� 
{
   uchar i;
   for(i=8;i>0;i--)
   {
       DQ=1;_nop_();_nop_();
       DQ=0;_nop_();_nop_();_nop_();_nop_();_nop_();
       DQ=val&0x01;
       delay_us(6);
       val=val/2;
   }
   DQ=1;
   _nop_();
}			  
uchar read_byte(void)    ///////��һ���ֽ�
{
    uchar i;
	uchar value=0;
	for(i=8;i>0;i--)
    {
    	DQ=1;_nop_();_nop_();
    	value>>=1;
    	DQ=0;
    	_nop_();_nop_();_nop_();_nop_();
    	DQ=1;_nop_();_nop_();_nop_();_nop_();
    	if(DQ)value|=0x80;
    	delay_us(6);
    }
	DQ=1;
	return(value);
}
void gettemp()
{
    uchar a,b;
	uint t;		 
	reset();
	write_byte(0xcc);
	write_byte(0xbe);
	a=read_byte();	   //��ȡ���ֽ�
	b=read_byte();	   //��ȡ���ֽ�
	reset();
	write_byte(0xcc);
	write_byte(0x44);
	//�����ȡ�¶�t  
    t=b;
	t<<=8;           //ֵ����8λ   
	t=t|a;           //�ϲ��ߵ�λ��ֵ
	if(t>0xfff)		 //�ж��¶���Ϊ������Ϊ��
 	  t=~t+1;      //��ֵ����
 	t=t*(0.625);    //�¶�����10��,��ȷ��1λС��
	if((temp-t)<100||(t-temp)<100)
	temp=t;
}
void TempShow()	 ///�¶ȶ�ȡ����
{			  
	char buf[4];
	gettemp();
    buf[0]=temp%1000/100+0x30;  //ʮλ��
    buf[1]=temp%100/10+0x30;    //��λ��
	buf[2]='.';
    buf[3]=temp%10+0x30;        //С��λ
	pd(0x40);
 	write_data(buf[0]);
	write_data(buf[1]);
	write_data(buf[2]);
	write_data(buf[3]);
	write_data(du);
	write_data('C');
	LcdStr(0x00,"The Temperature:");	
		
}
