		ORG	0000H			
MAIN:	MOV		P1,#0FFH		;P1׼������
		MOV		A,P1			;��ѯ���ް���
		CJNE	A,#0FFH,IFKEY	;�ް������²�ѯ
		SJMP   	MAIN
		
IFKEY:	LCALL	DELAY10ms       ;ȥǰ�ض���
		MOV		R3,#00H         ;���ð�����ֵ
		MOV		A,P1			;�����ֵ
		XRL		A,#0FFH			;��Aȡ��
		CJNE	A,#0H,SCAN  	;�ް�����ת
		MOV		A,#0FFH			;��Aȫ��1
		SJMP	NOKEY	        
SCAN:	MOV		R2,#8	        ;ѭ��8��
SCAN1:	RRC		A				;ѭ������
		JC		WAIT         	;�ж�A��Ϊ1��λ�Ƿ��Ƴ�
		INC		R3				;��ֵ��1
		DJNZ	R2,SCAN1
		MOV		A,#0FFH	        ;��Aȫ��1
        SJMP	NOKEY				  
WAIT:	MOV		A,P1			;�����P1
		CJNE	A,#0FFH,WAIT    ;�ȴ�����̧��
		LCALL	DELAY10ms       ;ȥ���ض���
NOKEY:	MOV 	A,R3			;��̬�������ʾ��ֵ
		INC		A				;��0-7��Ϊ1-8
		MOV 	B,A				;���浽B
		MOV 	DPTR,#TABLE 
		MOVC 	A,@A+DPTR 
		MOV 	P0,A
		SJMP	MAIN	
		
TABLE:  DB 0C0H,0F9H,0A4H,0B0H,99H,92H,82H,0F8H,80H,90H
	
DELAY10ms:MOV 	R6,#20			;��ʱ10ms
DELOOP2:MOV 	R7,#250			;2��s*250*20
DELOOP1:DJNZ 	R7,DELOOP1
		DJNZ 	R6,DELOOP2
		RET
		END