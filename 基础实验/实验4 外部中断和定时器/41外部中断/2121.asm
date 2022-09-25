		ORG 0000H
		LJMP MAIN
		ORG 0003H
		LJMP INT0SUB
		
		ORG 0030H
MAIN:	SETB IT0	 ;下降沿触发
		SETB EA		 ;CPU中断开放
		SETB EX0	 ;INT0中断允许
		SETB  P1.0
		SJMP $
			
INT0SUB:CLR Ex0
        delay 10ms
        CPL p1.0
        delay 10ms
        SETB Ex0
        RET I
        END
