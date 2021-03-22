//执行三个并发进程
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

int main(){
	pid_t p0;
	pid_t p1;
	pid_t p2;
	
	
	if((p0=fork())==0){
		execlp("./p0",0);
	}
	else{
		if((p1=fork())==0){
			execlp("./p1",0);	
		}
		else{
			if((p2=fork())==0){
				execlp("./p2",0);	
			}
			else{
				wait(&p0);
				wait(&p1);
				wait(&p2);
			}
		}
	}

}
