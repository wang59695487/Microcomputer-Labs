		ORG 0000H
		LJMP MAIN
		ORG 0003H
		LJMP INT0SUB
		
		ORG 0030H
MAIN:	SETB IT0	 ;�½��ش���
		SETB EA		 ;CPU�жϿ���
		SETB EX0	 ;INT0�ж�����
		SETB  P1.0
		SJMP $
			
INT0SUB:CLR Ex0
        delay 10ms
        CPL p1.0
        delay 10ms
        SETB Ex0
        RET I
        END
