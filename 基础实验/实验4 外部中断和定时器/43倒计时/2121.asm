		ORG 0000H
		SJMP MAIN
		ORG 000BH				;T0中断
		LJMP T0INT
		ORG 001BH
		LJMP T0INT1				;T1中断
		
		ORG 0040H		
MAIN:   MOV  	TMOD,#01H		;工作方式1
    	MOV  	R0,#6			;十位初始值
		MOV  	R1,#1			;个位初始值

LOOP:	DEC		R1				;个位秒数减一
		MOV 	R2,#20			;设置20个50ms循环
		MOV  	TH0,#3CH		;定时初始状态
		MOV  	TL0,#0B0H
		SETB 	TR0				
		SETB 	EA				;中断初始化
		SETB 	ET0

		;动态数码管显示
DISDLAY:MOV 	A,R1			;个位显示
		MOV 	DPTR,#TABLE 
		MOVC 	A,@A+DPTR 
		MOV 	P0,A
		MOV 	P1,#7FH 
		LCALL  	DELAY1ms		;延迟显示		
		
    	MOV 	A,R0			;十位显示
		MOV 	DPTR,#TABLE 
		MOVC 	A,@A+DPTR 
		MOV 	P0,A
		MOV 	P1,#0BFH
		LCALL  	DELAY1ms		;延迟显示			
		
		CJNE	R2,#0,DISDLAY	;判断50ms是否完成
		CJNE	R1,#0,LOOP		;判断个位是否为零，不为零跳转
		CJNE	R0,#0,GOON		;判断十位是否为零，不为零跳转
		MOV 	P0,#0			;置零，停止
		SJMP	$
		
GOON:	MOV  	R1,#0AH			;设置个位类初始状态
		DEC		R0				;十位减一
		SJMP    LOOP			;继续循环
			
TABLE: DB 3FH,06H,5BH,4FH,66H,6DH,7DH,07H,7FH,6FH

DELAY1ms:	MOV  	R3,#1		;延时1ms
			SETB 	ET1			;设置T1初始状态
			MOV  	TH1,#0FCH
			MOV  	TL1,#18H
			SETB 	TR1
			CJNE    R3,#0,$		;踏步等待计时完成
			RET

T0INT: 	MOV  TL0,#0B0H			;T0中断
		MOV  TH0,#3CH
		DEC  R2
		RETI
		
T0INT1: MOV  TL1,#18H			;T1中断
		MOV  TH1,#0FCH
		DEC  R3
		RETI
		END
