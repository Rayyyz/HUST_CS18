#define _GNU_SOURCE
#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>

typedef struct Line{
  int age;       //距离上次访问时长
  int valid;     //有效位（是否有数据使用缓存
  int tag;      //组号
  int* block; 	//块数据
} Line;

typedef struct Group{
  Line* lines; // 每一组有多少行
} Group;

typedef struct Cache{
  int groupNum;    // 每个cache有多少组
  int lineNum;		//每个组有多少行
  Group* groups;
} Cache;

Cache *createCache(int groupNum, int lineNum);
Line createLine(int tag, int blockSize, int memAddr);
void freeCache(Cache* cache);
int calculateAddr(char* fileLine, long* memAddr);
void incAge(Group* group, int linenum);
void visitData(Group* group, int linenum, int tag, int blockSize, long memAddr,int* hit, int* miss, int* eviction);
void execCache(int s, int E, int b, FILE* fp, int v,int* hit, int* miss, int* eviction);
void help();

int main(int argc, char** argv){
    int hit, miss, eviction;
    int v=0,s, E, b, i;
    FILE* fp; 
    
    for (i = 1; i < argc; i++)
    {
        char *arg = *(argv + i);
        char *nextarg = *(argv + i + 1);
        if (strcmp(arg, "-v") == 0){
            v = 1;
        }
        else if (strcmp(arg, "-s") == 0){
            s = atoi(nextarg);
            i++;
        }
        else if (strcmp(arg, "-E") == 0){
            E = atoi(nextarg);
            i++;
        }
        else if (strcmp(arg, "-b") == 0){
            b = atoi(nextarg);
            i++;
        }
        else if (strcmp(arg, "-t") == 0){
            fp = fopen(nextarg, "r");
            i++;
        }
        else if (strcmp(arg, "-h") == 0){
            help();
        }
    }
    execCache(s, E, b, fp, v, &hit, &miss, &eviction);  
    printSummary(hit, miss, eviction);
    return 0;
}
//创建cache
Cache *createCache(int groupNum, int lineNum){
	Cache* cache = (Cache*) malloc(sizeof(Cache));
	cache->groupNum = groupNum;
	cache->lineNum = lineNum;
  	Group* groups = (Group*)malloc(groupNum * sizeof(Group));
  	cache->groups = groups;
  	for(int i = 0; i < groupNum; i++){
      		Line* lines = (Line*) malloc(lineNum * sizeof(Line));
      		for(int j = 0; j < lineNum; j++){
          		lines[j].valid = 0;
      		}
      		groups[i].lines = lines;
  	}
  	return cache;
}

//创建行
Line createLine(int tag, int blockSize, int memAddr){
    Line line;
    line.valid = 1;
    line.age = -1;
    line.tag = tag;
    int* block = (int*) malloc(blockSize * sizeof(int));//根据块大小来定
    int byteNum = memAddr & (blockSize - 1);		//计算地址字节数
    for(int i = 0; i < blockSize; i++){
        block[i] = memAddr - byteNum + i;
    }
    line.block = block;
    return line;
}

//释放Cache
void freeCache(Cache* cache){
    for(int i = 0; i < cache->groupNum; i++){
        for(int j = 0; j < cache->lineNum; j++){
            free(cache->groups[i].lines[j].block);
        }
        free(cache->groups[i].lines);
    }
    free(cache->groups);
    free(cache);
    return;
}
    
//计算出要访问的主存地址以及地址的长度（字节为单位ie
int calculateAddr(char* fileLine, long* memAddr){
    int addrlen = 0;
    while(fileLine[3 + addrlen] != ','){
        addrlen++;
    }
    char* addr = (char*) malloc(addrlen * sizeof(char));
    int i = 0;
    do{
        addr[i] = fileLine[i + 3];
        i++;
    } while(i < addrlen);
    *(addr + addrlen) = '\0';
    *memAddr = strtol(addr, NULL, 16);
    free(addr);
    return addrlen;
}

//将没有命中的行的age++ 
void incAge(Group* group, int linenum){
    for(int i = 0; i < linenum; i++){
        if(group->lines[i].valid == 1){
            group->lines[i].age += 1;
        }
    }
    return;
}

