		ORG 	0000H
		MOV 	P1,#00H		;�����
		MOV 	P0,#5BH
		MOV 	P2,#01H
		LCALL 	DELAY
LOOP:	MOV 	P0,#5EH		;�������ϱ���
		MOV 	P2,#02H
		LCALL 	DELAY2S	
		LCALL	BLINK		;������˸
		MOV 	P0,#0EDH	;�Ƶ���
		MOV 	P2,#03H
		LCALL 	DELAY
		MOV 	P0,#0B3H    ;�������ϱ���
		MOV 	P2,#01H
		LCALL 	DELAY2S
		LCALL 	BLINK		;������˸
		MOV 	P0,#0EDH	;�Ƶ���
		MOV 	P2,#03H		
		LCALL 	DELAY		
		SJMP 	LOOP

BLINK:	MOV 	R3,#2	    ;������˸
BLINK0:	MOV 	P0,#5BH	    ;�����
		MOV 	P2,#01H
		LCALL 	DELAY
		MOV 	P0,#0B6H	;�̵���
		MOV 	P2,#02H
		LCALL 	DELAY
		DJNZ 	R3,BLINK0
		RET			

DELAY2S:MOV	    R4,#4		;��ʱ2s
DELOOP0:LCALL   DELAY
		DJNZ 	R4,DELOOP0
		RET		

DELAY:  MOV 	R5,#4		;��ʱ0.5s
DELOOP3:MOV 	R6,#248
DELOOP2:MOV 	R7,#250
DELOOP1:DJNZ 	R7,DELOOP1
		DJNZ 	R6,DELOOP2
		DJNZ 	R5,DELOOP3	
		RET
		END
