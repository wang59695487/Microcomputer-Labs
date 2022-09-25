#include "Feiyun.h"
void delay(uint z)         ///延时函数,大约是一毫秒/z
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);	  
}