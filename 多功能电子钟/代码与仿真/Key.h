#ifndef _key_h                    //�������룬������Ͳ������±���
#define _key_h
typedef struct
{
    char c_key;
	char l_key;
	char iscg;
}KEY;
#define	KeyUp  (P1==(P1=0x0f))
#define	KeyDown  !KeyUp
uchar scankey(void);			 //ɨ�躯��
uchar ReadKey(KEY *dat);           
#endif
