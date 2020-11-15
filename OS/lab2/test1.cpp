#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/wait.h>
using namespace std;
int ticket = 100;
int ticket1=0,ticket2=0,ticket3=0;
int semid;     	  	//信号灯定义
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
        semid = semget(IPC_PRIVATE,1,IPC_CREAT|0666);
        if(semid==-1)
        {
                cout<<"semid信号灯创建失败！\n";
                exit(0);
        }
	//即将开始
	cout<<"飞机售票线程开始工作，线程数：3"<<endl;
	cout<<"即将开始工作......"<<endl;
	cout<<"3"<<endl;
	sleep(1);
	cout<<"2"<<endl;
	sleep(1);
	cout<<"1"<<endl;
	sleep(1);
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

//售票线程
void* subp1(void*)
{
        while(ticket>0)//有票
        {
                P(semid,0);
                //打印售票信息
		if(ticket>0)
		{
			ticket--;
			ticket1++;
			cout<<"售票线程1售票，剩余票数："<<ticket<<endl;
		}
		V(semid,0);
        }
        //显示售票总数
     	cout<<"线程1一共售票："<<ticket1<<endl;
}

void* subp2(void*)
{
        while(ticket>0)//有票
        {
                P(semid,0);
                //打印售票信息
                if(ticket>0)
                {
                        ticket--;
                        ticket2++;
                        cout<<"售票线程2售票，剩余票数："<<ticket<<endl;
                }
                V(semid,0);
        }
        //显示售票总数
	cout << "线程2一共售票："<<ticket2<<endl;
}
void* subp3(void*)
{
        while(ticket>0)//有票
        {
                P(semid,0);
                //打印售票信息
		if(ticket>0)
                {
                        ticket--;
                        ticket3++;
                        cout<<"售票线程3售票，剩余票数："<<ticket<<endl;
                }
		V(semid,0);
        }
        //显示售票总数
        cout<< "线程3一共售票："<<ticket3<<endl;
}
