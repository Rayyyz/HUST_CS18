NAME    main  ;程序主体，包括主界面显示、各功能选择、登录子程序、通用函数
              ;编写者：彭子晨
EXTRN   FIND:NEAR, SHOW:NEAR, BUY:NEAR, RECOMMEND:NEAR, RANK:NEAR, CHANGEDATA:NEAR, JUDGE:NEAR, MOVEENVIR:NEAR, ADDRCS:NEAR, ADDRSS:NEAR, GET_TIME:NEAR, OLD_INT:WORD
PUBLIC  PRINT_H, ATOI, F2TO10, AUTH, GOOD, GA1, N
.386
INCLUDE MACRO.lib
STACK  SEGMENT USE16 PARA STACK 'STACK'
    DB 200 DUP(0)
STACK  ENDS
DATA   SEGMENT USE16 PARA PUBLIC 'DATA'
    BNAME   DB  'PENG ZC', 0DH, 2 DUP(0) ;老板姓名
    CNAME   DB  'CUSTOMER',2 DUP(0)
    BPASS   DB  'AbCdE',0DH     ;密码,5位,0结尾,进行了加密处理
    AUTH    DB  0               ;当前登录状态,0表示顾客状态
    GOOD    DW  0               ;当前浏览商品地址
    C1      EQU 1
    C2      EQU 2
    N       EQU 10              ;商品总数
    SNAME   DB  'SHOP',0        ;网店名称,用0结束
    GA1     DB  'GOOD1', 0DH, 4 DUP(0), 10    ;商品名称及折扣
            DW  15 XOR 'I',56,78,2,0          ;进货价,销售价,进货总数,已售数量,推荐度
    GA2     DB  'GOOD2', 0DH, 4 DUP(0), 9  ;商品名称及折扣
            DW  8 XOR 'I',30,25,5,64            ;进货价,销售价,进货总数,已售数量,推荐度
    GAN     DB  N-2  DUP('TmpValue', 0DH, 0 XOR 'I', 8, 15, 0, 20, 0, 30, 0, 2, 0, ?, ?)
    IN_NAME     DB  10, 0, 10 DUP(0)    ;输入的姓名存储在这里
    IN_PWD      DB  6, 0, 6 DUP(0)      ;输入的密码存储在这里
    MAIN_BOSS   DB  'USER: PENG ZC',0AH,'$'
    MAIN_CUS    DB  'USER: CUSTOMER',0AH,'$'
    MAIN_GOOD   DB  'GOOD: ','$'
    MAIN_CHOOSE DB  'Please Enter 1-9 to choose the function: ',0AH,'$'
    MAIN_FUNCS  DB  '1.Login/Relogin', 0AH
                DB  '2.Find a certain good & show data',0AH
                DB  '3.Purchase',0AH
                DB  '4.Calculate the recomendation',0AH
                DB  '5.Rank',0AH
                DB  '6.Change the data of goods',0AH
                DB  '7.Move the environment',0AH
                DB  '8.Show the offset address of SS',0AH
                DB  '9.Quit',0AH,'$'
    NUM_INPUT        DB 0AH,'Please Input The num:$'
    NAME_INPUT       DB 0AH,'Please Input The Name:$'
    PWD_INPUT        DB 0AH,'Please Input The Password:$'
    LOGIN_FAIL       DB 0AH,'Login Failed!',0AH,'$' 
    LOGIN_SUCCESS    DB 0AH,'Login In Successful!',0AH,'$'
    Q_QUIT           DB 0AH,'Input Q to exit:$'
    TABLE       DW  LOGIN_1, FIND_2, BUY_3, RECOMMEND_4, RANK_5
                DW  CHANGEDATA_6, MOVEENVIR_7, ADDRSS_8
    TIME_SAVE   DB  0
DATA   ENDS

CODE  SEGMENT USE16 PARA PUBLIC 'CODE'
    ASSUME CS:CODE,DS:DATA,SS:STACK
START: 
    MOV AX, DATA
    MOV DS, AX
    MOV AUTH, 0
BACK:
    CRLF
    CALL MENU
    MOV AH, 1    ;判断输入1-9
    INT 21H
    CRLF
    MOV BL, AL    ;改用地址表方式查找功能
    SUB BL, 30H
    XOR BH, BH    ;将AL转换为数字形式给BX
    DEC BX        ;BX减1
    SHL BX, 1     ;BX*2
    CMP AL, '9'
    JE  QUIT
    JMP TABLE[BX] ;地址表

