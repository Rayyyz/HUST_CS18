.386
.model flat, C
.STACK
.CODE
getmax PROC Param1:SDWORD, Param2:SDWORD
    MOV EAX, Param1
    CMP EAX, Param2
    JG EXIT
    MOV EAX, Param2
EXIT:
    RET
getmax  ENDP
    END