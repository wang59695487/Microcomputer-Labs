		ORG	0000H			
MAIN:	MOV		R1,#06H		;ѭ������
		MOV		R0,#0H		;��ʾ��ʼֵ
LOOP:	MOV 	A,R0		;ȡ����
		MOV 	DPTR,#TABLE 
		MOVC 	A,@A+DPTR 
		MOV 	P0,A		;����������
		LCALL	DELAY200ms	;��ʱ200ms
		INC		R0			;��ʾ���ּ�1
		DJNZ	R1,LOOP		;��ʾ��Ϸ�
		SJMP	MAIN		;ѭ����ʾ
		
TABLE:  DB 0FEH,0FDH,0FBH,0F7H,0EFH,0DFH
			
DELAY200ms:MOV 	R5,#2		;��ʱ200ms
DELOOP3:MOV 	R6,#199
DELOOP2:MOV 	R7,#249
DELOOP1:DJNZ 	R7,DELOOP1
		DJNZ 	R6,DELOOP2
		DJNZ 	R5,DELOOP3	
		RET
		END
			
			