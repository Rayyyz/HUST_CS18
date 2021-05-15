.386
.MODEL FLAT, C

INCLUDE D:\masm32\include\user32.inc
INCLUDE D:\masm32\include\kernel32.inc
INCLUDELIB  D:\masm32\lib\user32.lib
INCLUDELIB  D:\masm32\lib\kernel32.lib
GOODS	STRUCT				;��Ʒ��Ϣ�ṹ����
	GNAME	DB 10 DUP(0)	;��Ʒ��
	GOFF	DB	?			;�ۿ�
	GIP		DW	?			;������
	GSP		DW	?			;�ۻ���
	GNUM	DW	?			;��������
	GSOLD	DW  ?			;������
	GRECO	DW  ?			;�Ƽ���
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
		GA1		GOODS < "BOOK", 9, 25, 36, 100, 20, 0 >		;N����Ʒ����Ϣ����
		GA2		GOODS < "CUP", 8, 8, 15, 150, 24, 0 >	
		GA3		GOODS < "PEN", 34, 60, 30, 2, 0, 0 >

.CODE
;Ѱ����Ʒ
FIND_G	PROC  FNAME_ADDR:DWORD
	FINDGOOD:
		MOV  ESI, OFFSET GA1
		MOV  EDX, ESI
		MOV  CL, N      ;CL������Ʒ��������
	FIND_LOOP:
		MOV  CH, 10     ;CH������Ʒ���ֱȶ�
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
		MOV  EAX,1;�ҵ�����1
		RET
	FIND_FAIL:
		MOV	 EAX,0;û�ҵ�����0		
		RET
FIND_G ENDP


;�ӳ���3-�¶��������GOOD��ַΪ0�򷵻����˵�
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
		CALL RECOMMEND  ;����������Ʒ���Ƽ��Ȳ����(16����)
	BUY_EXIT:
	    MOV  EAX, 1 ;����0������ɹ�
		RET
	FAIL_EXIT:
		MOV  EAX, 0 ;����1������ʧ��
		RET
BUY_G ENDP


;�ӳ���-�������е���Ʒ�Ƽ���,��Ʒ����N
RECOMMEND PROC	
		MOV   N_LOOP, 0       ;��ʼ��
		MOV   ESI, OFFSET GA1
	CAL_LOOP:
		MOV  BL, N_LOOP       ;��Ʒ�������
		CMP  BL, N
		JE   REC_EXIT
		MOV  AH, 0
		MOV  AL, [ESI+10] ;�ۿ�
		MOV  BX, WORD PTR[ESI+13] ;���ۼ�
		IMUL AX, BX      ;AX=���ۼ�*�ۿ�
		CWD
		MOV  BX, 10
		IDIV BX          ;AX=ʵ�����ۼ۸�=AX/10(BX)
		MOV  BX, AX      ;BX=ʵ�����ۼ۸�
		MOV  AX, WORD PTR[ESI+11] ;AX=������
		MOV  CX, 128
		IMUL AX, CX
		CWD
		IDIV BX          ;AX=������(AX)*128/ʵ�����ۼ۸�(BX)
		MOV  CX, AX      ;CX=������(AX)*128/ʵ�����ۼ۸�(BX)
		MOV  AX, WORD PTR[ESI+17] ;AX=��������
		MOV  BX, 64
		IMUL AX, BX
		CWD
		MOV  BX, WORD PTR[ESI+15] ;BX=��������
		IDIV BX                  ;AX=��������*128/��������*2
		ADD  AX, CX              ;AX=AX+CX
		MOV  [ESI+19], AX
		MOV  AX, [ESI+19]
		MOV  BL, N_LOOP    ;��Ʒ�������
		INC  BL
		MOV  N_LOOP, BL
		ADD  ESI, 21        ;������һ����Ʒ
		JMP  CAL_LOOP
	REC_EXIT:
		RET
RECOMMEND ENDP
	END