;1-登录
LOGIN_1:
    CALL LOGIN
    JMP BACK

;2-查找指定商品并显示信息
FIND_2:
    CALL FIND
    JMP BACK

;3-购买商品并计算推荐度
BUY_3:
    CALL BUY
    JMP BACK

;4-所有商品推荐度计算
RECOMMEND_4:
    CALL RECOMMEND
    JMP  BACK

;5-排行
RANK_5:
    CALL RANK
    JMP  BACK

;6-改变商品信息
CHANGEDATA_6:
    CALL CHANGEDATA
    JMP  BACK

;7-改变环境
MOVEENVIR_7:
    CALL MOVEENVIR
M_NEXT:
    MOV  DX, OFFSET Q_QUIT  ;打印“输入Q就退出”
    MOV  AH, 9
    INT  21H
    MOV  AH, 0      ;输入Q退出
    INT  16H
    CMP  AL, 'Q'
    JNE  M_NEXT    ;如果不输入Q则每隔一秒进行循环
    PUSH DS        ;恢复原08H中断矢量   
    PUSH CS
    POP  DS 
    LDS  DX, DWORD PTR CS:OLD_INT
    MOV  AX, 2508H
    INT  21H  
    POP  DS
    JMP  BACK

;8-输出16进制的SS内容
ADDRSS_8:
    CALL ADDRSS
    JMP  BACK

;9-退出程序
QUIT:
    OR   CS:OLD_INT, 0      ;判断是否安装中断处理程序
    JZ   Q_EXIT             ;已安装则恢复原中断矢量,否则直接退出
    PUSH DS
    PUSH CS
    POP  DS 
    LDS  DX, DWORD PTR CS:OLD_INT
    MOV  AX, 2508H
    INT  21H            ;恢复原08H中断矢量
    POP  DS
Q_EXIT:
    MOV  AH, 4CH
    INT  21H


;子程序0-输出主菜单
MENU PROC
    CRLF
    CMP  AUTH, 1
    JE   PRINT_BOSS
    JNE  PRINT_CUSTOMER
PRINT_BOSS:         ;老板模式
    SENTENCE MAIN_BOSS
    JMP  MAIN_MENU
PRINT_CUSTOMER:     ;客人模式
    SENTENCE MAIN_CUS
MAIN_MENU:          ;输出主菜单
    SENTENCE MAIN_GOOD
    MOV  CX, 4      ;输出当前GOOD地址（16进制）
    MOV  BX, GOOD
    CALL PRINT_H 
    SENTENCE MAIN_CHOOSE  ;输出剩余菜单项
    SENTENCE MAIN_FUNCS
    SENTENCE NUM_INPUT
    RET
MENU ENDP

;子程序1-登录
LOGIN  PROC  
INPUTNAME:  ;输入名字
    SENTENCE  NAME_INPUT
    MOV  DX, OFFSET IN_NAME
    MOV  AH, 10
    INT  21H
    MOV  SI, OFFSET BNAME
    MOV  DI, OFFSET IN_NAME+2
    MOV  CX, 10
    JNE  CHECKNAME
CHECKNAME:  ;检查名字是否正确，如果正确则输入密码，否则以客人身份退出
    MOV  AL, [SI]
    CMP  (AL), [DI]
    JNE  CUSTOMER
    INC  SI
    INC  DI
    DEC  CX
    JZ   INPUTPWD
    JNZ  CHECKNAME
INPUTPWD:           ;输入密码
    SENTENCE PWD_INPUT
    MOV  DX, OFFSET IN_PWD
    MOV  AH, 10
    INT  21H
    MOV  SI, OFFSET BPASS
    MOV  DI, OFFSET IN_PWD+2
    MOV  CX, 5  
    PUSH DS         ;反跟踪手法：获取时间,存入TIME_SAVE
    MOV  AX, CS
    MOV  DS, AX
    CALL GET_TIME
    POP  DS
    MOV  WORD PTR TIME_SAVE, AX
CHECKPWD:   ;将密码解密，检查密码是否正确，如果正确则以老板身份退出，否则以客人身份退出
    MOV  AL, [SI]
    CALL SOLVE
    CMP  (AL), [DI]
    JNE  CUSTOMER
    INC  SI
    INC  DI
    DEC  CX
    JZ   BOSS
    JNZ  CHECKPWD
