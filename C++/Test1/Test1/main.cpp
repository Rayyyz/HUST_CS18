#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <iostream>
using namespace std;
struct Queue {
    int* const  elems;	   	//elems申请内存用于存放队列的元素
    const  int  max;	  	//elems申请的最大元素个数max
    int   head, tail;	 	//队列头head和尾tail，队空head=tail;初始head=tail=0
};
void initQueue(Queue* const p, int m);	//初始化p指队列：最多申请m个元素
void initQueue(Queue* const p, const Queue& s); //用s深拷贝初始化p指队列
void initQueue(Queue* const p, Queue&& s); //用s移动初始化p指队列
int  number(const Queue* const p);	//返回p指队列的实际元素个数
int  size(const Queue* const p);			//返回p指队列申请的最大元素个数max
Queue* const enter(Queue* const p, int e);  //将e入队列尾部，并返回p
Queue* const leave(Queue* const p, int& e); //从队首出元素到e，并返回p
Queue* const assign(Queue* const p, const Queue& q); //深拷贝赋s给队列并返回p
Queue* const assign(Queue* const p, Queue&& q); //移动赋s给队列并返回p
char* print(const Queue* const p, char* s);//打印p指队列至s并返回s
void destroyQueue(Queue* const p);	 //销毁p指向的队列

extern const char* TestQueue(int& s);   //用于实验一
int main() {
    int nMark = 0;
    const char* strResult = TestQueue(nMark);
    cout << "学号：U201814755" << endl;
    cout << "姓名：彭子晨" << endl;
    cout << "实验一测试：" << strResult << "," << nMark << endl;
    return 0;
}

//初始化p指队列：最多申请m个元素
void initQueue(Queue* const p, int m) {
    //*(Queue**)&p = (Queue*)malloc(sizeof(Queue));
    if (p != nullptr) {
        *(int**)&(p->elems)= (int*)malloc(sizeof(int) * m);  
        *(int*)&(p->max) = m; 
        p->head = 0;
        p->tail = 0;
    }
    return;
}
//用s深拷贝初始化p指队列
void initQueue(Queue* const p, const Queue& s) {
    //*(Queue**)&p = (Queue*)malloc(sizeof(Queue));
    if (p != nullptr) {
        *(int**)&(p->elems) = (int*)malloc(sizeof(int) * s.max);
        *(int*)&(p->max) = s.max;
        p->head = s.head;
        p->tail = s.tail;
        if (s.elems != nullptr && p->elems != nullptr) {
            for (int i = 0; i < p->max; i++)
                p->elems[i] = s.elems[i];
        }        
    }
    return;
}
//用s移动初始化p指队列
void initQueue(Queue* const p, Queue&& s) {
    //*(Queue**)&p = (Queue*)malloc(sizeof(Queue));
    if (p != nullptr) {
        *(int**)&(p->elems) = s.elems;
        *(int*)&(p->max) = s.max;
        p->head = s.head;
        p->tail = s.tail;
        *(int**)&s.elems = nullptr;
        *(int*)&(s.max) = 0;
        s.head = 0;
        s.tail = 0;
    }
    return;
}
//返回p指队列的实际元素个数
int  number(const Queue* const p) {
    if (p == nullptr || p->max == 0) return 0;  //除数不能为零
    return (p->tail - p->head + p->max) % p->max;
}
//返回p指队列申请的最大元素个数max
int  size(const Queue* const p) {
    return p->max;
}
//将e入队列尾部，并返回p
Queue* const enter(Queue* const p, int e) {
    if ((p->tail + 1) % p->max == p->head) 
        throw "Queue is full!";
    p->elems[p->tail] = e;
    p->tail = (p->tail+1) % p->max;
    return p;
}
//从队首出元素到e，并返回p
Queue* const leave(Queue* const p, int& e) {
    if (p->tail == p->head)
        throw"Queue is empty!";
    e = p->elems[p->head];
    p->head = (p->head + 1) % p->max;
    return p;
}
//深拷贝赋s给队列并返回p
Queue* const assign(Queue* const p, const Queue& q) {
    if (p == &q) return p;
    if (p->elems != nullptr && p->elems!=q.elems) {
        free(p->elems);
        *(int**)&p->elems = nullptr;
    }
    if (p != nullptr) {
        *(int**)&(p->elems) = (int*)malloc(sizeof(int) * q.max);
        *(int*)&(p->max) = q.max;
        p->head = q.head;
        p->tail = q.tail;
        if (q.elems != nullptr && p->elems != nullptr) {
            for (int i = 0; i < p->max; i++)
                p->elems[i] = q.elems[i];
        }
    }
    return p;
}
//移动赋s给队列并返回p
Queue* const assign(Queue* const p, Queue&& q) {
    if (p == &q) return p;
    if (p->elems != nullptr && p->elems != q.elems) {
        free(p->elems);
    }
    if (p!=&q && p != nullptr) {
        *(int**)&(p->elems) = q.elems;
        *(int*)&(p->max) = q.max;
        p->head = q.head;
        p->tail = q.tail;
        *(int**)&q.elems = nullptr;
        *(int*)&(q.max) = 0;
        q.head = 0;
        q.tail = 0;
    }
    return p;
}
//打印p指队列至s并返回s
char* print(const Queue* const p, char* s) {
    int j = p->head;
    int elem = 0;
    int elem_vec[10] = { -1 }, elem_index = 0;
    int s_index = 0;
    for (int i = 0; i < number(p); i++) {   //遍历number(p)次，即队列中的数字个数
        elem = p->elems[j];        //elem为当前数
        elem_index = 0;         
        while (elem) {
            elem_vec[elem_index++] = elem%10;       //把数字每位拆分成数组（个位->高位）
            elem = elem / 10;
        }
        for (int k = elem_index-1; k >=0; k--) {    //反向（高位->低位）输入s中
            s[s_index++] = (char)(elem_vec[k] + '0');
        }
        s[s_index++] = ',';     //每个数后面加上逗号
        j = (j + 1) % p->max;   //j遍历队列下一个数
    }
    s[s_index - 1] = '\0';      //最后一个逗号改为终止符
    return s;
}
//销毁p指向的队列
void destroyQueue(Queue* const p) {
    if (p == nullptr) return;
    if (p->elems != nullptr)
        free(p->elems);
    *(int**)&p->elems = nullptr;
    *(int*)&p->max = 0;
    p->head = 0;
    p->tail = 0;
    return;
}