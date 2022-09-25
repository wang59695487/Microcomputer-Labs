#ifndef _key_h                    //条件编译，编译过就不再向下编译
#define _key_h
typedef struct
{
    char c_key;
	char l_key;
	char iscg;
}KEY;
#define	KeyUp  (P1==(P1=0x0f))
#define	KeyDown  !KeyUp
uchar scankey(void);			 //扫描函数
uchar ReadKey(KEY *dat);           
#endif