BOSS:
    SENTENCE  LOGIN_SUCCESS
    MOV  AUTH, 1
    JMP  EXIT
CUSTOMER:
    SENTENCE  LOGIN_FAIL
    MOV  AUTH, 0
EXIT:
    RET
LOGIN ENDP

;子程序--输出16进制，寄存器BX中为要转换的值，CX为计数器
;*****************************************
PRINT_H PROC
    PUSH DX ;保留信息
    PUSH AX
    PUSH BX
    PUSH CX
ROLL:
    ROL  BX, 4
    MOV  DX, BX
    AND  DX, 0FH
    CMP  DX, 9H
    JBE  DIGITAL
    JMP  ALPHA
DIGITAL:    ;数字
    ADD  DX, '0'
    MOV  AH, 2
    INT  21H
    DEC  CX 
    JNZ  ROLL
    JMP  PRINTH_EXIT
ALPHA:      ;字母
    SUB  DX, 0AH
    ADD  DX, 'A'
    MOV  AH, 2
    INT  21H
    DEC  CX 
    JNZ  ROLL
    JMP  PRINTH_EXIT
PRINTH_EXIT:
    MOV  AH, 2
    MOV  DX, 'H'
    INT  21H
    CRLF
    POP  CX
    POP  BX
    POP  AX
    POP  DX
    RET
PRINT_H ENDP

;子程序--输入字符转数字,DI记录偏移位置,AX存放结果
ATOI PROC
    PUSH DX
    PUSH CX
    PUSH BX
    XOR  AX, AX  ;清零
    XOR  DX, DX
    XOR  CX, CX
    MOV  BX, 10
    MOV  CL, BYTE PTR [DI+1]
LOOP1:
    MOV  DL, [DI+2] ;把一个字符放到DL
    CMP  DL, 0DH    ;判断是否为回车符
    JE   ATOI_EXIT  
    SUB  DL, '0'    ;变成0~9的数字
    IMUL AX, BX     ;AX原本内容乘10
    ADD  AX, DX
    INC  DI
    LOOP LOOP1
ATOI_EXIT:
    POP  BX
    POP  CX
    POP  DX
    RET
ATOI ENDP

;子程序，做密码干扰用
SOLVE PROC   
    PUSHA
    XOR AX, AX   ;垃圾运算，无意义，干扰用
    MOV CX, 8
    MOV BX, 111H
LOOP_S:
    INC AX
    ADD BX, AX
    XOR BX, AX
    MOV DX, BX
    INC AX
    INC BX
    DEC CX
    JNZ  LOOP_S   ;垃圾运算结束（中间内容可随意修改
    PUSH DS         ;反跟踪手法：获取时间,判断是否人工单步执行
    MOV  AX, CS
    MOV  DS, AX
    CALL GET_TIME
    POP  DS
    CMP  WORD PTR TIME_SAVE, AX ;比较秒数，若为直接执行，则相差在毫秒级，应该相等
    JNE  QUIT                   ;若不同，说明在单步执行，直接退出 
    POPA 
    JMP SOLVE_PASS       ;若不是单步执行，则传到真正的解密函数
    RET
SOLVE ENDP

;子程序--将AL中的加密码进行单字解密
SOLVE_PASS PROC
    CMP AL, 'a'
    JGE Little
    JMP Big
Little:
    SUB AL, 49
    ADD AL, C1
    RET
Big:
    SUB AL, 17
    ADD AL, C2
    RET
SOLVE_PASS ENDP


;子程序--将2进制转换并输出10进制，寄存器AX中为要转换的值,BX为基数10
;*****************************************
F2TO10 PROC
    PUSH DX ;保留信息
    PUSH BX
    PUSH CX
    PUSH SI
    XOR  CX, CX
    MOV  BX, 10 ;进制
_LOP1:
    XOR  DX, DX
    DIV  BX
    PUSH DX
    INC  CX
    OR   AX, AX
    JNZ  _LOP1
_LOP2:
    POP  AX
    CMP  AL, 10
    JB   _L1
    ADD  AL, 7
_L1:
    ADD  AL, 30H
    MOV  AH, 2
    MOV  DL, AL
    INT  21H
    LOOP _LOP2

    POP  SI
    POP  CX
    POP  BX
    POP  DX
    RET
F2TO10 ENDP


CODE   ENDS
    END  START

