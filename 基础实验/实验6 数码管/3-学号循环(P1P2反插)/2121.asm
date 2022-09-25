		ORG 	0000H
		SJMP 	MAIN
		ORG 	000BH			;T0中断
		LJMP 	T0INT
		
		ORG		0040H
MAIN:	MOV		R0,#30H			;设置储存首址
		MOV		R1,#0AH			;设置循环次数
LOOP:	MOV		P2,#0FH			;P1准备输入
		MOV		A,P2			;查询有无按键
		ADD		A,#0F0H
		CJNE	A,#0FFH,IFKEY  	;取列值
		SJMP   	LOOP
		
IFKEY:	LCALL	DELAY10ms       ;去前沿抖动
		MOV		R3,#0FFH        ;设置按键初值	
		MOV 	P2,#0FH 		;行输出全0
		MOV		A,P2			;读入键值		
		ADD		A,#0F0H
		XRL  	A,#0FFH  		;取列值
		CJNE	A,#0,IFKEY1  	;不为零跳转
		MOV		A,#0FFH			;将A全置1
		SJMP	NOKEY	        
IFKEY1:	MOV		B,A    			;将列值送入B
		MOV 	P2,#0F0H 		;列输出全0
		MOV		A,P2			;读入键值		
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
				    
WAIT:	MOV 	P2,#0FH 		;行输出全0
		MOV		A,P2			;读入键值		
		ADD		A,#0F0H
		XRL  	A,#0FFH  		;取列值
		CJNE	A,#0,WAIT  		;不为零跳转
		LCALL	DELAY10ms       ;去后沿抖动
		MOV 	A,R3			;保存数字
		MOV 	@R0,A
		INC		R0
		DEC		R1
NOKEY:	CJNE	R1,#0,LOOP		;循环10次
		SJMP	DISPLAY			;开始显示
	
KEYCD:  DB 11H,21H,41H,81H,12H,22H,42H,82H,14H,24H,44H,84H,18H,28H,48H,88H,0FFH
	
DELAY10ms:MOV 	R6,#20			;延时10ms
DELOOP2:MOV 	R7,#250			;2μs*250*20
DELOOP1:DJNZ 	R7,DELOOP1
		DJNZ 	R6,DELOOP2
		RET			

DISPLAY:MOV		3AH,#0AH		;保存辅助数字
		MOV		R2,#07H		
		MOV		R0,#30H			
		MOV		R1,#3BH	
MORE:	MOV		A,@R0	
		MOV		@R1,A
		INC		R0
		INC		R1
		DJNZ 	R2,MORE		

DISPLAY1:MOV 	R0,#30H 		;R0指向显示缓存区首址
		MOV 	R3,#30H 		;R0指向显示缓存区首址
		MOV		R5,#0BH			;R5计数10次一循环
		MOV  	TMOD,#01H		;工作方式1
DISLOOP:MOV 	R2,#20			;设置20个50ms循环
		MOV  	TH0,#3CH		;定时初始状态
		MOV  	TL0,#0B0H
		SETB 	TR0				
		SETB 	EA				;中断初始化
		SETB 	ET0

		;动态数码管显示						
DISLOOP1:MOV	A,R3
		MOV		R0,A
		MOV 	R1,#7FH 		;R1为位控信号寄存器，指向第1个数码管
NEXT: 	MOV 	A,@R0 			;取出一个数
		INC 	R0 				;指针指向下一个数地址
		MOV 	DPTR,#TABLE 	;DPTR指向7段码表首地址
		MOVC	A,@A+DPTR 		;取出该数的7段码
		MOV 	P0,A 			;将7段码输出到段码输出口
		MOV 	A,R1
		MOV 	P1,A 			;位控信号输出到位控输出口
		LCALL 	DELAY1ms		
		SETB 	C
		MOV 	A,R1
		RRC 	A
		MOV 	R1,A 			;修改位控信号，指向下一个数码管
		JC 		NEXT 			;没有显示完毕，继续		
		CJNE	R2,#0,DISLOOP1	;判断1s是否完成
		INC		R3
		DJNZ 	R5,DISLOOP
		SJMP	DISPLAY1
			
TABLE:  DB 3FH,06H,5BH,4FH,66H,6DH,7DH,07H,7FH,6FH,00H	;0-9及黑格的段码
		
DELAY1ms:MOV 	R6,#2			;延时1ms
DELOOP4:MOV 	R7,#250			;2μs*250*2
DELOOP3:DJNZ 	R7,DELOOP3
		DJNZ 	R6,DELOOP4
		RET		
		
T0INT: 	MOV  TL0,#0B0H			;T0中断
		MOV  TH0,#3CH
		DEC  R2
		RETI
		END			