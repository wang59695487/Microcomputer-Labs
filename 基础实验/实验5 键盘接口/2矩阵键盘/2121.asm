		ORG	0000H			
MAIN:	MOV		P1,#0FH			;P1׼������
		MOV		A,P1			;��ѯ���ް���
		ADD		A,#0F0H
		CJNE	A,#0FFH,IFKEY  	;ȡ��ֵ
		SJMP   	MAIN
		
IFKEY:	LCALL	DELAY10ms       ;ȥǰ�ض���
		MOV		R3,#0FFH        ;���ð�����ֵ	
		MOV 	P1,#0FH 		;�����ȫ0
		MOV		A,P1			;�����ֵ		
		ADD		A,#0F0H
		XRL  	A,#0FFH  		;ȡ��ֵ
		CJNE	A,#0,IFKEY1  	;��Ϊ����ת
		MOV		A,#0FFH			;��Aȫ��1
		SJMP	NOKEY	        
IFKEY1:	MOV		B,A    			;����ֵ����B
		MOV 	P1,#0F0H 		;�����ȫ0
		MOV		A,P1			;�����ֵ		
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
				    
WAIT:	MOV 	P1,#0FH 		;�����ȫ0
		MOV		A,P1			;�����ֵ		
		ADD		A,#0F0H
		XRL  	A,#0FFH  		;ȡ��ֵ
		CJNE	A,#0,WAIT  		;��Ϊ����ת
		LCALL	DELAY10ms       ;ȥ���ض���
NOKEY:	MOV 	A,R3			;��̬�������ʾ��ֵ
		MOV 	DPTR,#TABLE 
		MOVC 	A,@A+DPTR 
		MOV 	P0,A
		SJMP	MAIN
	
KEYCD:  DB 11H,21H,41H,81H,12H,22H,42H,82H,14H,24H,44H,84H,18H,28H,48H,88H,0FFH
TABLE:  DB 0C0H,0F9H,0A4H,0B0H,99H,92H,82H,0F8H,80H,90H,08H,00H,46H,40H,06H,0EH
	
DELAY10ms:MOV 	R6,#20			;��ʱ10ms
DELOOP2:MOV 	R7,#250			;2��s*250*20
DELOOP1:DJNZ 	R7,DELOOP1
		DJNZ 	R6,DELOOP2
		RET
		END