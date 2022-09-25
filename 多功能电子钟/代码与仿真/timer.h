#ifndef _timer_h                    //条件编译，编译过就不再向下编译
#define _timer_h
typedef struct
{
    int  count;
	char iscg;
}TIMER;
extern TIMER timer;
void  TimerInit(void);
#endif