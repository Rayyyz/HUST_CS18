//#include "stdafx.h"
#include "stdio.h"

extern "C" int show(char *szMsg);

int main(int argc, char *argv[])
{
	int i = show((char *)"This is a message from main program");
	_asm {
		mov  ecx, 100
L1:		inc  i
		loop L1
	}
	;
	printf("i = %d\n", i);
	return 0;
}
