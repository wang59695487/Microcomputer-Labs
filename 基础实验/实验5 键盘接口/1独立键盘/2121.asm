		ORG	0000H			
MAIN:	MOV		P1,#0FFH		;P1准备输入
		MOV		A,P1			;查询有无按键
		CJNE	A,#0FFH,IFKEY	;无按键重新查询
		SJMP   	MAIN
		
IFKEY:	LCALL	DELAY10ms       ;去前沿抖动
		MOV		R3,#00H         ;设置按键初值
		MOV		A,P1			;读入键值
		XRL		A,#0FFH			;将A取反
		CJNE	A,#0H,SCAN  	;无按键跳转
		MOV		A,#0FFH			;将A全置1
		SJMP	NOKEY	        
SCAN:	MOV		R2,#8	        ;循环8次
SCAN1:	RRC		A				;循环右移
		JC		WAIT         	;判断A中为1的位是否移出
		INC		R3				;键值加1
		DJNZ	R2,SCAN1
		MOV		A,#0FFH	        ;将A全置1
        SJMP	NOKEY				  
WAIT:	MOV		A,P1			;输出到P1
		CJNE	A,#0FFH,WAIT    ;等待按键抬起
		LCALL	DELAY10ms       ;去后沿抖动
NOKEY:	MOV 	A,R3			;静态数码管显示数值
		INC		A				;由0-7变为1-8
		MOV 	B,A				;保存到B
		MOV 	DPTR,#TABLE 
		MOVC 	A,@A+DPTR 
		MOV 	P0,A
		SJMP	MAIN	
		
TABLE:  DB 0C0H,0F9H,0A4H,0B0H,99H,92H,82H,0F8H,80H,90H
	
DELAY10ms:MOV 	R6,#20			;延时10ms
DELOOP2:MOV 	R7,#250			;2μs*250*20
DELOOP1:DJNZ 	R7,DELOOP1
		DJNZ 	R6,DELOOP2
		RET
		END