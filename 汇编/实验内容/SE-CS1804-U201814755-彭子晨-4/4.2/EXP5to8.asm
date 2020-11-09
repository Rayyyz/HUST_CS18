NAME    Fun5to8  ;子功能5-8模块,包括排行（未做）、改变商品信息、迁移商店运行环境、显示CS内容等子程序
                 ;编写者：彭子晨
EXTRN   PRINT_H:NEAR, ATOI:NEAR, F2TO10:NEAR, AUTH:BYTE, GOOD:WORD, N:ABS
PUBLIC  RANK, CHANGEDATA, JUDGE, MOVEENVIR, ADDRCS, ADDRSS, OLD_INT, GET_TIME
.386
INCLUDE MACRO.lib
STACK  SEGMENT USE16 PARA STACK 'STACK'
STACK  ENDS
DATA   SEGMENT USE16 PARA PUBLIC 'DATA'
    IN_OFF      DB  3, 0, 3 DUP(0)     ;输入的商品折扣（字符形式，需要转换）
    IN_BUY      DB  5, 0, 5 DUP(0)     ;输入的进货价   
    IN_SELL     DB  5, 0, 5 DUP(0)     ;输入的销售价
    IN_NUM      DB  5, 0, 5 DUP(0)     ;输入的进货总数
    BEFORE_DATA      DB 0AH,'BEFORE: ', '$'
    OFF_INPUT        DB 0AH,'OFF persent(0~10): $'
    INPRICE_INPUT    DB 0AH,'InPrice(0~9999): $'
    SELLPRICE_INPUT  DB 0AH,'SellPrice(0~9999): $'
    NUMBER_INPUT     DB 0AH,'Number(0~9999): $'
    SET_SUCCESS      DB 0AH,'New08H set successful!',0AH,'$' 
DATA   ENDS    

DATA1  SEGMENT USE16 PARA PUBLIC 'DATA1'  
    STACKBAK         DB 200 DUP(0)   ;与堆栈段同样大小的空间，用于环境切换
DATA1  ENDS

CODE  SEGMENT USE16 PARA PUBLIC 'CODE'
    ASSUME CS:CODE,DS:DATA,SS:STACK
    
;子程序-排名(该功能还未实现)
RANK  PROC
    RET
RANK  ENDP

;子程序-更改商品信息
CHANGEDATA PROC
    CMP  AUTH, 1
    JNZ  CG_EXIT
    SENTENCE BEFORE_DATA
    CRLF
    MOV  SI, GOOD
INPUTDATA:  ;显示"折扣：x>“
    SENTENCE OFF_INPUT
    MOV  DH, 0
    MOV  AH, 2
    MOV  DL, BYTE PTR [SI+10]
    CMP  DL, 0AH
    JE   OFF10  
    MOV  AH, 2  ;折扣为1-9
    ADD  DL, '0'   
    INT  21H
    JMP  OFFIN
OFF10:          ;折扣为10
    MOV  AH, 2
    MOV  DX, '1'
    INT  21H
    MOV  DX, '0'
    INT  21H
OFFIN:
    MOV  DX, '>'
    INT  21H
    MOV  AH, 10     ;输入折扣
    MOV  DX, OFFSET IN_OFF
    INT  21H
    MOV  DI, OFFSET IN_OFF
    CALL JUDGE      ;判断输入是否有误，有误AL=0,重新输入
    CMP  AL, 0
    JE   INPUTDATA
    CMP  IN_OFF+2, 0DH     ;若输入为回车，则无变化
    JE   BUYIN             ;跳到下一个输入
    MOV  DI, OFFSET IN_OFF ;更换信息
    CALL ATOI
    MOV  [SI+10], AL
