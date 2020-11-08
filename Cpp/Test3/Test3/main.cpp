#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "queue.h"
using namespace std;

class STACK : public QUEUE {
    QUEUE q;
public:
    STACK(int m);         //初始化栈：最多存放2m-2个元素
    STACK(const STACK& s);         	//用栈s深拷贝初始化栈
    STACK(STACK&& s)noexcept;     	//用栈s移动拷贝初始化栈
    int size()const noexcept;		//返回栈的容量即2m
    operator int() const noexcept;	//返回栈的实际元素个数
    STACK& operator<<(int e); 	    //将e入栈，并返回当前栈
    STACK& operator>>(int& e);     	//出栈到e，并返回当前栈
    STACK& operator=(const STACK& s);	//深拷贝赋值并返回被赋值栈
    STACK& operator=(STACK&& s)noexcept;//移动赋值并返回被赋值栈
    char* print(char* b)const noexcept;	//从栈底到栈顶打印栈元素 
    ~STACK()noexcept;	              	//销毁栈
};

extern const char* TestSTACK(int& s);  //用于实验三
int main() {
    int nMark = 0;
    const char* strResult = TestSTACK(nMark);
    cout << "学号：U201814755" << endl;
    cout << "姓名：彭子晨" << endl;
    cout << "实验三测试：" << strResult << "," << nMark << endl;
    return 0;
}

//初始化栈：最多存放2m-2个元素
STACK::STACK(int m):q(m), QUEUE(m){
    return;
}
//用栈s深拷贝初始化栈
STACK::STACK(const STACK& s):QUEUE(s),q(s.q) {
    return;
}
//用栈s移动拷贝初始化栈
STACK::STACK(STACK&& s)noexcept: QUEUE((QUEUE&&)s),q((QUEUE&&)s.q) {
    return;
}

//返回栈的容量即2m
int STACK::size()const noexcept {
    int q1MaxSize = q.size();
    int q2MaxSize = QUEUE::size();
    return q1MaxSize + q2MaxSize;
}

//返回栈的实际元素个数
STACK::operator int() const noexcept {
    int q1Num = q.operator int();
    int q2Num = QUEUE::operator int();
    return q1Num + q2Num;
}

//将e入栈，并返回当前栈
//e入队列1（基类队列），如果队列1当前数量满了，则入队列2,如果队列2也满了则返回“栈已满”
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

//出栈到e，并返回当前栈
STACK& STACK::operator>>(int& e) {

    int q1Num = QUEUE::operator int();  //默认基类的队列为先
    int q2Num = q.operator int();
    int q1MaxSize = QUEUE::size();
    int q2MaxSize = q.size();
    if (q1Num == 0)
        throw"STACK is empty!";
    if (q2Num) {    //如果队列2有数据，则优先出栈队列2
        int* elem = new int[q2Num];
        for (int i = 0; i < q2Num - 1; i++) {
            q.operator>>(elem[i]);
        }
        q.operator>>(e);
        for (int i = 0; i < q2Num - 1; i++) {
            q.operator<<(elem[i]);
        }
    }
    else {           //否则出栈队列1的数据
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

//深拷贝赋值并返回被赋值栈
STACK& STACK::operator=(const STACK& s) {
    QUEUE::operator=(s);
    q.operator=(s.q);
    return *this;
}

//移动赋值并返回被赋值栈
STACK& STACK::operator=(STACK&& s)noexcept {
    QUEUE::operator=((QUEUE&&)s);
    q.operator=((QUEUE&&)s.q);
    return *this;
}

//从栈底到栈顶打印栈元素
char* STACK::print(char* b)const noexcept {
    QUEUE::print(b);    //print函数对比实验二更改了s_index的初始值为strlen(s)
    q.print(b);
    return b;
}

//销毁栈
STACK::~STACK()noexcept {
    q.~QUEUE();
    QUEUE::~QUEUE();
    return;
}