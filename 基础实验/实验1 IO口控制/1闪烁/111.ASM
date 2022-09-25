		ORG 	0000H
LOOP: 	CLR 	P1.0
		LCALL 	Delay10ms
		SETB 	P1.0
		LCALL 	Delay10ms
		LCALL 	Delay10ms
		SJMP 	LOOP
		
Delay10ms:	MOV  R6,#20
Dloop1:		MOV  R7,#250
DLoop0:		DJNZ R7 ,Dloop0
			DJNZ R6 ,Dloop1
			RET

