.386
;.MODEL FLAT, STDCALL
.model flat, c
 public show
 MessageBoxA PROTO STDCALL :DWORD,:DWORD, :DWORD,:DWORD
 includelib  user32.lib
 includelib  kernel32.lib
.DATA
 szSubMsg  db  "This is sub-function",0
 szTopic   db  "Show(char *szMainMsg)",0
 
.CODE
show	 proc   addrMainMsg:dword
	 invoke MessageBoxA,0,addr szSubMsg,addr szTopic,0
	 invoke MessageBoxA,0,addrMainMsg,addr szTopic,0
	 mov    ax, 5	;·µ»ØÖµ
         RET
show     endp
         end