BUYIN:
    SENTENCE INPRICE_INPUT
    MOV  AX, WORD PTR [SI+11] ;转换成十进制
    CALL F2TO10
    MOV  AH, 2
    MOV  DX, '>'
    INT  21H
    MOV  AH, 10      ;输入进货价
    MOV  DX, OFFSET IN_BUY
    INT  21H
    MOV  DI, OFFSET IN_BUY
    CALL JUDGE      ;判断输入是否有误
    CMP  AL, 0
    JE   BUYIN
    CMP  IN_BUY+2, 0DH     ;若输入为回车，则无变化
    JE   SELLIN            ;跳到下一个输入
    MOV  DI, OFFSET IN_BUY ;更换信息
    CALL ATOI
    MOV  [SI+11], AX
SELLIN:
    SENTENCE SELLPRICE_INPUT
    MOV  AX, WORD PTR [SI+13] ;转换成十进制
    CALL F2TO10
    MOV  AH, 2
    MOV  DX, '>'
    INT  21H
    MOV  AH, 10      ;输入销售价
    MOV  DX, OFFSET IN_SELL
    INT  21H
    MOV  DI, OFFSET IN_SELL
    CALL JUDGE      ;判断输入是否有误
    CMP  AL, 0
    JE   SELLIN
    CMP  IN_SELL+2, 0DH     ;若输入为回车，则无变化
    JE   NUMIN              ;跳到下一个输入
    MOV  DI, OFFSET IN_SELL ;更换信息
    CALL ATOI
    MOV  [SI+13], AX
NUMIN:
    SENTENCE NUMBER_INPUT
    MOV  AX, WORD PTR [SI+15] ;转换成十进制
    CALL F2TO10
    MOV  AH, 2
    MOV  DX, '>'
    INT  21H
    MOV  AH, 10      ;输入买入数量
    MOV  DX, OFFSET IN_NUM
    INT  21H
    MOV  DI, OFFSET IN_NUM
    CALL JUDGE      ;判断输入是否有误
    CMP  AL, 0
    JE   NUMIN
    CMP  IN_NUM+2, 0DH     ;若输入为回车，则无变化
    JE   CG_EXIT           ;跳出
    MOV  DI, OFFSET IN_NUM ;更换信息
    CALL ATOI
    MOV  [SI+15], AX
CG_EXIT:
    RET
CHANGEDATA ENDP

;子程序-判断输入(偏移地址DI)是否有误，AL=0为有误，否则无误
JUDGE PROC
    PUSH BX
    PUSH CX
    XOR  CX, CX
    MOV  CL, BYTE PTR [DI+1]
    ADD  DI, 2
    XOR  BX, BX
    CMP  BYTE PTR [DI], 0DH
    JE   TRUE
LOP1:
    MOV  BL, BYTE PTR [DI]
    CMP  BL, 0DH
    JE   TRUE
    CMP  BX, '9'
    JG   FALSE
    CMP  BX, '0'
    JL   FALSE
    INC  DI
    LOOP LOP1
TRUE:
    MOV  AL, 1
    POP  CX
    POP  BX
    RET
FALSE:
    MOV  AL, 0
    POP  CX
    POP  BX
    RET
JUDGE ENDP
    COUNT            DB 18           ;“滴答”计数
    TIME_SEC         DB '3','0'      ;设定切换的时间-秒
    TIMEGET_SEC      DB ?,?          ;读取的时间-秒
    OLD_INT          DW 0,0          ;新程序中使用的变量，用于存放旧中断矢量
    STACK_FLAG       DB 0            ;用于记录目前的堆栈段，0为STACK,1为STACKTAK

;子程序-迁移环境
MOVEENVIR PROC
    PUSH DS
    PUSH CS        ;初始化（中断处理程序的安装）
    POP  DS
    OR   OLD_INT, 0     ;判断是否安装中断处理程序
    JNZ  MOV_EXIT       ;已安装则返回主菜单
    MOV  AX, 3508H      ;获取原08H的中断矢量
    INT  21H            ;系统功能调用35H的入口/出口
    MOV  OLD_INT, BX
    MOV  OLD_INT+2, ES
    MOV  DX, OFFSET NEW08H
    MOV  AX, 2508H      ;设置新08H的中断矢量
    INT  21H
    POP  DS             ;还原DS
    MOV  DX, OFFSET SET_SUCCESS     ;打印“安装成功”
    MOV  AH, 9
    INT  21H
    RET
