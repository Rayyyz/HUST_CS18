//使用双向链表维护LRU特性,双向链表可以使删除节点的复杂度为O（1）
//使用哈希表保证能够快速访问缓存中数据
#include "cachelab.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "malloc.h"

//定义LRU缓存
typedef struct LRUCache
{
    int groupNum; //缓存有几组
    int lineNum;  //每组有几行
    Group **groups;
} LRUCache;

//缓存组
typedef struct Group
{
    int tag;         //组号
    int lineNum;     //行数
    int curSize;     //实际节点个数
    Block **hashMap; //哈希表
    Block *linkHead; //链表头
    Block *linkTail; //链表尾
} Group;

//缓存单元
typedef struct Block
{
    int tag;   //组号
    long data; //数据

    struct Block *LinkPrev; //链表前一个元素
    struct Block *LinkNext; //链表后一个元素
    struct Block *HashPrev; //哈希链表前一个元素
    struct Block *HashNext; //哈希链表后一个元素
} Block;

//函数声明
LRUCache *createLRUCache(int groupnum, int linenum);          //创建缓存
Block *createBlock(int groupnum, long data);                  //创建缓存单元
Block *deleteLinkBlock(LRUCache *cache, Block *delBlock);     //删除链表缓存单元
int insertLinkBlock(LRUCache *cache, Block *newBlock);        //插入链表缓存单元
Block *findBlock(LRUCache *cache, long data);                 //查询缓存单元
void insertHashBlock(LRUCache *cache, Block *newBlock);       //插入哈希表缓存单元
void deleteHashBlock(LRUCache *cache, Block *delBlock);       //删除哈希表缓存单元
void updateLRUCache(LRUCache *cache, Block *b);               //更新缓存
int visitData(LRUCache *cache, long data);                    //在缓存内访问数据
void printCache(LRUCache *cache);                             //打印缓存数据
void help();                                                  //帮助文档
void calculateAddr(char *fileLine, long *memAddr, int *size); //获得内存地址和字节数
void execCache(int v, int s, int E, int b, FILE *fp, int *hit, int *miss, int *eviction);
void accessData(LRUCache *cache, long addr, int *hit, int *miss, int *eviction); //访问数据，统计命中率

int main(int argc, char **argv)
{
    int hit_count = 0, miss_count = 0, eviction_count = 0;
    int v, s, E, b, t;
    FILE *fp;

    for (int i = 1; i < argc; i++)
    {
        char *arg = *(argv + i);
        char *nextarg = *(argv + i + 1);
        if (strcmp(arg, "-v") == 0)
        {
            v = 1;
        }
        else if (strcmp(arg, "-s") == 0)
        {
            s = atoi(nextarg);
            i++;
        }
        else if (strcmp(arg, "-E") == 0)
        {
            E = atoi(nextarg);
            i++;
        }
        else if (strcmp(arg, "-b") == 0)
        {
            b = atoi(nextarg);
            i++;
        }
        else if (strcmp(arg, "-t") == 0)
        {
            fp = fopen(nextarg, "r");
            i++;
        }
        else if (strcmp(arg, "-h") == 0)
        {
            help();
        }
    }
    if (s == 0 || E == 0 || b == 0 || fp == NULL)
    {
        printf("缺少必要的参数。");
        help();
        exit(1);
    }
    execCache(v, s, E, b, fp, &hit_count, &miss_count, &eviction_count);
    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}

//操作数据
void accessData(LRUCache *cache, long addr, int *hit, int *miss, int *eviction)
{
    int tag = (int)(addr % cache->groupNum);
    Group *group = cache->groups[tag];
    for (int i = 0; i < cache->lineNum; i++)
    {
        int ret = visitData(cache, addr);
        if (ret == 1) //假设命中
            *hit += 1;
        else if (group->curSize == cache->lineNum)
        { //未命中且缓存已满
            *miss += 1;
            *eviction += 1;
        }
        else
        { //未命中且缓存不满
            *miss += 1;
        }
    }
}

