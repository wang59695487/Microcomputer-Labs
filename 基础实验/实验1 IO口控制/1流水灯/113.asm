		ORG 	0000H
MAIN: 	MOV		R3,#40		;����ѭ������
		MOV 	A,#01H		;���ó�ʼ״̬
OUTPUT: MOV 	P1,A
		RL		A			;ѭ������
		LCALL	DELAY
		DJNZ 	R3,OUTPUT	
		MOV 	P1,#0		;���������
		SJMP 	$
		
DELAY: 	MOV 	R5,#4		 ;��ʱ����,500����
DELOOP3:MOV 	R6,#248
DELOOP2:MOV 	R7,#250
DELOOP1:DJNZ 	R7,DELOOP1
		DJNZ 	R6,DELOOP2
		DJNZ 	R5,DELOOP3	
		MOV		R4,#2		 ;������ʱ8΢��
DELOOP0:DJNZ 	R4,DELOOP0
		NOP
		RET
		END

