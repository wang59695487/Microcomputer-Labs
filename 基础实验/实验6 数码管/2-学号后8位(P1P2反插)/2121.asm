		ORG 	0000H
		SJMP 	MAIN
		
		ORG		0040H
MAIN:	MOV		R0,#30H			;���ô�����ַ
		MOV		R1,#08H			;����ѭ������
LOOP:	MOV		P2,#0FH			;P1׼������
		MOV		A,P2			;��ѯ���ް���
		ADD		A,#0F0H
		CJNE	A,#0FFH,IFKEY  	;ȡ��ֵ
		SJMP   	LOOP
		
IFKEY:	LCALL	DELAY10ms       ;ȥǰ�ض���
		MOV		R3,#0FFH        ;���ð�����ֵ	
		MOV 	P2,#0FH 		;�����ȫ0
		MOV		A,P2			;�����ֵ		
		ADD		A,#0F0H
		XRL  	A,#0FFH  		;ȡ��ֵ
		CJNE	A,#0,IFKEY1  	;��Ϊ����ת
		MOV		A,#0FFH			;��Aȫ��1
		SJMP	NOKEY	        
IFKEY1:	MOV		B,A    			;����ֵ����B
		MOV 	P2,#0F0H 		;�����ȫ0
		MOV		A,P2			;�����ֵ		
		ADD		A,#0FH
		XRL  	A,#0FFH  		;ȡ��ֵ
		CJNE	A,#0,IFKEY2  	;��Ϊ����ת
		MOV		A,#0FFH	          
        SJMP	NOKEY	
IFKEY2:	ADD 	A,B				;�õ�������
		MOV 	B,A				;�������뱣�浽B		
		MOV 	DPTR,#KEYCD		
SCAN:	INC   	R3				;������ƥ��
       	MOV     A,R3
       	MOVC    A,@A+DPTR		;��ȡ������
       	CJNE	A,B,SCAN1       ;��������B���Ƿ�һ��
       	SJMP	WAIT		
SCAN1:  CJNE   	A,#0FFH,SCAN    ;û�����������ѯ
      	MOV     A,#0FFH         ;��Aȫ��1    
       	SJMP	NOKEY	 
				    
WAIT:	MOV 	P2,#0FH 		;�����ȫ0
		MOV		A,P2			;�����ֵ		
		ADD		A,#0F0H
		XRL  	A,#0FFH  		;ȡ��ֵ
		CJNE	A,#0,WAIT  		;��Ϊ����ת
		LCALL	DELAY10ms       ;ȥ���ض���
		MOV 	A,R3			;��������
		MOV 	@R0,A
		INC		R0
		DEC		R1
NOKEY:	CJNE	R1,#0,LOOP		;ѭ��8��
		SJMP	DISPLAY			;��ʼ��ʾ
	
KEYCD:  DB 11H,21H,41H,81H,12H,22H,42H,82H,14H,24H,44H,84H,18H,28H,48H,88H,0FFH
	
DELAY10ms:MOV 	R6,#20			;��ʱ10ms
DELOOP2:MOV 	R7,#250			;2��s*250*20
DELOOP1:DJNZ 	R7,DELOOP1
		DJNZ 	R6,DELOOP2
		RET
									
DISPLAY:MOV 	R0,#30H 		;R0ָ����ʾ��������ַ
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
		SJMP 	DISPLAY 				
			
TABLE: DB 3FH,06H,5BH,4FH,66H,6DH,7DH,07H,7FH,6FH	;0-9�Ķ���

DELAY1ms:MOV 	R6,#2			;��ʱ1ms
DELOOP4:MOV 	R7,#250			;2��s*250*2
DELOOP3:DJNZ 	R7,DELOOP3
		DJNZ 	R6,DELOOP4
		RET
		END