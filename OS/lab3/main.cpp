#include <iostream>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

const int BUF_SIZE = 10;//定义环形缓冲区总大小

union semun{
	int val;		//用于SETVAL
	struct semid_ds *buf;	//用于IPC_SET
	unsigned short *array;	//用于SETALL
	struct seminfo *__buf;	//用于IPC_INFO
};

struct Share{
	int iput,iget;      //环形缓冲区的放入位置、取出位置
	char buf[BUF_SIZE];    //缓冲区
}*sharebuf;
union semun arg;
struct sembuf sem;
pid_t pr,pw;        //进程
int shmid;          //共享内存标识符
int semid;          //信号灯

void P(int semid, int index);
void V(int semid, int index);
void* gettxt(void);
void* puttxt(void);
int main()
{
	//创建共享内存组
	shmid = shmget((key_t)123,sizeof(struct Share),IPC_CREAT|0666);
	if(shmid == -1){
		cout<<"共享内存创建失败！\n";
		exit(0);
	}
	
	sharebuf = (struct Share*)shmat(shmid,0,0);
	if(sharebuf==(void*)(-1)){
		cout<<"缓冲区创建失败！\n";
		exit(0);
	}
	sharebuf->iput = 0;	//初始化
	sharebuf->iget = 0;

	//创建信号灯
	//信号灯0：控制读写信号灯
	//信号灯1：初始num=NUM_SIZE，缓冲区空闲数据数
	//信号灯2：初始num=0,缓冲区已有数据数
	semid = semget((key_t)456,3,IPC_CREAT|0666);
	if(semid == -1)	{
		cout<<"信号灯集创建失败！\n";
		exit(0);
	}
	//信号灯赋初值
	arg.val = 1;
	if(semctl(semid,0,SETVAL,arg)<0){
		cout<<"信号灯0创建失败！\n";
		exit(0);
	}
	arg.val = BUF_SIZE;
	if(semctl(semid,1,SETVAL,arg)<0){
                cout<<"信号灯1创建失败！\n";
                exit(0);
        }
	arg.val = 0;	
	if(semctl(semid,2,SETVAL,arg)<0){
                cout<<"信号灯2创建失败！\n"; 
                exit(0);
        }

	//创建两个进程readbuf、writebuf
	if((pr = fork())==0){		//进程1：readbuf
		cout<<"get created\n";
		gettxt();
	}
	else if((pw = fork())==0){	//进程2：writebuf
		cout<<"put created\n";
		puttxt();
	}
	//主进程main执行
	//等待两个进程运行结束
        waitpid(pr,NULL,0);
        waitpid(pw,NULL,0);
	//删除信号灯
        semctl(semid,3,IPC_RMID,arg);
      	//删除共享内存组
        shmctl(shmid,IPC_RMID,NULL);

	cout<<"OVER!\n";
	return 0;
}

void P(int semid, int index)
{
        struct sembuf sem;
        sem.sem_num = index;
        sem.sem_op = -1;
        sem.sem_flg = 0;        //操作标记：0或IPC_NOWAIT等
        semop(semid,&sem,1);   //1:表示执行命令的个数
        return;
}

void V(int semid, int index)
{
        struct sembuf sem;
        sem.sem_num = index;
        sem.sem_op = 1;
        sem.sem_flg = 0;  //操作标记：0或IPC_NOWAIT等
        semop(semid,&sem,1);   //1:表示执行命令的个数
        return;
}

void* gettxt(void){
	FILE* fget = NULL;
	//****写文件内容到缓冲区
        fget=fopen("input.txt","r");
	if(fwrite==NULL){
		cout<<"get: 打开input.txt文件时发生错误！\n";
		exit(0);
	}
	char ch;
	int count = 0;
	while(1){
		ch = fgetc(fget);
		//P(semid,0);
		P(semid,1);
		sharebuf->buf[sharebuf->iput]=ch;
		sharebuf->iput = (sharebuf->iput+1)%BUF_SIZE;
		V(semid,2);
		//V(semid,0);
		if(ch==EOF) break;
		count++;
		//if(count%5==0) cout<<"put.cpp: 5 char写入\n";
	}
	//**写入完毕
	fclose(fget);
	cout<<"get: 从input.txt读取了"<<count<<"个字符并写入缓存区。\n";
	cout<<"get: 写入缓存区结束，文件已读取完毕。\n";
	exit(0);
}

void* puttxt(void){
	FILE* fput=NULL;
        fput=fopen("output.txt","w");
	if(fput==NULL){
		cout<<"put: 打开output.txt文件时发生错误！\n";
		exit(0);
	}
	//读取文件内容到缓冲区
	char ch;
	int count = 0;

	while(1){
		//P(semid,0);
		P(semid,2);
		ch = sharebuf->buf[sharebuf->iget];
		sharebuf->iget = (sharebuf->iget+1)%BUF_SIZE;
		V(semid,1);
		//V(semid,0);
		if(ch==EOF) break;
		fputc(ch,fput);
		count++;
		//if(count%5==0) cout<<"put: 5 char写入\n";
	}
	//
	fclose(fput);
	cout<<"put: 读取了"<<count<<"个字符并写入output.txt。\n";
	cout<<"put: 读取缓存区结束，文件已写入完毕。\n";
	exit(0);
}