//执行缓存测试
void execCache(int v, int s, int E, int b, FILE *fp, int *hit, int *miss, int *eviction)
{
    int groupnum = pow(2, s);
    int blocksize = pow(2, b);
    LRUCache *cache = createLRUCache(groupnum, E);

    char *fileLine = NULL; //文件行指针
    size_t len = 0;        //每行的长度
    ssize_t read;

    while (read = getline(&fileLine, &len, fp) != -1)
    { //逐行分析
        char *printLine = fileLine;
        printLine[strlen(printLine) - 1] = "\0";
        printf("%s", printLine);
        if (fileLine[0] == 'I') //忽略I指令
            continue;

        long addr;                             //内存地址
        char op = fileLine[1];                 //指令，M，L，S
        int size;                              //访问的内存字节数量
        calculateAddr(fileLine, &addr, &size); //得到内存地址和访问的字节数量

        switch (op)
        {
        case 'M':
            //数据修改
            accessData(cache, addr, hit, miss, eviction);
            accessData(cache, addr, hit, miss, eviction);
            break;
        case 'S':
            //数据存储
            accessData(cache, addr, hit, miss, eviction);
            break;
        case 'L':
            //数据装载
            accessData(cache, addr, hit, miss, eviction);
            break;
        default:
            printf("不能识别到S/M/L指令");
            break;
        }
    }
}

//计算出一行中要访问的主存地址以及字节长度
void calculateAddr(char *fileLine, long *memAddr, int *size)
{
    int addrlen = 0;
    while (fileLine[3 + addrlen] != ',')
        addrlen++;
    char *addr = (char *)malloc(addrlen * sizeof(char));
    int i = 0;
    do
    {
        addr[i] = fileLine[i + 3]; //地址位
        i++;
    } while (i < addrlen);
    *(addr + addrlen) = '\0';          //拼接字符串
    *memAddr = strtol(addr, NULL, 16); //将地址由char数组转换成16进制数
    free(addr);
}

//创建缓存
LRUCache *createLRUCache(int groupnum, int linenum)
{
    LRUCache *cache = (LRUCache *)malloc(sizeof(LRUCache));
    cache->groupNum = groupnum;
    cache->lineNum = linenum;
    for (int i = 0; i < groupnum; i++)
    {
        cache->groups[i] = (Group *)malloc(sizeof(Group));
        cache->groups[i]->curSize = 0;
        cache->groups[i]->hashMap = (Block *)malloc(sizeof(Block) * linenum);
        cache->groups[i]->lineNum = linenum;
        cache->groups[i]->linkHead = NULL;
        cache->groups[i]->linkTail = NULL;
        cache->groups[i]->tag = i;
    }
    return cache;
}

//创建缓存单元
Block *createBlock(int groupnum, long data)
{
    Block *block = (Block *)malloc(sizeof(Block));

    block->data = data;
    block->tag = (int)(data & (groupnum - 1));
    block->HashPrev = NULL;
    block->HashNext = NULL;
    block->LinkNext = NULL;
    block->LinkPrev = NULL;
    return block;
}

/*-----链表函数实现-----*/
//删除节点,返回已删除的节点
Block *deleteLinkBlock(LRUCache *cache, Block *delBlock)
{
    int tag = delBlock->tag;
    Group *group = cache->groups[tag];
    if (group->curSize == 0)
        return;
    if (group->curSize == 1)
    { //假设链表只剩当前一个节点
        group->linkHead = group->linkTail = NULL;
    }
    else if (group->linkHead == delBlock)
    { //假设删除的是头节点
        group->linkHead = delBlock->LinkNext;
        group->linkHead->LinkPrev = NULL;
    }
    else if (group->linkTail == delBlock)
    { //假设删除的是尾节点
        group->linkTail = delBlock->LinkPrev;
        group->linkTail->LinkNext = NULL;
    }
    else
    { //删除的节点在中间
        delBlock->LinkPrev->LinkNext = delBlock->LinkNext;
        delBlock->LinkNext->LinkPrev = delBlock->LinkPrev;
    }
    group->curSize--;
    return delBlock;
}

