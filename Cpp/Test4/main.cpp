#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include "headMAT.h"

extern const char* TestMAT(int& s);	//实验四测试
template MAT<int>;
template MAT<long long>;
template MAT<double>;
int main(int argc, char* argv[]) 	//请扩展main()测试其他运算
{
	
	
	cout << "-----------MAT<int> test------------" << endl;
	MAT<int>   a(1, 2), b(2, 2), c(1, 2);
	char t[2048];
	a[0][0] = 1;			//类似地初始化矩阵的所有元素
	a[0][1] = 2; 			//等价于“*(a.operator[ ](0)+1)=2;”即等价于“*(a[0]+1)=2;”
	cout << "初始化a：" << endl;
	cout << a.print(t);				//初始化矩阵后输出该矩阵
	b[0][0] = 3; 	b[0][1] = 4;		//调用T* const operator[ ](int r)初始化数组元素
	b[1][0] = 5; 	b[1][1] = 6;
	cout << "初始化b：" << endl;
	cout << b.print(t);
	c = a * b;						//测试矩阵乘法运算
	cout << "c=a*b：" << endl;
	cout << c.print(t);
	cout << "a+c：" << endl;
	cout << (a + c).print(t);		//测试矩阵加法运算
	c = c - a;						//测试矩阵减法运算
	cout << "c=c-a：" << endl;
	cout << c.print(t);
	c += a;							//测试矩阵“+=”运算
	cout << "c+=a：" << endl;
	cout << c.print(t);
	c = ~b;							//测试矩阵转置运算
	cout << "c=~b：" << endl;
	cout << c.print(t); 

	
	cout << "-----------MAT<long long> test------------" << endl;
	MAT<long long>   a1(1, 2), b1(2, 2), c1(1, 2);
	char t1[2048];
	a1[0][0] = 12348;			//类似地初始化矩阵的所有元素
	a1[0][1] = 254912; 			//等价于“*(a.operator[ ](0)+1)=2;”即等价于“*(a[0]+1)=2;”
	cout << "初始化a：" << endl;
	cout << a1.print(t1);				//初始化矩阵后输出该矩阵
	b1[0][0] = 32300; 	b1[0][1] = 4090;		//调用T* const operator[ ](int r)初始化数组元素
	b1[1][0] = 541299; 	b1[1][1] = 6564;
	cout << "初始化b：" << endl;
	cout << b1.print(t1);
	c1 = a1 * b1;						//测试矩阵乘法运算
	cout << "c=a*b：" << endl;
	cout << c1.print(t1);
	cout << "a+c：" << endl;
	cout << (a1 + c1).print(t1);		//测试矩阵加法运算
	c1 = c1 - a1;						//测试矩阵减法运算
	cout << "c=c-a：" << endl;
	cout << c1.print(t1);
	c1 += a1;							//测试矩阵“+=”运算
	cout << "c+=a：" << endl;
	cout << c1.print(t1);
	c1 = ~b1;							//测试矩阵转置运算
	cout << "c=~b：" << endl;
	cout << c1.print(t1); 

	cout << "-----------MAT<double> test------------" << endl;
	MAT<double>  a2(1, 2), b2(2, 2), c2(1, 2);
	char t2[2048];
	a2[0][0] = 1.4;		//类似地初始化矩阵的所有元素
	a2[0][1] = 4.1; 		//等价于“*(a.operator[ ](0)+1)=2;”即等价于“*(a[0]+1)=2;”
	cout << "初始化a：" << endl;
	cout << a2.print(t2);				//初始化矩阵后输出该矩阵
	b2[0][0] = 3.367; 	b2[0][1] = 2.5;	//调用T* const operator[ ](int r)初始化数组元素
	b2[1][0] = 5.1; 	b2[1][1] = 5.88;
	cout << "初始化b：" << endl;
	cout << b2.print(t2);
	c2 = a2 * b2;						//测试矩阵乘法运算
	cout << "c=a*b：" << endl;
	cout << c2.print(t2);
	cout << "a+c：" << endl;
	cout << (a2 + c2).print(t2);		//测试矩阵加法运算
	c2 = c2 - a2;						//测试矩阵减法运算
	cout << "c=c-a：" << endl;
	cout << c2.print(t2);
	c2 += a2;							//测试矩阵“+=”运算
	cout << "c+=a：" << endl;
	cout << c2.print(t2);
	c2 = ~b2;							//测试矩阵转置运算
	cout << "c=~b：" << endl;
	cout << c2.print(t2);

	cout << "\n-----------All test------------" << endl;
	int nMark = 0;
	const char* strResult = TestMAT(nMark);
	cout << "学号：U201814755" << endl;
	cout << "姓名：彭子晨" << endl;
	cout << "实验四测试：" << strResult << "," << nMark << endl;
	
	return 0;
}
