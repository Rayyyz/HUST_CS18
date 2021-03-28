#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<sys/syscall.h>
#include<linux/kernel.h>

int main(int argc,char *argv[]){
	int a=syscall(335,6);
        printf("System call sys_mycall return %d\n",a);
        return 0;
}
