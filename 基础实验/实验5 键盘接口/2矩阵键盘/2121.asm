		ORG	0000H			
MAIN:	MOV		P1,#0FH			;P1准备输入
		MOV		A,P1			;查询有无按键
		ADD		A,#0F0H
		CJNE	A,#0FFH,IFKEY  	;取列值
		SJMP   	MAIN
		
IFKEY:	LCALL	DELAY10ms       ;去前沿抖动
		MOV		R3,#0FFH        ;设置按键初值	
		MOV 	P1,#0FH 		;行输出全0
		MOV		A,P1			;读入键值		
		ADD		A,#0F0H
		XRL  	A,#0FFH  		;取列值
		CJNE	A,#0,IFKEY1  	;不为零跳转
		MOV		A,#0FFH			;将A全置1
		SJMP	NOKEY	        
IFKEY1:	MOV		B,A    			;将列值送入B
		MOV 	P1,#0F0H 		;列输出全0
		MOV		A,P1			;读入键值		
		ADD		A,#0FH
		XRL  	A,#0FFH  		;取行值
		CJNE	A,#0,IFKEY2  	;不为零跳转
		MOV		A,#0FFH	          
        SJMP	NOKEY	
IFKEY2:	ADD 	A,B				;得到特征码
		MOV 	B,A				;将特征码保存到B		
		MOV 	DPTR,#KEYCD		
SCAN:	INC   	R3				;特征码匹配
       	MOV     A,R3
       	MOVC    A,@A+DPTR		;获取特征码
       	CJNE	A,B,SCAN1       ;特征码与B中是否一致
       	SJMP	WAIT		
SCAN1:  CJNE   	A,#0FFH,SCAN    ;没有溢出继续查询
      	MOV     A,#0FFH         ;将A全置1    
       	SJMP	NOKEY	 
				    
WAIT:	MOV 	P1,#0FH 		;行输出全0
		MOV		A,P1			;读入键值		
		ADD		A,#0F0H
		XRL  	A,#0FFH  		;取列值
		CJNE	A,#0,WAIT  		;不为零跳转
		LCALL	DELAY10ms       ;去后沿抖动
NOKEY:	MOV 	A,R3			;静态数码管显示数值
		MOV 	DPTR,#TABLE 
		MOVC 	A,@A+DPTR 
		MOV 	P0,A
		SJMP	MAIN
	
KEYCD:  DB 11H,21H,41H,81H,12H,22H,42H,82H,14H,24H,44H,84H,18H,28H,48H,88H,0FFH
TABLE:  DB 0C0H,0F9H,0A4H,0B0H,99H,92H,82H,0F8H,80H,90H,08H,00H,46H,40H,06H,0EH
	
DELAY10ms:MOV 	R6,#20			;延时10ms
DELOOP2:MOV 	R7,#250			;2μs*250*20
DELOOP1:DJNZ 	R7,DELOOP1
		DJNZ 	R6,DELOOP2
		RET
		END