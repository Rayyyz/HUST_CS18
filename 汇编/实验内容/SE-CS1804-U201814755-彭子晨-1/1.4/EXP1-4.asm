.386
STACK  SEGMENT USE16 STACK
DB 500 DUP(0)
STACK  ENDS
DATA   SEGMENT USE16
    BNAME   DB  'PENG ZC', 0DH, 2 DUP(0) ;老板姓名
    CNAME   DB  'CUSTOMER',2 DUP(0)
    BPASS   DB  '12345',0DH     ;密码,5位,0结尾
    AUTH    DB  0               ;当前登录状态,0表示顾客状态
    GOOD    DW  0               ;当前浏览商品地址
    N       EQU 5               ;商品总数
    SNAME   DB  'SHOP',0        ;网店名称,用0结束
    LOOP_TIMES  DD  500000          ;循环次数
    GA1     DB  'GOOD1', 0DH, 4 DUP(0), 10    ;商品名称及折扣
            DW  35,56,78,2,0               ;进货价,销售价,进货总数,已售数量,推荐度
    GA2     DB  'GOOD2', 0DH, 4 DUP(0), 9     ;商品名称及折扣
            DW  12,30,25,5,64           ;进货价,销售价,进货总数,已售数量,推荐度
    GAN     DB  N-2  DUP('TmpValue', 0DH, 0, 8, 15, 0, 20, 0, 30, 0, 2, 0, ?, ?)
    IN_NAME     DB  10, 0, 10 DUP(0)    ;输入的姓名存储在这里
    IN_PWD      DB  6, 0, 6 DUP(0)      ;输入的密码存储在这里
    IN_GOOD     DB  10, 0, 10 DUP(0)    ;输入的商品名称存储在这里
    MAIN_BOSS   DB  'USER: PENG ZC',0AH,'$'
    MAIN_CUS    DB  'USER: CUSTOMER',0AH,'$'
    MAIN_GOOD   DB  'GOOD: ','$'
    MAIN_CHOOSE DB  'Please Enter 1-9 to choose the function: ',0AH,'$'
    MAIN_FUNCS  DB  '1.Login/Relogin', 0AH
                DB  '2.Find a certain good & show data',0AH
                DB  '3.Purchase',0AH
                DB  '4.Calculate the recomendation (500000 times)',0AH
                DB  '5.Rank',0AH
                DB  '6.Change the data of goods',0AH
                DB  '7.Move the environment',0AH
                DB  '8.Show the offset address of CS',0AH
                DB  '9.Quit',0AH,'$'
    NUM_INPUT        DB 0AH,'Please Input The num:$'
    NAME_INPUT       DB 0AH,'Please Input The Name:$'
    PWD_INPUT        DB 0AH,'Please Input The Password:$'
    GOODS_INPUT      DB 0AH,'Please Input The Goods Name:$'
    LOGIN_FAIL       DB 0AH,'Login Failed!',0AH,'$'
    LOGIN_SUCCESS    DB 0AH,'Login In Successful!',0AH,'$'
    SUCCESS          DB 0AH,'Successful!',0AH,'$'
    FAILED           DB 0AH,'Failed!',0AH,'$'
    RECOMENDATION    DB 0AH,'New recomendation: ', '$'
DATA   ENDS

CODE  SEGMENT USE16
    ASSUME CS:CODE,DS:DATA,SS:STACK
START: 
    MOV AX, DATA
    MOV DS, AX
    JMP CUSTOMER
MAIN_START:
    MOV AH, 2
    MOV DX, 0AH
    INT 21H
    CMP AUTH, 1
    JE  PRINT_BOSS
    JNE PRINT_CUSTOMER
;老板模式
PRINT_BOSS:
    MOV AH, 9
    MOV DX, OFFSET MAIN_BOSS
    INT 21H
    JMP MAIN_MENU
;客人模式
PRINT_CUSTOMER:
    MOV AH, 9
    MOV DX, OFFSET MAIN_CUS
    INT 21H
    JMP MAIN_MENU
;输出主菜单
MAIN_MENU:
    MOV AH, 9
    MOV DX, OFFSET MAIN_GOOD
    INT 21H
;输出当前GOOD地址（十六进制）并换行
    MOV CX, 4
    MOV BX, GOOD
PRINT_GOOD:
    ROL BX, 4
    MOV DX, BX
    AND DX, 0FH
    CMP DX, 9H
    JBE DIGITAL_GOOD
    JMP ALPHA_GOOD
DIGITAL_GOOD:    ;数字
    ADD DX, '0'
    MOV AH, 2
    INT 21H
    DEC CX 
    JNZ PRINT_GOOD
    JMP PRINT_GOOD_END
ALPHA_GOOD:      ;字母
    SUB DX, 0AH
    ADD DX, 'A'
    MOV AH, 2
    INT 21H
    DEC CX 
    JNZ PRINT_GOOD
    JMP PRINT_GOOD_END
PRINT_GOOD_END:    
    MOV AH, 2
    MOV DX, 'H'
    INT 21H
    MOV DX, 0AH
    INT 21H
