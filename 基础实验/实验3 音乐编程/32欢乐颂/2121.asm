		OUTPUT BIT P1.0
		ORG 0000H
		LJMP START
		ORG 000BH
		LJMP INT00
		
		ORG 0030H
START:  MOV TMOD, #01H		;������ʽ1��16λ������
		SETB ET0			;T0�ж�����
		SETB EA				;CPU�ж�����
MUSIC0: CLR A
		MOV 40H, A 			;40H���ȡֵ�����
MUSIC1: MOV DPTR, #TABLE
		MOV A, 40H
		MOVC A, @A+DPTR 	;ȡ��һ������+����

		JZ END0 			;00H��ʾ�����������Ž���
		MOV 30H, A 			;30H�ݴ� ����+����
		ANL A, #0FH 		;����λ��ʾ����
		MOV 31H, A 			;31H��Ž�����(����DELAY�ĸ���)
		MOV A, 30H
		SWAP A
		ANL A, #0FH			;����λ��ʾ����
		MOV 32H,A 			;32H�����������������ö�ʱ��ֵ
MUSIC2: MOV DPTR,# TABLE1 	;����Ƶ�ʱ��ͷ����ʱ��ֵ��
		MOV A, 32H			;ȡ����ʱ��ֵ
		RL A				;ѭ������,��ֵ��2�ö�ʱ��ֵλ��
		MOV 34H,A			;34H��Ŷ�ʱ��ֵλ��
		MOVC A,@A+DPTR		;ȡ����ֵ���ֽ�
		MOV TH0,A 			;�趨��ʱ���ĳ�ֵ���ֽ�
		MOV 44H,A 			;44H���涨ʱ����ֵ���ֽ�
		INC 34H				
		MOV A,34H
		MOVC A,@A+DPTR		;ȡ����ֵ���ֽ�
		MOV TL0,A 			;�趨��ʱ���ĳ�ֵ���ֽ�
		MOV 45H,A			;45H���涨ʱ����ֵ���ֽ�
		SETB TR0			;��ʼ��ʱ����������
DEL_NS: LCALL DLY125ms 		;���н���������ʱ
		DJNZ 31H, DEL_NS	;31HΪ֮ǰ��õĽ�����(����DELAY�ĸ���)
		INC 40H 			;׼����һ�������Ĳ���
		SJMP MUSIC1
END0:   CLR TR0 			;һ�������ֹͣ��ʱ							
		LCALL DLY125ms		;��ʱ0.5s��ѭ������
		LCALL DLY125ms
		LCALL DLY125ms
		LCALL DLY125ms
		SJMP MUSIC0
		
DLY125ms: MOV R3, #5		;������һ��������ʱʱ��125ms
DEL2: 	  MOV R4, #50 		;R4ѭ����ʱ50x0.5ms=25ms
DEL3: 	  MOV R5, #250 		;R5ѭ����ʱ250x2us=0.5ms
DEL4: 	  DJNZ R5, DEL4
		  DJNZ R4, DEL3
		  DJNZ R3, DEL2
		  RET
		
INT00:	MOV TH0,44H 		;��ʱ�жϷ������
		MOV TL0,45H			;�������붨ʱ��ֵ
		CPL OUTPUT			;P1.0ȡ��
		RETI
		
;�������̡�������ÿ�����������ĵı��������λΪ���ױ��룬����λΪ���ģ�����delay�ĸ�����
TABLE:  DB 64H,64H,74H,84H,84H,74H,64H,54H,44H,44H,54H,64H,66H,52H,58H
		DB 64H,64H,74H,84H,84H,74H,64H,54H,44H,44H,54H,64H,56H,42H,48H
		DB 64H,54H,64H,44H,54H,62H,72H,64H,54H,62H,72H,64H,54H,44H,54H,12H,64H
		DB 64H,64H,74H,84H,84H,74H,64H,54H,44H,44H,54H,64H,56H,42H,48H,00H

TABLE1: DB 00H,00H,0FBH, 04H,0FBH,92H,0FCH,0CH ;����5-����7
		DB 0FCH, 44H,0FCH,0ACH,0FDH,09H 	   ;����1-����3
		DB 0FDH, 34H,0FDH,82H,0FDH,0C8H 	   ;����4-����5
		DB 0FEH, 06H,0FEH,22H,0FEH,56H 		   ;����6-����1
		DB 0FEH, 85H,0FEH,9AH,0FEH,0C1H 	   ;����2-����5
		END
