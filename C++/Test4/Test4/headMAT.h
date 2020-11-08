#define _CRT_SECURE_NO_WARNINGS 
#include <iomanip> 
#include <iostream>
#include <exception>
#include <typeinfo>
#include <string.h>
using namespace std;

template <typename T>
class MAT {
	T* const e;				//ָ���������;���Ԫ�ص�ָ��
	const int r, c;			//�������r����c��С
public:
	MAT(int r, int c);				//������
	MAT(const MAT& a);				//�������
	MAT(MAT&& a)noexcept;			//�ƶ�����
	virtual ~MAT()noexcept;
	virtual T* const operator[ ](int r);//ȡ����r�еĵ�һ��Ԫ�ص�ַ��rԽ�����쳣
	virtual MAT operator+(const MAT& a)const;	//����ӷ������ܼ����쳣
	virtual MAT operator-(const MAT& a)const;	//������������ܼ����쳣
	virtual MAT operator*(const MAT& a)const;	//����˷������ܳ����쳣
	virtual MAT operator~()const;				//����ת��
	virtual MAT& operator=(const MAT& a);		//�����ֵ����
	virtual MAT& operator=(MAT&& a)noexcept;	//�ƶ���ֵ����
	virtual MAT& operator+=(const MAT& a);		//��+=������
	virtual MAT& operator-=(const MAT& a);		//��-=������
	virtual MAT& operator*=(const MAT& a);		//��*=������
	virtual char* print(char* s)const noexcept;//print�����s������s�����ÿո���������ûس�����
};

//������
template <typename T>
MAT<T>::MAT(int r, int c) :r(r), c(c), e(new T[r * c]) {
	return;
}

//�������
template <typename T>
MAT<T>::MAT(const MAT& a) :r(a.r), c(a.c), e(new T[a.r * a.c]) {
	//if (a.e == nullptr) return;
	for (int i = 0; i < a.r * a.c; i++) {
		e[i] = a.e[i];
	}
	return;
}

//�ƶ�����
template <typename T>
MAT<T>::MAT(MAT&& a)noexcept :r(a.r), c(a.c), e(a.e) {
	*(T**)&a.e = nullptr;
	*(int*)&a.r = 0;
	*(int*)&a.c = 0;
	return;
}

//���پ���
template <typename T>
MAT<T>::~MAT()noexcept {
	if (!e) {
		delete e;
		*(T**)&e = nullptr;
	}
	*(int*)&r = 0;
	*(int*)&c = 0;
	return;
}

//ȡ����r�еĵ�һ��Ԫ�ص�ַ��rԽ�����쳣
template <typename T>
T* const MAT<T>::operator[ ](int r) {
	if (r < 0 || r >= this->r)
		throw "Overflowed!";
	return &e[r * c];
}

//����ӷ������ܼ����쳣
template <typename T>
MAT<T> MAT<T>::operator+(const MAT& a)const {
	MAT Madd(r, c);
	if (r != a.r || c != a.c || !e || !a.e)
		throw "Cannot +!";
	for (int i = 0; i < r * c; i++) {
		Madd.e[i] = e[i] + a.e[i];
	}
	return Madd;
}

//������������ܼ����쳣
template <typename T>
MAT<T> MAT<T>::operator-(const MAT& a)const {
	MAT Msub(r, c);
	if (r != a.r || c != a.c || !e || !a.e)
		throw "Cannot -!";
	for (int i = 0; i < r * c; i++) {
		Msub.e[i] = e[i] - a.e[i];
	}
	return Msub;
}

//����˷������ܳ����쳣
template <typename T>
MAT<T> MAT<T>::operator*(const MAT& a)const {
	MAT Mmul(r, a.c);
	if (c != a.r || !e || !a.e)
		throw "Cannot *!";
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < a.c; j++) {
			Mmul.e[i * c + j] = 0;
			for (int k = 0; k < c; k++) {
				Mmul.e[i * c + j] += e[i * c + k] * a.e[k * a.c + j];
			}
		}
	}
	return Mmul;
}

//����ת��
template <typename T>
MAT<T> MAT<T>::operator~()const {
	MAT Mover(c, r);	//ת֮��ľ����к͸߻���
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			Mover.e[j * r + i] = e[i * c + j];
		}
	}
	return Mover;
}

//�����ֵ����
template <typename T>
MAT<T>& MAT<T>::operator=(const MAT& a) {
	if (&a == this) return *this;
	*(T**)&e = new T[a.r * a.c];
	*(int*)&r = a.r;
	*(int*)&c = a.c;
	for (int i = 0; i < a.r * a.c; i++) {
		e[i] = a.e[i];
	}
	return *this;
}

//�ƶ���ֵ����
template <typename T>
MAT<T>& MAT<T>::operator=(MAT&& a)noexcept {
	if (&a == this) return *this;
	*(T**)&e = a.e;
	*(int*)&r = a.r;
	*(int*)&c = a.c;

	*(T**)&a.e = nullptr;
	*(int*)&a.r = 0;
	*(int*)&a.c = 0;
	return *this;
}

//��+=������
template <typename T>
MAT<T>& MAT<T>::operator+=(const MAT& a) {
	if (r != a.r || c != a.c || !e || !a.e)
		throw "Cannot +=!";
	for (int i = 0; i < r * c; i++) {
		e[i] = e[i] + a.e[i];
	}
	return *this;
}

//��-=������
template <typename T>
MAT<T>& MAT<T>::operator-=(const MAT& a) {
	if (r != a.r || c != a.c || !e || !a.e)
		throw "Cannot -=!";
	for (int i = 0; i < r * c; i++) {
		e[i] = e[i] - a.e[i];
	}
	return *this;
}

//��*=������
template <typename T>
MAT<T>& MAT<T>::operator*=(const MAT& a) {
	MAT Mmul(r, a.c);
	if (c != a.r || !e || !a.e)
		throw "Cannot *!";
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < a.c; j++) {
			Mmul.e[i * c + j] = 0;
			for (int k = 0; k < c; k++) {
				Mmul.e[i * c + j] += e[i * c + k] * a.e[k * a.c + j];
			}
		}
	}
	if (!e) delete e;
	*(T**)&e = Mmul.e;
	*(int*)&r = Mmul.r;
	*(int*)&c = Mmul.c;
	return *this;
}

//print�����s������s�����ÿո���������ûس�����
//�����ػ�,�������������ֿ�
template <>
char* MAT<double>::print(char* s)const noexcept {
	char* stmp = s;
	stmp[0] = '\0';
	if (!e) return s;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			stmp = s + strlen(s);
			if (j == c - 1)
				sprintf(stmp, "%8lf\n", e[i * c + j]);
			else
				sprintf(stmp, "%8lf ", e[i * c + j]);
		}
	}
	return s;
}
template <>
char* MAT<float>::print(char* s)const noexcept {
	char* stmp = s;
	stmp[0] = '\0';
	if (!e) return s;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			stmp = s + strlen(s);
			if (j == c - 1)
				sprintf(stmp, "%8lf\n", e[i * c + j]);
			else
				sprintf(stmp, "%8lf ", e[i * c + j]);
		}
	}
	return s;
}
template <typename T>
char* MAT<T>::print(char* s)const noexcept {
	char* stmp = s;
	stmp[0] = '\0';
	if (!e) return s;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			stmp = s + strlen(s);
			if (j == c - 1)
				sprintf(stmp, "%6ld\n", e[i * c + j]);
			else
				sprintf(stmp, "%6ld ", e[i * c + j]);
		}
	}
	return s;
}