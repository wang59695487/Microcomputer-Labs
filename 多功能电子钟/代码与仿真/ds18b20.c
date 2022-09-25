#include "Feiyun.h" 
uint temp=270;       
void delay_us(uint t)	 ////延时函数
{
  for(;t>0;t--);
}    
void reset(void)	         ////DS18B20复位函数 
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
void write_byte(uchar val)	//写一个字节 
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
uchar read_byte(void)    ///////读一个字节
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
	a=read_byte();	   //读取高字节
	b=read_byte();	   //读取低字节
	reset();
	write_byte(0xcc);
	write_byte(0x44);
	//处理读取温度t  
    t=b;
	t<<=8;           //值左移8位   
	t=t|a;           //合并高低位数值
	if(t>0xfff)		 //判断温度是为正还是为负
 	  t=~t+1;      //负值换算
 	t=t*(0.625);    //温度扩大10倍,精确到1位小数
	if((temp-t)<100||(t-temp)<100)
	temp=t;
}
void TempShow()	 ///温度读取函数
{			  
	char buf[4];
	gettemp();
    buf[0]=temp%1000/100+0x30;  //十位数
    buf[1]=temp%100/10+0x30;    //个位数
	buf[2]='.';
    buf[3]=temp%10+0x30;        //小数位
	pd(0x40);
 	write_data(buf[0]);
	write_data(buf[1]);
	write_data(buf[2]);
	write_data(buf[3]);
	write_data(du);
	write_data('C');
	LcdStr(0x00,"The Temperature:");	
		
}
