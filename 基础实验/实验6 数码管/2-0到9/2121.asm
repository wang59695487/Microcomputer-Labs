		ORG	0000H			
MAIN:	MOV		R1,#0AH		;ѭ������
		MOV		R0,#0H		;��ʾ��ʼֵ
LOOP:	MOV 	A,R0		;ȡ����
		MOV 	DPTR,#TABLE 
		MOVC 	A,@A+DPTR 
		MOV 	P0,A		;����������
		LCALL	DELAY1s		;��ʱ1s
		INC		R0			;��ʾ���ּ�1
		DJNZ	R1,LOOP		;��ʾ��Ϸ�
		SJMP	MAIN		;ѭ����ʾ
		
TABLE:  DB 0C0H,0F9H,0A4H,0B0H,99H,92H,82H,0F8H,80H,90H
			
DELAY1s:MOV 	R5,#8		;��ʱ1s
DELOOP3:MOV 	R6,#248
DELOOP2:MOV 	R7,#250
DELOOP1:DJNZ 	R7,DELOOP1
		DJNZ 	R6,DELOOP2
		DJNZ 	R5,DELOOP3	
		RET
		END
			
			