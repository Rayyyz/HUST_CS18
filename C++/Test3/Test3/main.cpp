#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "queue.h"
using namespace std;

class STACK : public QUEUE {
    QUEUE q;
public:
    STACK(int m);         //��ʼ��ջ�������2m-2��Ԫ��
    STACK(const STACK& s);         	//��ջs�����ʼ��ջ
    STACK(STACK&& s)noexcept;     	//��ջs�ƶ�������ʼ��ջ
    int size()const noexcept;		//����ջ��������2m
    operator int() const noexcept;	//����ջ��ʵ��Ԫ�ظ���
    STACK& operator<<(int e); 	    //��e��ջ�������ص�ǰջ
    STACK& operator>>(int& e);     	//��ջ��e�������ص�ǰջ
    STACK& operator=(const STACK& s);	//�����ֵ�����ر���ֵջ
    STACK& operator=(STACK&& s)noexcept;//�ƶ���ֵ�����ر���ֵջ
    char* print(char* b)const noexcept;	//��ջ�׵�ջ����ӡջԪ�� 
    ~STACK()noexcept;	              	//����ջ
};

extern const char* TestSTACK(int& s);  //����ʵ����
int main() {
    int nMark = 0;
    const char* strResult = TestSTACK(nMark);
    cout << "ѧ�ţ�U201814755" << endl;
    cout << "���������ӳ�" << endl;
    cout << "ʵ�������ԣ�" << strResult << "," << nMark << endl;
    return 0;
}

//��ʼ��ջ�������2m-2��Ԫ��
STACK::STACK(int m):q(m), QUEUE(m){
    return;
}
//��ջs�����ʼ��ջ
STACK::STACK(const STACK& s):QUEUE(s),q(s.q) {
    return;
}
//��ջs�ƶ�������ʼ��ջ
STACK::STACK(STACK&& s)noexcept: QUEUE((QUEUE&&)s),q((QUEUE&&)s.q) {
    return;
}

//����ջ��������2m
int STACK::size()const noexcept {
    int q1MaxSize = q.size();
    int q2MaxSize = QUEUE::size();
    return q1MaxSize + q2MaxSize;
}

//����ջ��ʵ��Ԫ�ظ���
STACK::operator int() const noexcept {
    int q1Num = q.operator int();
    int q2Num = QUEUE::operator int();
    return q1Num + q2Num;
}

//��e��ջ�������ص�ǰջ
//e�����1��������У����������1��ǰ�������ˣ��������2,�������2Ҳ�����򷵻ء�ջ������
STACK& STACK::operator<<(int e) {
    int q1Num = QUEUE::operator int();
    int q2Num = q.operator int();   
    int q1MaxSize = QUEUE::size();
    int q2MaxSize = q.size();
    if (q1Num + 1 < q1MaxSize) {
        QUEUE::operator<<(e);
        return *this;
    }
    if (q2Num + 1 >= q2MaxSize) {
        throw "STACK is full!";
    }
    else {
        q.operator<<(e);
    }
    return *this;
}

//��ջ��e�������ص�ǰջ
STACK& STACK::operator>>(int& e) {

    int q1Num = QUEUE::operator int();  //Ĭ�ϻ���Ķ���Ϊ��
    int q2Num = q.operator int();
    int q1MaxSize = QUEUE::size();
    int q2MaxSize = q.size();
    if (q1Num == 0)
        throw"STACK is empty!";
    if (q2Num) {    //�������2�����ݣ������ȳ�ջ����2
        int* elem = new int[q2Num];
        for (int i = 0; i < q2Num - 1; i++) {
            q.operator>>(elem[i]);
        }
        q.operator>>(e);
        for (int i = 0; i < q2Num - 1; i++) {
            q.operator<<(elem[i]);
        }
    }
    else {           //�����ջ����1������
        int *elem = new int[q1Num];
        for (int i = 0; i < q1Num-1; i++) {
            QUEUE::operator>>(elem[i]);
        }
        QUEUE::operator>>(e);
        for (int i = 0; i < q1Num - 1; i++) {
            QUEUE::operator<<(elem[i]);
        }        
    }
    return *this;
}

//�����ֵ�����ر���ֵջ
STACK& STACK::operator=(const STACK& s) {
    QUEUE::operator=(s);
    q.operator=(s.q);
    return *this;
}

//�ƶ���ֵ�����ر���ֵջ
STACK& STACK::operator=(STACK&& s)noexcept {
    QUEUE::operator=((QUEUE&&)s);
    q.operator=((QUEUE&&)s.q);
    return *this;
}

//��ջ�׵�ջ����ӡջԪ��
char* STACK::print(char* b)const noexcept {
    QUEUE::print(b);    //print�����Ա�ʵ���������s_index�ĳ�ʼֵΪstrlen(s)
    q.print(b);
    return b;
}

//����ջ
STACK::~STACK()noexcept {
    q.~QUEUE();
    QUEUE::~QUEUE();
    return;
}