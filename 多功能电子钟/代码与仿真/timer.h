#ifndef _timer_h                    //�������룬������Ͳ������±���
#define _timer_h
typedef struct
{
    int  count;
	char iscg;
}TIMER;
extern TIMER timer;
void  TimerInit(void);
#endif