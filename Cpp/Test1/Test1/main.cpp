#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <iostream>
using namespace std;
struct Queue {
    int* const  elems;	   	//elems�����ڴ����ڴ�Ŷ��е�Ԫ��
    const  int  max;	  	//elems��������Ԫ�ظ���max
    int   head, tail;	 	//����ͷhead��βtail���ӿ�head=tail;��ʼhead=tail=0
};
void initQueue(Queue* const p, int m);	//��ʼ��pָ���У��������m��Ԫ��
void initQueue(Queue* const p, const Queue& s); //��s�����ʼ��pָ����
void initQueue(Queue* const p, Queue&& s); //��s�ƶ���ʼ��pָ����
int  number(const Queue* const p);	//����pָ���е�ʵ��Ԫ�ظ���
int  size(const Queue* const p);			//����pָ������������Ԫ�ظ���max
Queue* const enter(Queue* const p, int e);  //��e�����β����������p
Queue* const leave(Queue* const p, int& e); //�Ӷ��׳�Ԫ�ص�e��������p
Queue* const assign(Queue* const p, const Queue& q); //�����s�����в�����p
Queue* const assign(Queue* const p, Queue&& q); //�ƶ���s�����в�����p
char* print(const Queue* const p, char* s);//��ӡpָ������s������s
void destroyQueue(Queue* const p);	 //����pָ��Ķ���

extern const char* TestQueue(int& s);   //����ʵ��һ
int main() {
    int nMark = 0;
    const char* strResult = TestQueue(nMark);
    cout << "ѧ�ţ�U201814755" << endl;
    cout << "���������ӳ�" << endl;
    cout << "ʵ��һ���ԣ�" << strResult << "," << nMark << endl;
    return 0;
}

//��ʼ��pָ���У��������m��Ԫ��
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
//��s�����ʼ��pָ����
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
//��s�ƶ���ʼ��pָ����
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
//����pָ���е�ʵ��Ԫ�ظ���
int  number(const Queue* const p) {
    if (p == nullptr || p->max == 0) return 0;  //��������Ϊ��
    return (p->tail - p->head + p->max) % p->max;
}
//����pָ������������Ԫ�ظ���max
int  size(const Queue* const p) {
    return p->max;
}
//��e�����β����������p
Queue* const enter(Queue* const p, int e) {
    if ((p->tail + 1) % p->max == p->head) 
        throw "Queue is full!";
    p->elems[p->tail] = e;
    p->tail = (p->tail+1) % p->max;
    return p;
}
//�Ӷ��׳�Ԫ�ص�e��������p
Queue* const leave(Queue* const p, int& e) {
    if (p->tail == p->head)
        throw"Queue is empty!";
    e = p->elems[p->head];
    p->head = (p->head + 1) % p->max;
    return p;
}
//�����s�����в�����p
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
//�ƶ���s�����в�����p
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
//��ӡpָ������s������s
char* print(const Queue* const p, char* s) {
    int j = p->head;
    int elem = 0;
    int elem_vec[10] = { -1 }, elem_index = 0;
    int s_index = 0;
    for (int i = 0; i < number(p); i++) {   //����number(p)�Σ��������е����ָ���
        elem = p->elems[j];        //elemΪ��ǰ��
        elem_index = 0;         
        while (elem) {
            elem_vec[elem_index++] = elem%10;       //������ÿλ��ֳ����飨��λ->��λ��
            elem = elem / 10;
        }
        for (int k = elem_index-1; k >=0; k--) {    //���򣨸�λ->��λ������s��
            s[s_index++] = (char)(elem_vec[k] + '0');
        }
        s[s_index++] = ',';     //ÿ����������϶���
        j = (j + 1) % p->max;   //j����������һ����
    }
    s[s_index - 1] = '\0';      //���һ�����Ÿ�Ϊ��ֹ��
    return s;
}
//����pָ��Ķ���
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