MOV_EXIT:
    POP  DS
    RET
MOVEENVIR ENDP

;子程序-中断处理程序，新的INT 08H的代码，按指定时间执行信息迁移
NEW08H PROC
    PUSHF
    CALL DWORD PTR CS:OLD_INT   ;执行旧的中断处理程序
    DEC  CS:COUNT
    JZ   DISP
    IRET        ;未计满，返回
DISP:
    MOV  CS:COUNT, 18
    STI             ;开中断
    PUSHA           ;保护现场 
    PUSH DS
    MOV  AX, CS     ;将DS指向CS
    MOV  DS, AX      
    CALL GET_TIME   ;获取当前时间,比较和设定秒数是否一致
    POP  DS         ;恢复DS
    MOV  AX, WORD PTR CS:TIME_SEC
    CMP  AX, WORD PTR CS:TIMEGET_SEC
    JNE  NEW08_EXIT
    CMP  CS:STACK_FLAG, 0  ;若时间一致则开始迁移
    JE   STACK_C1
    JMP  STACK_C2

STACK_C1:           ;STACK->STACKTAK
    MOV  CX, 200    ;迁移程序,大小为200
    MOV  AX, DATA1  ;修改数据段首址为DATA1
    MOV  DS, AX
    MOV  SI, 0      ;迁移起始堆栈段
    MOV  DI, OFFSET STACKBAK  ;迁移目的数据段
C1_LOOP:
    CMP  CX, 0      ;CX为零说明迁移结束
    JZ   C1_CG
    MOV  AL, SS:[SI]  ;逐字节复制转移
    MOV  DS:[DI], AL
    INC  SI
    INC  DI
    DEC  CX
    JMP  C1_LOOP
C1_CG:
    MOV  AX, DATA1  ;转移段首址
    MOV  SS, AX
    MOV  CS:STACK_FLAG, 1
    JMP  NEW08_EXIT

STACK_C2:           ;STACKTAK->STACK
    MOV  AX, STACK  ;转移堆栈段首址为STACK
    MOV  SS, AX
    MOV  AX, DATA1  ;修改数据段首址为DATA1
    MOV  DS, AX
    MOV  CX, 200    ;迁移程序,大小为200
    MOV  SI, OFFSET STACKBAK    ;迁移起始数据段
    MOV  DI, 0      ;迁移目的堆栈段
C2_LOOP:
    CMP  CX, 0
    JZ   C2_CG
    MOV  AL, DS:[SI]
    MOV  SS:[DI], AL
    INC  SI
    INC  DI
    DEC  CX
    JMP  C2_LOOP
C2_CG:
    MOV  CS:STACK_FLAG, 0
NEW08_EXIT:
    MOV  AX, DATA   ;DS恢复成DATA段首址
    MOV  DS, AX
    POPA            ;恢复现场
    IRET            ;中断返回
NEW08H ENDP

;从CMOS芯片中读取当前时钟的分秒信息，放到对应变量中
GET_TIME PROC
    MOV  AL, 0      ;读取“秒”信息
    OUT  70H, AL
    JMP  $+2
    IN   AL, 71H
    MOV  AH, AL
    AND  AL, 0FH
    SHR  AH, 4
    ADD  AX, 3030H  ;转换成对应的ASCII码
    XCHG AH, AL     ;高位在前显示
    MOV  WORD PTR TIMEGET_SEC, AX ;存到TIMEGET_SEC中
    RET
GET_TIME ENDP


;子程序-输出16进制的CS并换行
ADDRCS  PROC
    MOV  CX, 4
    MOV  BX, CS
    CALL PRINT_H
    RET
ADDRCS  ENDP

;子程序-输出16进制的SS并换行
ADDRSS  PROC
    MOV  CX, 4
    MOV  BX, SS
    CALL PRINT_H
    RET
ADDRSS  ENDP

CODE   ENDS
    END
