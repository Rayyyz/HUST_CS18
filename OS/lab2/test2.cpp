#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/wait.h>
using namespace std;

int semid;     	  	//信号灯定义
int sum = 0;		//累加和，公共变量
int num1=0,num2=0;
bool flag = false;	//表示计算进程是否结束
pthread_t p1,p2,p3;     //线程句柄定义
void P(int semid, int index);
void V(int semid, int index);
void* subp1(void*);          //线程1执行函数定义
void* subp2(void*);          //线程2执行函数定义
void* subp3(void*);          //线程3执行函数定义

//售票主函数
int main()
{
        //创建信号灯
        semid = semget(IPC_PRIVATE,2,IPC_CREAT|0666);
        if(semid==-1)
        {
                cout<<"semid信号灯创建失败！\n";
                exit(0);
        }

        //信号灯赋初值
	semctl(semid,0,SETVAL,1);
        //创建3个线程subp1,subp2,subp3
        if(pthread_create(&p1,NULL,subp1,NULL)!=0){
                cout<<"线程1创建失败!\n ";
        }
        if(pthread_create(&p2,NULL,subp2,NULL)!=0){
                cout<<"线程2创建失败!\n ";
        }
        if(pthread_create(&p3,NULL,subp3,NULL)!=0){
                cout<<"线程3创建失败!\n ";
        }
        //等待线程运行结束
        pthread_join(p1,NULL);
	pthread_join(p2,NULL);
        //删除信号灯
	semctl(semid,0,IPC_RMID);
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

//线程1：计算线程
void* subp1(void*)
{
        for(int i=1; i<=100; i++)
        {
                P(semid,0);
                //计算
		sum = sum + i;
		V(semid,1);
        }
	flag = true;
     	cout<<"计算线程结束，退出。"<<endl;
}
//线程2：打印线程1
void* subp2(void*)
{
        while(flag == false)
        {
                P(semid,1);
                //偶数打印信息
		if(sum%2==0){
			cout<<"打印线程1（偶数）：当前和sum = "<<sum<<endl;
                	num1++;
			V(semid,0);
		}
		else{
			V(semid,1);
		}
        }
        //显示线程1打印总结
	cout << "打印线程1结束，共打印了 "<<num1<<" 个数字。"<<endl;
}
//线程3：打印线程2
void* subp3(void*)
{
        while(flag == false)
        {
                P(semid,1);
                //奇数打印信息
		if(sum%2==1){
			cout<<"打印线程2（奇数）：当前和sum = "<<sum<<endl;
			num2++;
			V(semid,0);
		}
		else{
			V(semid,1);
		}
        }
        //显示线程2打印总结
        cout<< "打印线程2结束，共打印了 "<<num2<<" 个数字。"<<endl;
}