//插入链表,返回是否有淘汰
int insertLinkBlock(LRUCache *cache, Block *newBlock)
{
    int evic = 0;
    int tag = newBlock->tag;
    Group *group = cache->groups[tag];
    if (group->curSize == cache->lineNum)
    { //如果缓存容量已满，则淘汰表尾的数据
        deleteLinkBlock(group, group->linkTail);
        evic = 1;
    }
    if (group->curSize == 0)
    { //如果链表为空
        group->linkHead = group->linkTail = newBlock;
    }
    else
    { //插入表头
        newBlock->LinkNext = group->linkHead;
        newBlock->LinkPrev = NULL;
        group->linkHead->LinkPrev = newBlock;
        group->linkHead = newBlock;
    }
    group->curSize++;
    return evic;
}

/*-----哈希表函数实现-----*/

//利用hashMap查找对应数据
Block *findBlock(LRUCache *cache, long data)
{
    int tag = (int)(data & (cache->groupNum - 1));
    int pos = (int)(data & (cache->lineNum - 1));
    Group *group = cache->groups[tag];
    if (group->hashMap[pos])
    {
        Block *b = group->hashMap[pos];
        while (b)
        {
            if (b->data == data)
                return b;
            b = b->HashNext;
        }
    }
    return NULL;
}

//插入数据-哈希表
void insertHashBlock(LRUCache *cache, Block *newBlock)
{
    int tag = (int)((newBlock->data) & (cache->groupNum - 1));
    int pos = (int)((newBlock->data) & (cache->lineNum - 1));
    Group *group = cache->groups[tag];
    Block *b = group->hashMap[pos];

    if (b != NULL)
    { //如果当前槽内已有其他数据项，则另新增项的hashNext为已有项
        newBlock->HashNext = b;
        b->HashPrev = newBlock;
    }
    //将数据放入哈希表
    group->hashMap[pos] = newBlock;
}

//删除数据-哈希表
void deleteHashBlock(LRUCache *cache, Block *delBlock)
{
    int tag = (int)((delBlock->data) & (cache->groupNum - 1));
    Group *group = cache->groups[tag];
    if (group->curSize == 0)
        return;

    int pos = (int)((delBlock->data) & (cache->lineNum - 1));
    Block *b = group->hashMap[pos];
    while (b)
    {
        if (b->data == delBlock->data)
        {
            if (b->HashPrev == NULL)
            { //如果b为链表第一个节点
                group->hashMap[pos] = b->HashNext;
                group->hashMap[pos]->HashPrev = NULL;
            }
            else
            { //b不为链表第一个节点
                b->HashPrev->HashNext = b->HashNext;
            }
            if (b->HashNext)
            { //b不为链表最后一个节点
                b->HashNext->HashPrev = b->HashPrev;
            }
        }
        b = b->HashNext;
    }
}

//更新Cache，如果访问到到链表中已存在的数据，将其更新到链表表头（哈希表不需要变化）
void updateLRUCache(LRUCache *cache, Block *b)
{
    deleteLinkBlock(cache, b);
    insertLinkBlock(cache, b);
}

//命中返回1,miss返回0
int visitData(LRUCache *cache, long data)
{
    //利用哈希表查找
    Block *b = findBlock(cache, data);
    //数据已经在缓存中，更新数据并返回true
    if (b != NULL)
    {
        updateLRUCache(cache, b);
        return 1;
    }
    //数据不在缓存中，需要新建缓存插入链表表头
    Block *newBlock = createBlock(cache->groupNum, data);
    int tag = (int)(data & (cache->groupNum - 1));
    Group *group = cache->groups[tag];
    deleteHashBlock(cache, group->linkTail);
    insertHashBlock(cache, newBlock);
    insertLinkBlock(cache, newBlock);

    return 0;
}

//打印Cache中的内容
void printCache(LRUCache *cache)
{
    if (cache == NULL)
        return;
    printf("LRUCache\ngroups:%d\nlines:%d\n", cache->groupNum, cache->lineNum);
    for (int i = 0; i < cache->groupNum; i++)
    {
        printf("Tag:%d\n", i);
        Group *group = cache->groups[i];
        Block *b = group->linkHead;
        while (b)
        {
            printf("%d\n", b->data);
            b = b->LinkNext;
        }
    }
}

//帮助文档
void help()
{
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