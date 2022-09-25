#include"Feiyun.h"
uchar code Key[]={1,2,3,10,4,5,6,11,7,8,9,14,0,12,13,15};
uchar code check[]={0xe7,0xd7,0xb7,0x77,0xeb,0xdb,0xbb,0x7b,
					0xed,0xdd,0xbd,0x7d,0xee,0xde,0xbe,0x7e};
uchar code num[]="0123456789UDLREQ";

uchar scankey(void)           //扫描函数
{
	uchar readkey,key,i;
	uchar x_key,y_key;        //X为行，Y为竖
	uchar dat;
scan:P1=0xf0;
	delay(20);         //去抖
	if(P1!=0xf0)       //确认有键按下
	{
		y_key=P1;        //读Y键值
		P1=0x0f;
		while(P1==0x0f);  
			x_key=P1;        //读X键值
		while(P1!=0x0f);       //是否释放键
		    readkey=y_key|x_key;   //读取键值特征码;
	}
	else goto scan;         //重新扫描
	for(i=0;i<16;i++)
	if(readkey==check[i]) key=i;
	key=Key[key];
	if(key<16&&key>=0) dat=key;
	else scankey();
	delay(20);
	while(KeyDown);
    return dat;
}
uchar ReadKey(KEY *dat)
{
    char temp,buf;
	if(KeyDown) 
	{
	    temp=1;
		buf=scankey();
		if(buf!=dat->c_key||dat->iscg==0)
		{
			dat->iscg=1;
			dat->l_key=dat->c_key;
			dat->c_key=buf;	
		}
	}
	else
	{
		temp=0;
		dat->iscg=0;
	}
	return temp;
}