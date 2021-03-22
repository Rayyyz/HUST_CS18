//**实现效果
//cp dir1/a.doc dir2 表示将dir1下的a.doc文件复制到dir2目录下
//cp dir1 dir2 表示将dir1及其dir1下所包含的文件复制到dir2下
//cp dir1/ dir2 表示将dir1下的文件复制到dir2,不包括dir1

//**测试命令行
//gcc -o 1-1 1-1.c
//./1-1 AA BB
//./1-1 AA/ BB
//./1-1 AA/yu12/bsh.txt BB

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

#define BUF_SIZE 1024
#define PATH_SIZE 512
#define FILENAME_SIZE 50
#define DIR_SIZE 20

char* getFolderName(char* filePath);
int is_dir(char* path);
int endwith(char* s,char c);
void copy(char* src, char* des);
void copyFileToFolder(char* src,char *des);
void copyFolderToFolder(char* src,char *des);
void copyFile(char* src,char *des);

/*主函数*/
int main(int argc,char *argv[]){
	if(argc != 3){
		printf("输入参数格式有误：\'./1-1 源文件路径 目标路径\'\n");
		exit(1);
	}
	char* srcPath=argv[1];//取用户输入的第一个参数
	char* desPath=argv[2];//取用户输入的第二个参数

	copy(srcPath,desPath);//进行文件夹的拷贝
	return 0;
}

/*拷贝函数*/
void copy(char* src, char* des){
	printf("src: %s\ndes: %s\n",src,des);
	if(endwith(src,'/')){
		//printf("mode:1-目录/\n");
		//如果src是目录下的所有文件
		copyFolderToFolder(src,des);
	}
	else if(is_dir(src) && !endwith(src,'.')){
		//printf("mode:2-目录\n");
		//如果src是个目录同时并不以.结尾(防止死循环)
		char* desPath = (char*)malloc(PATH_SIZE);
		strcpy(desPath,des);
		strcat(desPath,"/");
		strcat(desPath,getFolderName(src));
		strcat(desPath,"/");
		//复制文件夹-》文件夹
		copyFolderToFolder(src,desPath);
	}
	else if(!endwith(src,'.')){	//如果src是个单文件
		//printf("mode:3-单文件\n");
		//在目标路径下复制相同的文件
		char* desPath = (char*)malloc(PATH_SIZE);
		strcpy(desPath,des);
		strcat(desPath,"/");
		strcat(desPath,getFolderName(src));
		//复制文件-》文件夹
		copyFile(src,desPath);
	}
}

/*文件夹-》文件夹*/
void copyFolderToFolder(char* src,char *des){
	//如果目标文件夹不存在则用mkdir创建文件夹
	if(!opendir(des)){
		if(mkdir(des,0777)){
			printf("创建文件夹失败！");
		};
	}
	
	//srcPath为'src',desPath为'des'
	char *srcPath = (char*)malloc(PATH_SIZE);
	strcpy(srcPath,src);
	char *desPath = (char*)malloc(PATH_SIZE);
	strcpy(desPath,des);

	//遍历文件目录
	struct dirent* ptr;
	DIR* dir = opendir(srcPath);
	while(ptr = readdir(dir)){
		//清空srcPath和desPath
		memset(srcPath,0,sizeof(srcPath));
		strcpy(srcPath,src);
		char* fileSrcPath = (char*)malloc(PATH_SIZE);
		char* fileDesPath = (char*)malloc(PATH_SIZE);
		//加入目录‘/文件名’
		if(!endwith(srcPath,'/')){
			strcpy(fileSrcPath,srcPath);
			strcat(fileSrcPath,"/");
		}
		else{
			strcpy(fileSrcPath,srcPath);
		}

		if(!endwith(desPath,'/')){
			strcpy(fileDesPath,desPath);
			strcat(fileDesPath,"/");
		}
		else{
			strcpy(fileDesPath,desPath);
		}
		strcat(fileSrcPath,ptr->d_name);
		strcat(fileDesPath,ptr->d_name);
		if(is_dir(fileSrcPath) && !endwith(fileSrcPath,'.')){
			//如果是目录并不以.结尾（不是/.或/..）
			copyFolderToFolder(fileSrcPath,fileDesPath);//进行递归调用
		}
		else if(!endwith(fileSrcPath,'.')){//*debug*如果不判断直接用else会导致..和.目录在这里被复制
			//不是目录
			copyFile(fileSrcPath,fileDesPath);//复制文件
		}
	}
}


/*文件-》文件*/
void copyFile(char* src,char *des){
	char buf[BUF_SIZE];
	FILE *fin,*fout;		//文件的读取和写入
	if((fin=fopen(src,"r"))==NULL){
		printf("源文件%s打开失败！\n",src);
		exit(1);
	}
	if((fout=fopen(des,"w"))==NULL){
		printf("目标文件%s打开失败！\n",des);
		exit(1);
	}
	int len;
	//从源文件中读取数据，先放入缓存区中，再从缓存区写入目标文件
	while((len=fread(buf,1,sizeof(buf),fin))>0){
		fwrite(buf,1,len,fout);
	}
	fclose(fout);
	fclose(fin);
	printf("复制%s到%s成功！\n",src,des);
}

/*通过文件夹路径获取文件夹名字*/
char* getFolderName(char* filePath ){
	char *p=strrchr(filePath, '/');//倒序查找字符出现的位置，返回地址
	char *filename = (char*)malloc(FILENAME_SIZE);
	if(!p)	//*debug*如果目录为‘AA’没有‘/’的情况下，路径名就是文件名
		sscanf(filePath, "%s", filename);
	else
		sscanf(p+1, "%s", filename);//格式化字符串

	return filename;
}

/*判断是否是目录*/
int is_dir(char* path){
	struct stat st;
	stat(path,&st);
	if(S_ISDIR(st.st_mode)){
		return 1;
	}
	else{
		return 0;
	}
}

/*字符串处理函数*/
int endwith(char* s,char c){//用于判断字符串结尾是否为“/”
	if(s[strlen(s)-1]==c){
		return 1;
	}
	else{
		return 0;
	}
}


