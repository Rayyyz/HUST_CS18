#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
extern const char* TestQUEUE(int& s);  //����ʵ���

class QUEUE {
    int* const  elems;	    //elems�����ڴ����ڴ�Ŷ��е�Ԫ��
    const  int  max;	    //elems��������Ԫ�ظ���Ϊmax
    int   head, tail;	 	//����ͷhead��βtail���ӿ�head=tail;��ʼhead=tail=0
public:
    QUEUE(int m);		    //��ʼ�����У��������m��Ԫ��
    QUEUE(const QUEUE& q); 			//��q�����ʼ������
    QUEUE(QUEUE&& q)noexcept;		//��q�ƶ���ʼ������
    virtual operator int() const noexcept;	    //���ض��е�ʵ��Ԫ�ظ���
    virtual int size() const noexcept;		    //���ض�����������Ԫ�ظ���max
    virtual QUEUE& operator<<(int e);  	 //��e�����β���������ص�ǰ����
    virtual QUEUE& operator>>(int& e); 	 //�Ӷ��׳�Ԫ�ص�e�������ص�ǰ����
    virtual QUEUE& operator=(const QUEUE& q);   //�����ֵ�����ر���ֵ����
    virtual QUEUE& operator=(QUEUE&& q)noexcept;//�ƶ���ֵ�����ر���ֵ����
    virtual char* print(char* s) const noexcept;//��ӡ������s������s
    virtual ~QUEUE();	 					    //���ٵ�ǰ����
};


int main() {
    int nMark = 0;
    const char* strResult = TestQUEUE(nMark);
    cout << "ѧ�ţ�U201814755" << endl;
    cout << "���������ӳ�" << endl;
    cout << "ʵ������ԣ�" << strResult << "," << nMark << endl;
    return 0;
}

//��ʼ�����У��������m��Ԫ��
QUEUE::QUEUE(int m):elems(new int[m]),max(m) {
    head = 0;
    tail = 0;
    return;
}
//��q�����ʼ������
QUEUE::QUEUE(const QUEUE& q):elems(new int[q.max]),max(q.max),head(q.head),tail(q.tail){
    for (int i = 0; i < q.max; i++) {
        elems[i] = q.elems[i];
    }
    return;
}
//��q�ƶ���ʼ������
QUEUE::QUEUE(QUEUE&& q)noexcept :elems(q.elems), max(q.max), head(q.head), tail(q.tail) {
    *(int**)&q.elems = nullptr;
    *(int*)&(q.max) = 0;
    q.head = 0;
    q.tail = 0;
    return;
}


//��e�����β���������ص�ǰ����
QUEUE& QUEUE::operator<<(int e) {
    if ((tail + 1) % max == head)
        throw "QUEUE is full!";
    elems[tail] = e;
    tail = (tail + 1) % max;
    return *this;
}

//�Ӷ��׳�Ԫ�ص�e�������ص�ǰ����
QUEUE& QUEUE::operator>>(int& e) {
    if (tail == head)
        throw "QUEUE is empty!";
    e = elems[head];
    head = (head + 1) % max;
    return *this;
}

//�����ֵ�����ر���ֵ����
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

//�ƶ���ֵ�����ر���ֵ����
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

//��ӡ������s������s
char* QUEUE::print(char* s) const noexcept {
    int j = head;
    int elem = 0;
    int elem_vec[10] = { -1 }, elem_index = 0;
    int s_index = 0;
    for (int i = 0; i < (tail-head+max)%max; i++) {   //����number(p)�Σ��������е����ָ���
        elem = elems[j];        //elemΪ��ǰ��
        elem_index = 0;
        while (elem) {
            elem_vec[elem_index++] = elem % 10;       //������ÿλ��ֳ����飨��λ->��λ��
            elem = elem / 10;
        }
        for (int k = elem_index - 1; k >= 0; k--) {    //���򣨸�λ->��λ������s��
            s[s_index++] = (char)(elem_vec[k] + '0');
        }
        s[s_index++] = ',';     //ÿ����������϶���
        j = (j + 1) % max;   //j����������һ����
    }
    //s[s_index - 1] = '\0';      //���һ�����Ÿ�Ϊ��ֹ��
    return s;
}

//���ٵ�ǰ����
QUEUE::~QUEUE() {
    if (elems != nullptr)
        delete(elems);
    *(int**)&elems = nullptr;
    *(int*)&max = 0;
    head = 0;
    tail = 0;
    return;
}

//���ض��е�ʵ��Ԫ�ظ���
QUEUE::operator int() const noexcept {
    return max != 0 ? (tail - head + max) % max : 0;
}

//���ض�����������Ԫ�ظ���max
int QUEUE::size() const noexcept {
    return max;
}