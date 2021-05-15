.386
.MODEL FLAT, C

INCLUDE D:\masm32\include\user32.inc
INCLUDE D:\masm32\include\kernel32.inc
INCLUDELIB  D:\masm32\lib\user32.lib
INCLUDELIB  D:\masm32\lib\kernel32.lib
GOODS	STRUCT				;商品信息结构声明
	GNAME	DB 10 DUP(0)	;商品名
	GOFF	DB	?			;折扣
	GIP		DW	?			;进货价
	GSP		DW	?			;售货价
	GNUM	DW	?			;进货总数
	GSOLD	DW  ?			;销售量
	GRECO	DW  ?			;推荐度
GOODS	ENDS

PUBLIC	  GOOD, GA1, GA2, GA3
printf	  PROTO C :dword, :vararg 
RECOMMEND PROTO
FIND_G	  PROTO :DWORD
BUY_G	 PROTO

.STACK
.CONST
		N  EQU 3
.DATA
		N_LOOP  DB  0
		GOOD	DD  0
		GA1		GOODS < "BOOK", 9, 25, 36, 100, 20, 0 >		;N个商品的信息定义
		GA2		GOODS < "CUP", 8, 8, 15, 150, 24, 0 >	
		GA3		GOODS < "PEN", 34, 60, 30, 2, 0, 0 >

.CODE
;寻找商品
FIND_G	PROC  FNAME_ADDR:DWORD
	FINDGOOD:
		MOV  ESI, OFFSET GA1
		MOV  EDX, ESI
		MOV  CL, N      ;CL用于商品数量计数
	FIND_LOOP:
		MOV  CH, 10     ;CH用于商品名字比对
		MOV  EDI, FNAME_ADDR
	FIND_COMPARE:
		MOV  AL, [ESI]
		CMP  (AL),[EDI]
		JNE  FIND_CHANGE
		INC  ESI
		INC  EDI
		DEC  CH
		JZ   FIND_SUCCESS
		JNZ  FIND_COMPARE
	FIND_CHANGE:
		ADD  EDX, 21
		MOV  ESI, EDX
		DEC  CL
		JNZ  FIND_LOOP
		JMP  FIND_FAIL
	FIND_SUCCESS:
		MOV  GOOD, EDX
		MOV  EAX,1;找到返回1
		RET
	FIND_FAIL:
		MOV	 EAX,0;没找到返回0		
		RET
FIND_G ENDP


;子程序3-下订单，如果GOOD地址为0则返回主菜单
BUY_G PROC
	PURCHASE:
		MOV  ESI, GOOD
		MOV  AL, [ESI]
		CMP  (AL), 0
		JE   BUY_EXIT
		MOV  BX, WORD PTR [ESI+15]
		MOV  AX, WORD PTR [ESI+17]
		CMP  AX, BX
		JGE  FAIL_EXIT
		MOV  CX, 1
		ADD  [ESI+17], CX
		CALL RECOMMEND  ;计算所有商品的推荐度并输出(16进制)
	BUY_EXIT:
	    MOV  EAX, 1 ;返回0，购买成功
		RET
	FAIL_EXIT:
		MOV  EAX, 0 ;返回1，购买失败
		RET
BUY_G ENDP


;子程序-计算所有的商品推荐度,商品数量N
RECOMMEND PROC	
		MOV   N_LOOP, 0       ;初始化
		MOV   ESI, OFFSET GA1
	CAL_LOOP:
		MOV  BL, N_LOOP       ;商品计算次数
		CMP  BL, N
		JE   REC_EXIT
		MOV  AH, 0
		MOV  AL, [ESI+10] ;折扣
		MOV  BX, WORD PTR[ESI+13] ;销售价
		IMUL AX, BX      ;AX=销售价*折扣
		CWD
		MOV  BX, 10
		IDIV BX          ;AX=实际销售价格=AX/10(BX)
		MOV  BX, AX      ;BX=实际销售价格
		MOV  AX, WORD PTR[ESI+11] ;AX=进货价
		MOV  CX, 128
		IMUL AX, CX
		CWD
		IDIV BX          ;AX=进货价(AX)*128/实际销售价格(BX)
		MOV  CX, AX      ;CX=进货价(AX)*128/实际销售价格(BX)
		MOV  AX, WORD PTR[ESI+17] ;AX=已售数量
		MOV  BX, 64
		IMUL AX, BX
		CWD
		MOV  BX, WORD PTR[ESI+15] ;BX=进货数量
		IDIV BX                  ;AX=已售数量*128/进货数量*2
		ADD  AX, CX              ;AX=AX+CX
		MOV  [ESI+19], AX
		MOV  AX, [ESI+19]
		MOV  BL, N_LOOP    ;商品计算次数
		INC  BL
		MOV  N_LOOP, BL
		ADD  ESI, 21        ;计算下一个商品
		JMP  CAL_LOOP
	REC_EXIT:
		RET
RECOMMEND ENDP
	END
