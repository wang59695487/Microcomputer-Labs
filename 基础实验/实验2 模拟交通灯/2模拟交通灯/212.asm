		ORG 	0000H
		MOV 	P1,#00H		;╨Л╣фаа
		MOV 	P0,#5BH
		MOV 	P2,#01H
		LCALL 	DELAY
LOOP:	MOV 	P0,#5EH		;╤╚нВблдо╠╠╨Л
		MOV 	P2,#02H
		LCALL 	DELAY2S	
		LCALL	BLINK		;╨Лблиак╦
		MOV 	P0,#0EDH	;╩ф╣фаа
		MOV 	P2,#03H
		LCALL 	DELAY
		MOV 	P0,#0B3H    ;╤╚нВ╨Лдо╠╠бл
		MOV 	P2,#01H
		LCALL 	DELAY2S
		LCALL 	BLINK		;╨Лблиак╦
		MOV 	P0,#0EDH	;╩ф╣фаа
		MOV 	P2,#03H		
		LCALL 	DELAY		
		SJMP 	LOOP

BLINK:	MOV 	R3,#2	    ;╨Лблиак╦
BLINK0:	MOV 	P0,#5BH	    ;╨Л╣фаа
		MOV 	P2,#01H
		LCALL 	DELAY
		MOV 	P0,#0B6H	;бл╣фаа
		MOV 	P2,#02H
		LCALL 	DELAY
		DJNZ 	R3,BLINK0
		RET			

DELAY2S:MOV	    R4,#4		;ясй╠2s
DELOOP0:LCALL   DELAY
		DJNZ 	R4,DELOOP0
		RET		

DELAY:  MOV 	R5,#4		;ясй╠0.5s
DELOOP3:MOV 	R6,#248
DELOOP2:MOV 	R7,#250
DELOOP1:DJNZ 	R7,DELOOP1
		DJNZ 	R6,DELOOP2
		DJNZ 	R5,DELOOP3	
		RET
		END