;输出剩余菜单项
    MOV AH, 9
    MOV DX, OFFSET MAIN_CHOOSE
    INT 21H
    MOV DX, OFFSET MAIN_FUNCS
    INT 21H
    MOV DX, OFFSET NUM_INPUT
    INT 21H
    ;判断输入1-9
    MOV AH, 1
    INT 21H
    ;输出一个换行符
    MOV AH, 2 
    MOV DX, 0AH
    INT 21H
    CMP AL, '1'
    JE  INPUTNAME
    CMP AL, '2'
    JE  FINDGOOD
    CMP AL, '3'
    JE  PURCHASE
    CMP AL, '4'
    JE  RECOMEND
    CMP AL, '5'
    JE  RANK
    CMP AL, '6'
    JE  CHANGEDATA
    CMP AL, '7'
    JE  MOVEENVIR
    CMP AL, '8'
    JE  ADDRDS
    CMP AL, '9'
    JE  QUIT
    JMP MAIN_START
;输入名字
INPUTNAME:
    MOV AH, 9
    MOV DX, OFFSET NAME_INPUT
    INT 21H
    MOV DX, OFFSET IN_NAME
    MOV AH, 10
    INT 21H
    MOV SI, OFFSET BNAME
    MOV DI, OFFSET IN_NAME+2
    MOV CX, 10
    JNE CHECKNAME
;检查名字是否正确，如果正确则输入密码，否则以客人身份返回主菜单
CHECKNAME:
    MOV AL, [SI]
    CMP (AL), [DI]
    JNE CUSTOMER
    INC SI
    INC DI
    DEC CX
    JZ  INPUTPWD
    JNZ CHECKNAME
;输入密码
INPUTPWD:
    MOV AH, 9
    MOV DX, OFFSET PWD_INPUT
    INT 21H
    MOV DX, OFFSET IN_PWD
    MOV AH, 10
    INT 21H
    MOV SI, OFFSET BPASS
    MOV DI, OFFSET IN_PWD+2
    MOV CX, 6
    JNE CHECKPWD
;检查密码是否正确，如果正确则以老板身份返回主菜单，否则以客人身份返回主菜单
CHECKPWD:
    MOV AL, [SI]
    CMP (AL), [DI]
    JNE CUSTOMER
    INC SI
    INC DI
    DEC CX
    JZ  BOSS
    JNZ CHECKPWD
BOSS:
    MOV AH, 9
    MOV DX, OFFSET LOGIN_SUCCESS
    INT 21H
    MOV AUTH, 1
    JMP MAIN_START
CUSTOMER:
    MOV AH, 9
    MOV DX, OFFSET LOGIN_FAIL
    INT 21H
    MOV AUTH, 0
    JMP MAIN_START
;查找指定商品并显示信息（显示信息还未做）
FINDGOOD:
    MOV AH, 9
    MOV DX, OFFSET GOODS_INPUT
    INT 21H
    MOV AH, 10
    MOV DX, OFFSET IN_GOOD
    INT 21H
    MOV SI, OFFSET GA1
    MOV DX, SI
    MOV CL, N
FIND_LOOP:
    MOV CH, 10
    MOV DI, OFFSET IN_GOOD+2
FIND_COMPARE:
    MOV AL, [SI]
    CMP (AL),[DI]
    JNE FIND_CHANGE
    INC SI
    INC DI
    DEC CH
    JZ  FIND_SUCCESS
    JNZ FIND_COMPARE
FIND_CHANGE:
    ADD DX, 21
    MOV SI, DX
    DEC CL
    JZ  FAIL
    JNZ FIND_LOOP
FIND_SUCCESS:
    MOV GOOD, DX
    MOV AH, 9
    MOV DX, OFFSET SUCCESS
    INT 21H
    JMP MAIN_START
;下订单，如果GOOD地址为0则返回主菜单
PURCHASE:
    MOV SI, GOOD
    MOV AL, [SI]
    CMP (AL), 0
    JE  FAIL
    MOV BX, WORD PTR [SI+15]
    MOV AX, WORD PTR [SI+17]
    CMP AX, BX
    JGE FAIL
    MOV CX, 1
    ADD [SI+17], CX
    MOV AH, 9
    MOV DX, OFFSET SUCCESS
    INT 21H
    JMP TIME_RECOMMEND_START   ;JMP RECOMEND更改
;计算当前GOOD地址商品的推荐度
TIME_RECOMMEND_START:
    ;开始计时
    MOV  AX, 0
    CALL TIMER
    MOV  LOOP_TIMES, 500000
