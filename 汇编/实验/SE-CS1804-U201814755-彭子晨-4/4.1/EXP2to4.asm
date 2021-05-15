NAME    Fun2to4  ;子功能2-4模块,包括查找商品、显示商品信息、购买、显示推荐度等子程序
                 ;编写者：彭子晨
EXTRN   PRINT_H:NEAR, ATOI:NEAR, F2TO10:NEAR, GA1:BYTE, GOOD:WORD, N:ABS
PUBLIC  FIND, SHOW, BUY, RECOMMEND
.386
INCLUDE MACRO.lib
STACK  SEGMENT USE16 PARA STACK 'STACK'
STACK  ENDS
DATA   SEGMENT USE16 PARA PUBLIC 'DATA'
    N_LOOP           DW  0                   ;用于循环的变量
    IN_GOOD          DB  10, 0, 10 DUP(0)    ;输入的商品名称存储在这里
    GOODS_INPUT      DB 0AH,'Please Input The Goods Name:$'
    RECOMENDATION    DB 0AH,'New recomendation: ', '$'
    SUCCESS          DB 0AH,'Successful!',0AH,'$'
    FAILED           DB 0AH,'Failed!',0AH,'$'
DATA   ENDS

CODE  SEGMENT USE16 PARA PUBLIC 'CODE'
    ASSUME CS:CODE,DS:DATA,SS:STACK

;子程序2.1-查找指定商品
FIND PROC
FINDGOOD:
    SENTENCE  GOODS_INPUT
    MOV  AH, 10
    MOV  DX, OFFSET IN_GOOD
    INT  21H
    MOV  SI, OFFSET GA1
    MOV  DX, SI
    MOV  CL, N      ;CL用于商品数量计数
FIND_LOOP:
    MOV  CH, 10     ;CH用于商品名字比对
    MOV  DI, OFFSET IN_GOOD+2
FIND_COMPARE:
    MOV  AL, [SI]
    CMP  (AL),[DI]
    JNE  FIND_CHANGE
    INC  SI
    INC  DI
    DEC  CH
    JZ   FIND_SUCCESS
    JNZ  FIND_COMPARE
FIND_CHANGE:
    ADD  DX, 21
    MOV  SI, DX
    DEC  CL
    JNZ  FIND_LOOP
    SENTENCE FAILED
    JMP  FIND_EXIT
FIND_SUCCESS:
    MOV  GOOD, DX
    SENTENCE  SUCCESS
    CALL SHOW
FIND_EXIT:
    RET
FIND ENDP

;子程序2.2-显示GOOD地址的商品信息
SHOW PROC
    MOV  SI, GOOD
    MOV  CX, 10
SHOW_NAME:     ;展示商品名字
    XOR  DX, DX
    MOV  AH, 2
    MOV  DL, BYTE PTR [SI]
    INT  21H
    INC  SI
    LOOP SHOW_NAME
    MOV  DX, ','
    INT  21H
    MOV  SI, GOOD
    XOR  DX, DX
    MOV  DL, BYTE PTR[SI+10] ;输出商品折扣
    CMP  DL, 0AH
    JNE   _OFF19
    MOV  DX, '1';折扣为0的情况
    MOV  AH, 2
    INT  21H
    MOV  DX, '0'
    INT  21H
    MOV  CX, 4
    JMP  SHOW_DATA
_OFF19:        ;折扣为1-9的情况
    ADD  DL, '0'
    MOV  AH, 2
    INT  21H
    MOV  CX, 4
SHOW_DATA:
    MOV  DX, ','
    INT  21H
    MOV  AX, WORD PTR[SI+11]
    CALL F2TO10     ;输出十进制的商品信息
    ADD  SI, 2
    LOOP SHOW_DATA
    CRLF
    RET
SHOW ENDP

;子程序3-下订单，如果GOOD地址为0则返回主菜单
BUY PROC
PURCHASE:
    MOV  SI, GOOD
    MOV  AL, [SI]
    CMP  (AL), 0
    JE   BUY_EXIT
    MOV  BX, WORD PTR [SI+15]
    MOV  AX, WORD PTR [SI+17]
    CMP  AX, BX
    JGE  FAIL_EXIT
    MOV  CX, 1
    ADD  [SI+17], CX
    SENTENCE SUCCESS
    CALL RECOMMEND  ;计算所有商品的推荐度并输出(16进制)
BUY_EXIT:
    RET
FAIL_EXIT:
    SENTENCE FAILED
    RET
BUY ENDP

;子程序4-计算所有的商品推荐度并输出成10进制
RECOMMEND PROC
    PUSH  BX
    PUSH  AX
    PUSH  SI
    MOV   N_LOOP, 0       ;初始化
    MOV   SI, OFFSET GA1
CAL_LOOP:
    MOV  BX, N_LOOP       ;商品计算次数
    CMP  BX, N
    JE   REC_EXIT

    MOV  AH, 0
    MOV  AL, [SI+10] ;折扣
    MOV  BX, WORD PTR[SI+13] ;销售价
    IMUL AX, BX      ;AX=销售价*折扣
    CWD
    MOV  BX, 10
    IDIV BX          ;AX=实际销售价格=AX/10(BX)
    MOV  BX, AX      ;BX=实际销售价格
    MOV  AX, WORD PTR[SI+11] ;AX=进货价
    XOR  AX, 'I'     ;解密
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
    MOV  DX, OFFSET RECOMENDATION
    MOV  AH, 9
    INT  21H
    MOV  AX, [SI+19]
    CALL F2TO10        ;输出推荐度
    MOV  BX, N_LOOP    ;商品计算次数
    INC  BX
    MOV  N_LOOP, BX
    ADD  SI, 21        ;计算下一个商品
    JMP  CAL_LOOP
REC_EXIT:
    POP  SI
    POP  AX
    POP  BX
    RET
RECOMMEND ENDP


CODE   ENDS
    END
