#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include "headMAT.h"

extern const char* TestMAT(int& s);	//ʵ���Ĳ���
template MAT<int>;
template MAT<long long>;
template MAT<double>;
int main(int argc, char* argv[]) 	//����չmain()������������
{
	
	
	cout << "-----------MAT<int> test------------" << endl;
	MAT<int>   a(1, 2), b(2, 2), c(1, 2);
	char t[2048];
	a[0][0] = 1;			//���Ƶس�ʼ�����������Ԫ��
	a[0][1] = 2; 			//�ȼ��ڡ�*(a.operator[ ](0)+1)=2;�����ȼ��ڡ�*(a[0]+1)=2;��
	cout << "��ʼ��a��" << endl;
	cout << a.print(t);				//��ʼ�����������þ���
	b[0][0] = 3; 	b[0][1] = 4;		//����T* const operator[ ](int r)��ʼ������Ԫ��
	b[1][0] = 5; 	b[1][1] = 6;
	cout << "��ʼ��b��" << endl;
	cout << b.print(t);
	c = a * b;						//���Ծ���˷�����
	cout << "c=a*b��" << endl;
	cout << c.print(t);
	cout << "a+c��" << endl;
	cout << (a + c).print(t);		//���Ծ���ӷ�����
	c = c - a;						//���Ծ����������
	cout << "c=c-a��" << endl;
	cout << c.print(t);
	c += a;							//���Ծ���+=������
	cout << "c+=a��" << endl;
	cout << c.print(t);
	c = ~b;							//���Ծ���ת������
	cout << "c=~b��" << endl;
	cout << c.print(t); 

	
	cout << "-----------MAT<long long> test------------" << endl;
	MAT<long long>   a1(1, 2), b1(2, 2), c1(1, 2);
	char t1[2048];
	a1[0][0] = 12348;			//���Ƶس�ʼ�����������Ԫ��
	a1[0][1] = 254912; 			//�ȼ��ڡ�*(a.operator[ ](0)+1)=2;�����ȼ��ڡ�*(a[0]+1)=2;��
	cout << "��ʼ��a��" << endl;
	cout << a1.print(t1);				//��ʼ�����������þ���
	b1[0][0] = 32300; 	b1[0][1] = 4090;		//����T* const operator[ ](int r)��ʼ������Ԫ��
	b1[1][0] = 541299; 	b1[1][1] = 6564;
	cout << "��ʼ��b��" << endl;
	cout << b1.print(t1);
	c1 = a1 * b1;						//���Ծ���˷�����
	cout << "c=a*b��" << endl;
	cout << c1.print(t1);
	cout << "a+c��" << endl;
	cout << (a1 + c1).print(t1);		//���Ծ���ӷ�����
	c1 = c1 - a1;						//���Ծ����������
	cout << "c=c-a��" << endl;
	cout << c1.print(t1);
	c1 += a1;							//���Ծ���+=������
	cout << "c+=a��" << endl;
	cout << c1.print(t1);
	c1 = ~b1;							//���Ծ���ת������
	cout << "c=~b��" << endl;
	cout << c1.print(t1); 

	cout << "-----------MAT<double> test------------" << endl;
	MAT<double>  a2(1, 2), b2(2, 2), c2(1, 2);
	char t2[2048];
	a2[0][0] = 1.4;		//���Ƶس�ʼ�����������Ԫ��
	a2[0][1] = 4.1; 		//�ȼ��ڡ�*(a.operator[ ](0)+1)=2;�����ȼ��ڡ�*(a[0]+1)=2;��
	cout << "��ʼ��a��" << endl;
	cout << a2.print(t2);				//��ʼ�����������þ���
	b2[0][0] = 3.367; 	b2[0][1] = 2.5;	//����T* const operator[ ](int r)��ʼ������Ԫ��
	b2[1][0] = 5.1; 	b2[1][1] = 5.88;
	cout << "��ʼ��b��" << endl;
	cout << b2.print(t2);
	c2 = a2 * b2;						//���Ծ���˷�����
	cout << "c=a*b��" << endl;
	cout << c2.print(t2);
	cout << "a+c��" << endl;
	cout << (a2 + c2).print(t2);		//���Ծ���ӷ�����
	c2 = c2 - a2;						//���Ծ����������
	cout << "c=c-a��" << endl;
	cout << c2.print(t2);
	c2 += a2;							//���Ծ���+=������
	cout << "c+=a��" << endl;
	cout << c2.print(t2);
	c2 = ~b2;							//���Ծ���ת������
	cout << "c=~b��" << endl;
	cout << c2.print(t2);

	cout << "\n-----------All test------------" << endl;
	int nMark = 0;
	const char* strResult = TestMAT(nMark);
	cout << "ѧ�ţ�U201814755" << endl;
	cout << "���������ӳ�" << endl;
	cout << "ʵ���Ĳ��ԣ�" << strResult << "," << nMark << endl;
	
	return 0;
}
