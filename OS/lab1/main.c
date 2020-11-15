#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int pipefd[2];  //创建无名管道。pipefd[0]只用于读；pipefd[1]只用于写
pid_t p1;
pid_t p2;
const int max = 15;
int time = 1;    //记录次数
int time1=0, time2 = 0; //分别记录两个子进程的数量
char message[50];//记录发送的数据
char killed[50] = "Parent Process is Killed!\n";
char killed1[50] = "Child Process 1 is Killed by Parent!\n";
char killed2[50] = "Child Process 2 is Killed by Parent!\n";

void parent(int sig_no);
void child1(void);
void child2(void);
void process1(int sig_no);
void process2(int sig_no);
void sendMessage(void);

int main()
{
        pipe(pipefd);
	//设置软中断信号SIGINT
        signal(SIGINT,parent);
        //创建子进程1,2
        p1 = fork();
        if(p1==0) child1();
        else if((p2=fork())==0) child2();
        else sendMessage();
        //等待子进程1,2退出
        waitpid(p1,NULL,0);
        waitpid(p2,NULL,0);
        //关闭管道
        close(pipefd[0]);
        close(pipefd[1]);
        //打印信息、退出
        printf("%s",killed);
        return 0;
}


//父进程信号处理
void parent(int sig_no)
{
	//发SIGUSR1给子进程1
	kill(p1,SIGUSR1);
	//发SIGUSR2给子进程2
	kill(p2,SIGUSR2);	
	//打印信息,退出
	printf("Parent has sent %d messages!\n",time-1);
	exit(0);
 
}

//子进程1
void child1(void)
{
	char msg1[50];
	//设置信号SIGINT处理
	signal(SIGINT,SIG_IGN);
	signal(SIGUSR1,process1);
	//设置SIGUSR1或2处理
	while(1)
	{
		//从管道接收数据
		read(pipefd[0],msg1,sizeof(msg1));
		//显示数据
		printf("%s",msg1);
		//计数器++
		time1++;
	}

}

//子进程2
void child2(void){
      	char msg2[50];
	//设置信号SIGINT处理
	signal(SIGINT,SIG_IGN);
	signal(SIGUSR2,process2);
        //设置SIGUSR1或2处理
        while(1)
        {
                //从管道接收数据
		read(pipefd[0],msg2,sizeof(msg2));
                //显示数据
		printf("%s",msg2);
                //计数器++
		time2++;
        }
}

//SIGUSR1信号处理
void process1(int sig_no){
	//关闭管道
	close(pipefd[0]);
	close(pipefd[1]);
	//打印信息
	printf("\nChild1 get %d message!\n",time1);
	printf("%s",killed1);
	//退出
	exit(0);
}

//SIGUSR2信号处理
void process2(int sig_no){
        //关闭管道
        close(pipefd[0]);
        close(pipefd[1]);
        //打印信息
        printf("\nChild2 get %d message!\n",time2);
	printf("%s",killed2);
        //退出
        exit(0);
}

void sendMessage(void)
{
	while(time<=max)
	{
       		sprintf(message,"I send you %d time!\n",time);
		write(pipefd[1],message,sizeof(message));
		time++;
	        sleep(1);	//linux的sleep(1)是一秒
	}
	 //发SIGUSR1给子进程1
        kill(p1,SIGUSR1);
        //发SIGUSR2给子进程2
        kill(p2,SIGUSR2);
        //打印信息,退出
        printf("Parent has sent %d messages!\n",time-1);
        exit(0);

}

