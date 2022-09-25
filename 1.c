#include<reg51.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define uint unsigned int
#define ulong unsigned long
#define uchar unsigned char
  
sbit E = P2^7;

void check_state();
void delay_us(uchar d_us);
void disp(char *hour,char *min,char *sec,char *ms,char *temper);
void write_com(uchar w_command);
void write_data(uchar w_data);
uchar read_data();
void init_all();
void write_str( uchar *str, uchar row, uchar col );
void set_time();
void convt(char *stri,uint time,uint flag);
void timer0() interrupt 1{
  TH0=0x3c;
  TL0=0xba;
//  write_str("false",0,0);
  set_time();
}

char xdata hour[3];
char xdata min[3];
char xdata sec[3];
char xdata ms[3];
uint xdata time[4]={0};
main(){
  init_all();  
  while(1);
  return 0;
}

void check_state(){
  RD=0;
  WR=1;
  P0=0xFF;
  do{
    E=0;
    E=1;
  }while(P0&0x80);
  E=0;
}
void convt(char *stri,int time,uint flag){
  if(flag){
    sprintf(stri,"%03d", time);
  }else{
    sprintf(stri, "%02d", time);
  }
}
void set_time(){
  if(time[3]>949){
    time[3]=0;
    if(time[2]>58){
      time[2]=0;
      if(time[1]>58){
        time[1]=0;
        time[0]=time[0]+1;
        if(time[0]==24)
          time[0]=0;
      }else{
        time[1]=time[1]+1;
      }
    }else{
      time[2]=time[2]+1;
    }
  }else{
    time[3]=time[3]+50;
  }
  convt(hour,time[0],0);
  convt(min,time[1],0);
  convt(sec,time[2],0);
  convt(ms,time[3],1);
  disp(hour,min,sec,ms,0);
}
void disp(char *o_hour,char *o_min,char *o_sec,char *o_ms,char *o_temper){
  uchar xdata time_o[16];
  time_o[0] = ' ';
  time_o[1] = ' ';
  time_o[2] = o_hour[0];
  time_o[3] = o_hour[1];
  time_o[4] = ':';
  time_o[5] = o_min[0];
  time_o[6] = o_min[1];
  time_o[7] = ':';
  time_o[8] = o_sec[0];
  time_o[9] = o_sec[1];
  time_o[10] = ':';
  time_o[11] = o_ms[0];
  time_o[12] = '0';
  time_o[13] = '0';
  time_o[14] = '\0'; 
  write_str(time_o,0,0);
//  write_str("false",0,0);
}


void write_com(uchar w_command){
  check_state();
  RD=0;
  WR=0;
  P0=w_command;
  E=1;
  E=0;
}
void write_data(uchar w_data){
  check_state();
  RD=1;
  WR=0;
  P0=w_data;
  E=1;
  E=0;
}
uchar read_data(){
  uchar res=0;
  P0=0xFF;
  RD=1;
  WR=1;
  E=0;
  E=1;
  delay_us(40);
  res=P0;
  E=0;
  return res;
}
void init_all(){
//  unsigned char xdata time[16]="dasfbdsaf";
  write_com( 0x38 );
  write_com( 0x0C );  
  write_com( 0x06 );  
  write_com( 0x01 );                
  TMOD=0x01;  
  TH0=0x3c;
  TL0=0xba;  
  EA = 1;
  ET0 = 1;
  TR0=1; 
  write_str("test\0",0,0);
}
void delay_us(uchar d_us){
  uint i;
  for(i=0;i<d_us;i++);
}
void write_str(unsigned char *str, unsigned char row, unsigned char col ){
  unsigned char addr = 0x00;      
  if (row){
    addr = 0xc0;
  }else{
    addr = 0x80;                                           
  }   
  addr += col;
  while ( *str != '\0' ){
    write_com( addr );
    write_data( *str );  
    addr++;        
    str++;
  }
}