		ORG 	0000H
		SJMP 	MAIN
		
		ORG		0040H
MAIN: 	MOV 	R0,#30H 		;赋初值1-8
		MOV 	R1,#08H 
		MOV 	R2,#01H 
STORE:	MOV 	A,R2
		MOV 	@R0,A 
		INC		R2
		INC		R0		
		DJNZ 	R1,STORE

LOOP:	MOV 	R0,#30H 		;R0指向显示缓存区首址
		MOV 	R1,#7FH 		;R1为位控信号寄存器，指向第1个数码管
NEXT: 	MOV 	A,@R0 			;取出一个数
		INC 	R0 				;指针指向下一个数地址
		MOV 	DPTR,#TABLE 	;DPTR指向7段码表首地址
		MOVC	A,@A+DPTR 		;取出该数的7段码
		MOV 	P0,A 			;将7段码输出到段码输出口
		MOV 	A,R1
		MOV 	P1,A 			;位控信号输出到位控输出口
		LCALL 	DELAY1ms		
		SETB 	C
		MOV 	A,R1
		RRC 	A
		MOV 	R1,A 			;修改位控信号，指向下一个数码管
		JC 		NEXT 			;没有显示完毕，继续
		SJMP 	LOOP				
					
TABLE: DB 3FH,06H,5BH,4FH,66H,6DH,7DH,07H,7FH,6FH	;0-9的段码

DELAY1ms:MOV 	R6,#2			;延时1ms
DELOOP2:MOV 	R7,#250			;2μs*250*2
DELOOP1:DJNZ 	R7,DELOOP1
		DJNZ 	R6,DELOOP2
		RET
		END