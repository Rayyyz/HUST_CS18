#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
extern const char* TestQUEUE(int& s);  //用于实验二

class QUEUE {
    int* const  elems;	    //elems申请内存用于存放队列的元素
    const  int  max;	    //elems申请的最大元素个数为max
    int   head, tail;	 	//队列头head和尾tail，队空head=tail;初始head=tail=0
public:
    QUEUE(int m);		    //初始化队列：最多申请m个元素
    QUEUE(const QUEUE& q); 			//用q深拷贝初始化队列
    QUEUE(QUEUE&& q)noexcept;		//用q移动初始化队列
    virtual operator int() const noexcept;	    //返回队列的实际元素个数
    virtual int size() const noexcept;		    //返回队列申请的最大元素个数max
    virtual QUEUE& operator<<(int e);  	 //将e入队列尾部，并返回当前队列
    virtual QUEUE& operator>>(int& e); 	 //从队首出元素到e，并返回当前队列
    virtual QUEUE& operator=(const QUEUE& q);   //深拷贝赋值并返回被赋值队列
    virtual QUEUE& operator=(QUEUE&& q)noexcept;//移动赋值并返回被赋值队列
    virtual char* print(char* s) const noexcept;//打印队列至s并返回s
    virtual ~QUEUE();	 					    //销毁当前队列
};


int main() {
    int nMark = 0;
    const char* strResult = TestQUEUE(nMark);
    cout << "学号：U201814755" << endl;
    cout << "姓名：彭子晨" << endl;
    cout << "实验二测试：" << strResult << "," << nMark << endl;
    return 0;
}

//初始化队列：最多申请m个元素
QUEUE::QUEUE(int m):elems(new int[m]),max(m) {
    head = 0;
    tail = 0;
    return;
}
//用q深拷贝初始化队列
QUEUE::QUEUE(const QUEUE& q):elems(new int[q.max]),max(q.max),head(q.head),tail(q.tail){
    for (int i = 0; i < q.max; i++) {
        elems[i] = q.elems[i];
    }
    return;
}
//用q移动初始化队列
QUEUE::QUEUE(QUEUE&& q)noexcept :elems(q.elems), max(q.max), head(q.head), tail(q.tail) {
    *(int**)&q.elems = nullptr;
    *(int*)&(q.max) = 0;
    q.head = 0;
    q.tail = 0;
    return;
}


//将e入队列尾部，并返回当前队列
QUEUE& QUEUE::operator<<(int e) {
    if ((tail + 1) % max == head)
        throw "QUEUE is full!";
    elems[tail] = e;
    tail = (tail + 1) % max;
    return *this;
}

//从队首出元素到e，并返回当前队列
QUEUE& QUEUE::operator>>(int& e) {
    if (tail == head)
        throw "QUEUE is empty!";
    e = elems[head];
    head = (head + 1) % max;
    return *this;
}

//深拷贝赋值并返回被赋值队列
QUEUE& QUEUE::operator=(const QUEUE& q){
    if (elems == q.elems) return *this;
    *(int**)&(elems) = (int*)malloc(sizeof(int) * q.max);
    *(int*)&(max) = q.max;
    head = q.head;
    tail = q.tail;
    if (q.elems != nullptr &&  elems != nullptr) {
        for (int i = 0; i < max; i++)
             elems[i] = q.elems[i];
    }
    return *this;
}

//移动赋值并返回被赋值队列
QUEUE& QUEUE::operator=(QUEUE&& q)noexcept {
    if (elems == q.elems) return *this;
    if (elems != nullptr) {
        delete(elems);
    }
    *(int**)&(elems) = q.elems;
    *(int*)&(max) = q.max;
    head = q.head;
    tail = q.tail;
    *(int**)&q.elems = nullptr;
    *(int*)&(q.max) = 0;
    q.head = 0;
    q.tail = 0;
    return *this;
}

//打印队列至s并返回s
char* QUEUE::print(char* s) const noexcept {
    int j = head;
    int elem = 0;
    int elem_vec[10] = { -1 }, elem_index = 0;
    int s_index = 0;
    for (int i = 0; i < (tail-head+max)%max; i++) {   //遍历number(p)次，即队列中的数字个数
        elem = elems[j];        //elem为当前数
        elem_index = 0;
        while (elem) {
            elem_vec[elem_index++] = elem % 10;       //把数字每位拆分成数组（个位->高位）
            elem = elem / 10;
        }
        for (int k = elem_index - 1; k >= 0; k--) {    //反向（高位->低位）输入s中
            s[s_index++] = (char)(elem_vec[k] + '0');
        }
        s[s_index++] = ',';     //每个数后面加上逗号
        j = (j + 1) % max;   //j遍历队列下一个数
    }
    //s[s_index - 1] = '\0';      //最后一个逗号改为终止符
    return s;
}

//销毁当前队列
QUEUE::~QUEUE() {
    if (elems != nullptr)
        delete(elems);
    *(int**)&elems = nullptr;
    *(int*)&max = 0;
    head = 0;
    tail = 0;
    return;
}

//返回队列的实际元素个数
QUEUE::operator int() const noexcept {
    return max != 0 ? (tail - head + max) % max : 0;
}

//返回队列申请的最大元素个数max
int QUEUE::size() const noexcept {
    return max;
}