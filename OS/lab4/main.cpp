#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void printdir(char* dir, int depth);
int main(int argc, char *argv[]){
	if(argc!=2)
    	{
        	printf("main参数中没有路径！\n");
        	return 0;
    	}
	printdir(argv[1], 0);
	return 0;
}


void printdir(char* dir, int depth)
{
	DIR* dp;
	struct dirent* entry;
	struct stat statbuf;
	if((dp=opendir(dir))==NULL)//打开dir目录不成功
	{
		//打印出错信息
		cout<<"打开"<<dir<<"目录时出错！\n";
		//返回
		return ;
	}
	if(chdir(dir)==-1)	//改变目录不成功
	{
		cout<<"改变目录时出错！\n";
		return ;
	}
	while((entry=readdir(dp))!=NULL)//读到一个目录项
	{
		//以该目录项的名字为参数，调用lstat得到该目录项的相关信息
		int ret = lstat(entry->d_name,&statbuf);
		if(ret!=0) cout<<"获取目录项相关信息失败！\n";
		if((statbuf.st_mode&S_IFMT) == S_IFDIR){	//是目录
			//如果目录项名字是".."或"."，则跳过
			if(strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".")==0) continue;
			//打印目录项的深度、目录名等信息
			cout<<"\nDIR -  ";
			cout<<"DEPTH:"<<setw(4)<<left<<depth<<"  ";
                        cout<<"SIZE:"<<setw(8)<<left<<statbuf.st_size<<"  ";
                        cout<<"NAME:"<<setw(20)<<left<<entry->d_name<<"  ";
                        cout<<"TIME:"<<4+ctime(&statbuf.st_atime);
			//递归调用printdir,打印子目录的信息，其中depth+4
			printdir(entry->d_name,depth+4);
		}
		else{	//是文件。打印文件深度、文件名等信息
			cout<<"FILE - ";						 	 				cout<<"DEPTH:"<<setw(4)<<left<<depth<<"  ";
                        cout<<"SIZE:"<<setw(8)<<left<<statbuf.st_size<<"  ";
                        cout<<"NAME:"<<setw(20)<<left<<entry->d_name<<"  ";
                        cout<<"TIME:"<<4+ctime(&statbuf.st_atime);
		}
	}	
	//返回父目录
	chdir("..");
	//关闭目录项
	closedir(dp);
	return ;
}
