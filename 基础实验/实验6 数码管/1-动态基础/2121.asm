		ORG 	0000H
		SJMP 	MAIN
		
		ORG		0040H
MAIN: 	MOV 	R0,#30H 		;����ֵ1-8
		MOV 	R1,#08H 
		MOV 	R2,#01H 
STORE:	MOV 	A,R2
		MOV 	@R0,A 
		INC		R2
		INC		R0		
		DJNZ 	R1,STORE

LOOP:	MOV 	R0,#30H 		;R0ָ����ʾ��������ַ
		MOV 	R1,#7FH 		;R1Ϊλ���źżĴ�����ָ���1�������
NEXT: 	MOV 	A,@R0 			;ȡ��һ����
		INC 	R0 				;ָ��ָ����һ������ַ
		MOV 	DPTR,#TABLE 	;DPTRָ��7������׵�ַ
		MOVC	A,@A+DPTR 		;ȡ��������7����
		MOV 	P0,A 			;��7������������������
		MOV 	A,R1
		MOV 	P1,A 			;λ���ź������λ�������
		LCALL 	DELAY1ms		
		SETB 	C
		MOV 	A,R1
		RRC 	A
		MOV 	R1,A 			;�޸�λ���źţ�ָ����һ�������
		JC 		NEXT 			;û����ʾ��ϣ�����
		SJMP 	LOOP				
					
TABLE: DB 3FH,06H,5BH,4FH,66H,6DH,7DH,07H,7FH,6FH	;0-9�Ķ���

DELAY1ms:MOV 	R6,#2			;��ʱ1ms
DELOOP2:MOV 	R7,#250			;2��s*250*2
DELOOP1:DJNZ 	R7,DELOOP1
		DJNZ 	R6,DELOOP2
		RET
		END