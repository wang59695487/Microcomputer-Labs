		ORG 0000H
		SJMP MAIN
		ORG 000BH				;T0�ж�
		LJMP T0INT
		
		ORG 0040H		
MAIN:   MOV  	TMOD,#01H		;������ʽ1
		MOV		R0,#0
LOOP:	MOV 	R5,#3			;����3��50msѭ��
		MOV  	TH0,#3CH		;��ʱ��ʼ״̬
		MOV  	TL0,#0B0H
		SETB 	TR0				
		SETB 	EA				;�жϳ�ʼ��
		SETB 	ET0

		;��̬�������ʾ	
DISDLAY:MOV 	A,R0			;ȡ��ѭ������
		MOV 	DPTR,#DUAN		;ȡ������
		MOVC 	A,@A+DPTR 		
		MOV 	P0,A		
		MOV 	A,R0			;ȡ��ѭ������
		MOV 	DPTR,#WEI 		;ȡ��λ��
		MOVC 	A,@A+DPTR 
		MOV 	P1,A
		CJNE	R5,#0,DISDLAY	;�ж�50ms�Ƿ����
		MOV 	R5,#3			;����3��50msѭ��
		INC		R0				
		CJNE	R0,#20,DISDLAY	;����ѭ��
		SJMP	MAIN
			
DUAN:	DB 08H,10H,20H,01H 			;��1�������4���εĶ��룬��20��
		DB 01H,01H,01H,01H,01H,01H 	;��2-7������ܵ�a�ζ���
		DB 01H,02H,04H,08H 		;��8�������4���εĶ���
		DB 08H,08H,08H,08H,08H,08H 	;��7-2������ܵ�d�ζ���
WEI:	DB 0FEH,0FEH,0FEH,0FEH 		;��1������ܵ�λ��
		DB 0FDH,0FBH,0F7H,0EFH,0DFH,0BFH 	;��2-7������ܵ�λ��
		DB 7FH,7FH,7FH,7FH 			;��8������ܵ�λ��
		DB 0BFH,0DFH,0EFH,0F7H,0FBH,0FDH 	;��7-2������ܵ�λ��

T0INT: 	MOV  TL0,#0B0H			;T0�ж�
		MOV  TH0,#3CH
		DEC  R5
		RETI
		END