//计算Hit/Miss/Eviction
void visitData(Group* group,int linenum, int tag, int blockSize, long memAddr,int* hit, int* miss, int* eviction){
    int InvalidLine = -1;
    int evictionLine = -1;
    int max_age = 0;
    for(int i = 0; i < linenum; i++){
        if((group->lines[i].valid == 1) && (group->lines[i].tag == tag)){	//区号相同，有效
            *hit +=1;	//命中
            group->lines[i].age = -1;	
            incAge(group, linenum);
            return ;
        } else if((InvalidLine == -1) && (group->lines[i].valid == 0)){		//未命中，记录空闲行
            InvalidLine = i;	
        } else if((group->lines[i].valid == 1) && (group->lines[i].age >= max_age)){	//都不空闲，选出age最大的并替换
            evictionLine = i;	
            max_age = group->lines[i].age;
        }
    }
    *miss += 1;
    if(InvalidLine != -1){
        group->lines[InvalidLine] = createLine(tag, blockSize, memAddr);
        incAge(group, linenum);
    } else{		//把age最大的替换
        *eviction += 1;	
        free(group->lines[evictionLine].block);
        group->lines[evictionLine] = createLine(tag, blockSize, memAddr);
        incAge(group,linenum);
    }
}
                       
//执行Cache测试
void execCache(int s, int E, int b, FILE* fp, int v,int* hit, int* miss, int* eviction){
    *hit = 0;
    *miss = 0;
    *eviction = 0;
    int groupnum = pow(2,s);
    int blockSize = pow(2,b);
    Cache* cache = createCache(groupnum, E);

    char* fileLine = NULL;//文件行指针
    size_t len = 0; //每一个line的长度
    ssize_t read;

    while((read = getline(&fileLine, &len, fp)) != -1){//逐行解析
		if(v==1)
		{
			char* printLine = fileLine;
			printLine[strlen(printLine) - 1] = '\0';
			printf("%s", printLine);
		}
        if(fileLine[0] == 'I') {continue;}
        long memAddr;                          //内存地址
		char op = fileLine[1];                 //指令，M，L，S
		//int size;                            //可忽略。访问的内存字节数量
		int addrlen = calculateAddr(fileLine, &memAddr); //得到内存地址和访问的字节数量
	//组相连地址构成为 addr = （区号tag+组号groupTag-s+块内地址blockSize-b）
        int groupTag = (memAddr >> b) & (groupnum - 1);
        Group* group = &(cache->groups[groupTag]); 
        int maxTag = pow(2,(4 * addrlen) - s - b) - 1;
        int tag = (memAddr >> (s + b)) & maxTag;
        switch (op)
		{
		case 'M':
			//数据修改
			visitData(group,E, tag, blockSize, memAddr, hit, miss, eviction);
			visitData(group,E, tag, blockSize, memAddr, hit, miss, eviction);
			break;
		case 'S':
			//数据存储
			visitData(group,E, tag, blockSize, memAddr, hit, miss, eviction);
			break;
		case 'L':
			//数据装载
			visitData(group,E, tag, blockSize, memAddr, hit, miss, eviction);
			break;
		default:
		    printf("不能识别到S/M/L指令");
		    break;
		}
	}
      
		fclose(fp);
		free(fileLine);
		freeCache(cache);
	
}

//帮助文档
void help(){
    printf("Usage: ./csim-ref [-hv] -s <num> -E <num> -b <num> -t <file>\n"
            "Options:\n"
            "\t-h\tPrint this help message.\n"
            "\t-v\tOptional v flag.\n"
            "\t-s <num>\tNumber of group index bits.\n"
            "\t-E <num>\tNumber of lines per group.\n"
            "\t-b <num>\tNumber of block offgroup bits.\n"
            "\t-t <file>\tTrace file.\n\n"
            "Examples:\n"
            "\tlinux>  ./csim-ref -s 4 -E 1 -b 4 -t traces/yi.file\n"
            "\tlinux>  ./csim-ref -v -s 8 -E 2 -b 4 -t traces/yi.file\n");
}
