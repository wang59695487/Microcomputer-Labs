		OUTPUT BIT P1.0
		ORG 0000H
		LJMP START
		ORG 000BH
		LJMP INT00
		
		ORG 0030H
START:  MOV TMOD, #01H		;工作方式1，16位计数器
		SETB ET0			;T0中断允许
		SETB EA				;CPU中断允许
MUSIC0: CLR A
		MOV 40H, A 			;40H存放取值的序号
MUSIC1: MOV DPTR, #TABLE
		MOV A, 40H
		MOVC A, @A+DPTR 	;取出一个音调+节拍

		JZ END0 			;00H表示整个乐曲播放结束
		MOV 30H, A 			;30H暂存 音调+节拍
		ANL A, #0FH 		;低四位表示节拍
		MOV 31H, A 			;31H存放节拍码(基本DELAY的个数)
		MOV A, 30H
		SWAP A
		ANL A, #0FH			;高四位表示音调
		MOV 32H,A 			;32H存放音符的音调，查得定时初值
MUSIC2: MOV DPTR,# TABLE1 	;简谱频率表表头（定时初值）
		MOV A, 32H			;取出定时初值
		RL A				;循环左移,初值乘2得定时初值位置
		MOV 34H,A			;34H存放定时初值位置
		MOVC A,@A+DPTR		;取出初值高字节
		MOV TH0,A 			;设定定时器的初值高字节
		MOV 44H,A 			;44H保存定时器初值高字节
		INC 34H				
		MOV A,34H
		MOVC A,@A+DPTR		;取出初值低字节
		MOV TL0,A 			;设定定时器的初值低字节
		MOV 45H,A			;45H保存定时器初值高字节
		SETB TR0			;开始计时，播放音调
DEL_NS: LCALL DLY125ms 		;进行节拍数的延时
		DJNZ 31H, DEL_NS	;31H为之前查得的节拍数(基本DELAY的个数)
		INC 40H 			;准备下一个音符的播放
		SJMP MUSIC1
END0:   CLR TR0 			;一遍结束，停止计时							
		LCALL DLY125ms		;延时0.5s后，循环播放
		LCALL DLY125ms
		LCALL DLY125ms
		LCALL DLY125ms
		SJMP MUSIC0
		
DLY125ms: MOV R3, #5		;音调的一个基本延时时间125ms
DEL2: 	  MOV R4, #50 		;R4循环延时50x0.5ms=25ms
DEL3: 	  MOV R5, #250 		;R5循环延时250x2us=0.5ms
DEL4: 	  DJNZ R5, DEL4
		  DJNZ R4, DEL3
		  DJNZ R3, DEL2
		  RET
		
INT00:	MOV TH0,44H 		;定时中断服务程序
		MOV TL0,45H			;重新载入定时初值
		CPL OUTPUT			;P1.0取反
		RETI
		
;《欢乐颂》简谱中每个音符及节拍的编码表，高四位为简谱编码，低四位为节拍（基本delay的个数）
TABLE:  DB 64H,64H,74H,84H,84H,74H,64H,54H,44H,44H,54H,64H,66H,52H,58H
		DB 64H,64H,74H,84H,84H,74H,64H,54H,44H,44H,54H,64H,56H,42H,48H
		DB 64H,54H,64H,44H,54H,62H,72H,64H,54H,62H,72H,64H,54H,44H,54H,12H,64H
		DB 64H,64H,74H,84H,84H,74H,64H,54H,44H,44H,54H,64H,56H,42H,48H,00H

TABLE1: DB 00H,00H,0FBH, 04H,0FBH,92H,0FCH,0CH ;低音5-低音7
		DB 0FCH, 44H,0FCH,0ACH,0FDH,09H 	   ;中音1-中音3
		DB 0FDH, 34H,0FDH,82H,0FDH,0C8H 	   ;中音4-中音5
		DB 0FEH, 06H,0FEH,22H,0FEH,56H 		   ;中音6-高音1
		DB 0FEH, 85H,0FEH,9AH,0FEH,0C1H 	   ;高音2-高音5
		END
