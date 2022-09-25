		ORG 0000H
		SJMP MAIN
		ORG 000BH				;T0�ж�
		LJMP T0INT
		ORG 001BH
		LJMP T0INT1				;T1�ж�
		
		ORG 0040H		
MAIN:   MOV  	TMOD,#01H		;������ʽ1
    	MOV  	R0,#6			;ʮλ��ʼֵ
		MOV  	R1,#1			;��λ��ʼֵ

LOOP:	DEC		R1				;��λ������һ
		MOV 	R2,#20			;����20��50msѭ��
		MOV  	TH0,#3CH		;��ʱ��ʼ״̬
		MOV  	TL0,#0B0H
		SETB 	TR0				
		SETB 	EA				;�жϳ�ʼ��
		SETB 	ET0

		;��̬�������ʾ
DISDLAY:MOV 	A,R1			;��λ��ʾ
		MOV 	DPTR,#TABLE 
		MOVC 	A,@A+DPTR 
		MOV 	P0,A
		MOV 	P1,#7FH 
		LCALL  	DELAY1ms		;�ӳ���ʾ		
		
    	MOV 	A,R0			;ʮλ��ʾ
		MOV 	DPTR,#TABLE 
		MOVC 	A,@A+DPTR 
		MOV 	P0,A
		MOV 	P1,#0BFH
		LCALL  	DELAY1ms		;�ӳ���ʾ			
		
		CJNE	R2,#0,DISDLAY	;�ж�50ms�Ƿ����
		CJNE	R1,#0,LOOP		;�жϸ�λ�Ƿ�Ϊ�㣬��Ϊ����ת
		CJNE	R0,#0,GOON		;�ж�ʮλ�Ƿ�Ϊ�㣬��Ϊ����ת
		MOV 	P0,#0			;���㣬ֹͣ
		SJMP	$
		
GOON:	MOV  	R1,#0AH			;���ø�λ���ʼ״̬
		DEC		R0				;ʮλ��һ
		SJMP    LOOP			;����ѭ��
			
TABLE: DB 3FH,06H,5BH,4FH,66H,6DH,7DH,07H,7FH,6FH

DELAY1ms:	MOV  	R3,#1		;��ʱ1ms
			SETB 	ET1			;����T1��ʼ״̬
			MOV  	TH1,#0FCH
			MOV  	TL1,#18H
			SETB 	TR1
			CJNE    R3,#0,$		;̤���ȴ���ʱ���
			RET

T0INT: 	MOV  TL0,#0B0H			;T0�ж�
		MOV  TH0,#3CH
		DEC  R2
		RETI
		
T0INT1: MOV  TL1,#18H			;T1�ж�
		MOV  TH1,#0FCH
		DEC  R3
		RETI
		END