RECOMEND:
    MOV  EAX, LOOP_TIMES
    CMP  EAX, 0
    JE   TIME_RECOMMEND_STOP
    DEC  EAX
    MOV  LOOP_TIMES, EAX
    MOV  SI, GOOD
    MOV  AH, 0
    MOV  AL, [SI+10] ;折扣
    MOV  BX, WORD PTR[SI+13] ;销售价
    IMUL AX, BX      ;AX=销售价*折扣
    CWD
    MOV  BX, 10
    IDIV BX          ;AX=实际销售价格=AX/10(BX)
    MOV  BX, AX      ;BX=实际销售价格
    MOV  AX, WORD PTR[SI+11] ;AX=进货价
    MOV  CX, 128
    IMUL AX, CX
    IDIV BX          ;AX=进货价(AX)*128/实际销售价格(BX)
    MOV  CX, AX      ;CX=进货价(AX)*128/实际销售价格(BX)

    MOV  AX, WORD PTR[SI+17] ;AX=已售数量
    MOV  BX, 64
    IMUL AX, BX
    CWD
    MOV  BX, WORD PTR[SI+15] ;BX=进货数量
    IDIV BX                  ;AX=已售数量*128/进货数量*2
    ADD  AX, CX              ;AX=AX+CX
    MOV  [SI+19], AX
    ;计算结束，输出当前商品推荐度
    MOV AH, 9
    MOV DX, OFFSET RECOMENDATION
    INT 21H
    MOV BX, [SI+19]
    MOV CX, 4
    JMP PRINT_RECOMMEND
;输出当前商品推荐度(十六进制)
PRINT_RECOMMEND:
    ROL BX, 4
    MOV DX, BX
    AND DX, 0FH
    CMP DX, 9H
    JBE DIGITAL_RECO
    JMP ALPHA_RECO
DIGITAL_RECO:    ;数字
    ADD DX, '0'
    MOV AH, 2
    INT 21H
    DEC CX 
    JNZ PRINT_RECOMMEND
    JMP PRINT_RECO_END
ALPHA_RECO:      ;字母
    SUB DX, 0AH
    ADD DX, 'A'
    MOV AH, 2
    INT 21H
    DEC CX 
    JNZ PRINT_RECOMMEND
    JMP PRINT_RECO_END
PRINT_RECO_END:
    MOV AH, 2
    MOV DX, 'H'
    INT 21H
    MOV DX, 0AH
    INT 21H
    JMP RECOMEND   ;JMP MAIN_START更改
;排名
RANK:
    JMP MAIN_START

CHANGEDATA:
    JMP MAIN_START

MOVEENVIR:
    JMP MAIN_START

;输出16进制的CS并换行
ADDRDS:
    MOV CX, 4
    MOV BX, CS
PRINT_CS:
    ROL BX, 4
    MOV DX, BX
    AND DX, 0FH
    CMP DX, 9H
    JBE DIGITAL
    JMP ALPHA
DIGITAL:    ;数字
    ADD DX, '0'
    MOV AH, 2
    INT 21H
    DEC CX 
    JNZ PRINT_CS
    JMP MAIN_START
ALPHA:      ;字母
    SUB DX, 0AH
    ADD DX, 'A'
    MOV AH, 2
    INT 21H
    DEC CX 
    JNZ PRINT_CS
    JMP MAIN_START
;结束计时,输出计算时长
TIME_RECOMMEND_STOP:
    MOV  AX, 1
    CALL TIMER
    JMP MAIN_START
FAIL:
    MOV AH, 9
    MOV DX, OFFSET FAILED
    INT 21H
    JMP MAIN_START

;退出程序
;时间计数器(ms),在屏幕上显示程序的执行时间(ms)
TIMER	PROC
	PUSH  DX
	PUSH  CX
	PUSH  BX
	MOV   BX, AX
	MOV   AH, 2CH
	INT   21H	     ;CH=hour(0-23),CL=minute(0-59),DH=second(0-59),DL=centisecond(0-100)
	MOV   AL, DH
	MOV   AH, 0
	IMUL  AX,AX,1000
	MOV   DH, 0
	IMUL  DX,DX,10
	ADD   AX, DX
	CMP   BX, 0
	JNZ   _T1
	MOV   CS:_TS, AX
_T0:	POP   BX
	POP   CX
	POP   DX
	RET
_T1:	SUB   AX, CS:_TS
	JNC   _T2
	ADD   AX, 60000
_T2:	MOV   CX, 0
	MOV   BX, 10
_T3:	MOV   DX, 0
	DIV   BX
	PUSH  DX
	INC   CX
	CMP   AX, 0
	JNZ   _T3
	MOV   BX, 0
_T4:	POP   AX
	ADD   AL, '0'
	MOV   CS:_TMSG[BX], AL
	INC   BX
	LOOP  _T4
	PUSH  DS
	MOV   CS:_TMSG[BX+0], 0AH
	MOV   CS:_TMSG[BX+1], 0DH
	MOV   CS:_TMSG[BX+2], '$'
	LEA   DX, _TS+2
	PUSH  CS
	POP   DS
	MOV   AH, 9
	INT   21H
	POP   DS
	JMP   _T0
_TS	DW    ?
 	DB    'Time elapsed in ms is '
_TMSG	DB    12 DUP(0)
TIMER   ENDP

QUIT:
    MOV AH, 4CH
    INT 21H
CODE   ENDS
    END  START

