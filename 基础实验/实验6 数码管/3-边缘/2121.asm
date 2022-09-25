		ORG 0000H
		SJMP MAIN
		ORG 000BH				;T0中断
		LJMP T0INT
		
		ORG 0040H		
MAIN:   MOV  	TMOD,#01H		;工作方式1
		MOV		R0,#0
LOOP:	MOV 	R5,#3			;设置3个50ms循环
		MOV  	TH0,#3CH		;定时初始状态
		MOV  	TL0,#0B0H
		SETB 	TR0				
		SETB 	EA				;中断初始化
		SETB 	ET0

		;动态数码管显示	
DISDLAY:MOV 	A,R0			;取出循环次数
		MOV 	DPTR,#DUAN		;取出段码
		MOVC 	A,@A+DPTR 		
		MOV 	P0,A		
		MOV 	A,R0			;取出循环次数
		MOV 	DPTR,#WEI 		;取出位码
		MOVC 	A,@A+DPTR 
		MOV 	P1,A
		CJNE	R5,#0,DISDLAY	;判断50ms是否完成
		MOV 	R5,#3			;设置3个50ms循环
		INC		R0				
		CJNE	R0,#20,DISDLAY	;继续循环
		SJMP	MAIN
			
DUAN:	DB 08H,10H,20H,01H 			;第1个数码管4个段的段码，共20个
		DB 01H,01H,01H,01H,01H,01H 	;第2-7个数码管的a段段码
		DB 01H,02H,04H,08H 		;第8个数码管4个段的段码
		DB 08H,08H,08H,08H,08H,08H 	;第7-2个数码管的d段段码
WEI:	DB 0FEH,0FEH,0FEH,0FEH 		;第1个数码管的位码
		DB 0FDH,0FBH,0F7H,0EFH,0DFH,0BFH 	;第2-7个数码管的位码
		DB 7FH,7FH,7FH,7FH 			;第8个数码管的位码
		DB 0BFH,0DFH,0EFH,0F7H,0FBH,0FDH 	;第7-2个数码管的位码

T0INT: 	MOV  TL0,#0B0H			;T0中断
		MOV  TH0,#3CH
		DEC  R5
		RETI
		END
