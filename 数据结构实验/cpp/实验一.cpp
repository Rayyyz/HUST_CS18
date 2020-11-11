/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

/*---------DATA DEFINE---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

/*-------TYPE DEFINE-------*/
typedef int status;
typedef int ElemType;

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct {  //˳���˳��ṹ���Ķ���
	ElemType* elem;
	int length;
	int listsize;
}SqList;

extern bool isNull = TRUE;  //ȫ�ֱ������ж����Ƿ�Ϊ��

/*-----FUNCTION DEFINE---------*/
status InitList(SqList& L);							//������
status DestroyList(SqList& L);						//ɾ����
status ClearList(SqList& L);						//��ձ�
status ListEmpty(SqList L);							//�жϱ��Ƿ�Ϊ��
int ListLength(SqList L);							//��
status GetElem(SqList L, int i, ElemType& e);         //��ñ�Ԫ��
status LocateElem(SqList L, ElemType e, status(*Compare)(ElemType a, ElemType b));      //��λ��Ԫ��
status PriorElem(SqList L, ElemType cur, ElemType* pre_e);  		//��ǰ��
status NextElem(SqList L, ElemType cur, ElemType* next_e);   		//����
status ListInsert(SqList& L, int i, ElemType e);             		//����Ԫ��
status ListDelete(SqList& L, int i, ElemType& e);           //ɾ��Ԫ��
status ListTrabverse(SqList L);                           //ɾ����
status Compare(ElemType a, ElemType b);					//�Ƚ�


void main(void) {
	SqList L;
	int op = 1;
	int index;
	ElemType e, cue, pre, next;
	while (op) {
		system("cls");
		printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. InitList       7. LocateElem\n");
		printf("    	  2. DestroyList    8. PriorElem\n");
		printf("    	  3. ClearList      9. NextElem \n");
		printf("    	  4. ListEmpty     10. ListInsert\n");
		printf("    	  5. ListLength    11. ListDelete\n");
		printf("    	  6. GetElem       12. ListTrabverse\n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("    ��ѡ����Ĳ���[0~12]:");
		scanf_s("%d", &op);
		getchar();
		switch (op) {
		case 1:
			if (InitList(L) == OK)
				printf("���Ա����ɹ���\n");
			else
				printf("���Ա���ʧ�ܣ�\n");
			getchar();
			break;
		case 2:
			if (isNull == TRUE) {
				printf("���Ա����ڣ�\n");
				getchar();
				break;
			}
				
			if (DestroyList(L) == OK)
				printf("���Ա����ٳɹ���\n");
			else
				printf("���Ա�����ʧ�ܣ�\n");
			getchar();
			break;
		case 3:
			if (isNull == TRUE) {
				printf("���Ա����ڣ�\n");
				getchar();
				break;
			}
			if (ClearList(L) == OK)
				printf("���Ա�����Ϊ�ձ�ɹ���\n");
			else
				printf("���Ա�����Ϊ�ձ�ʧ�ܣ�\n");
			getchar();
			break;
		case 4:
			if (isNull == TRUE) {
				printf("���Ա����ڣ�\n");
				getchar();
				break;
			}
			if (ListEmpty(L) == TRUE)
				printf("���Ա�Ϊ�գ�\n");
			else
				printf("���Ա�Ϊ�գ�\n");
			getchar();
			break;
		case 5:
			if (isNull == TRUE) {
				printf("���Ա����ڣ�\n");
				getchar();
				break;
			}
				printf("���Ա���%d��Ԫ�أ�\n", ListLength(L));
			getchar();
			break;
		case 6:
			if (isNull == TRUE) {
				printf("���Ա����ڣ�\n");
				getchar();
				break;
			}
			printf("�������õĵ�i��Ԫ�أ�");
			scanf_s("%d", &index);
			getchar();
			if (GetElem(L, index, e) != ERROR)
				printf("���Ա�ĵ�%d��Ԫ��Ϊ%d��\n", index, e);
			else
				printf("���벻�ڷ�Χ�ڣ�\n");
			getchar();
			break;
		case 7:
			if (isNull == TRUE) {
				printf("���Ա����ڣ�\n");
				getchar();
				break;
			}
			printf("��������ҵ�Ԫ�أ�");
			scanf_s("%d", &e);
			getchar();
			if (LocateElem(L, e, Compare) > 0)
				printf("��Ԫ�ص�λ����%d��\n", LocateElem(L, e, Compare));
			else
				printf("Ԫ�ز����ڣ�\n");
			getchar();
			break;
		case 8:
			if (isNull == TRUE) {
				printf("���Ա����ڣ�\n");
				getchar();
				break;
			}
			printf("��������ҵ�Ԫ�أ�");
			scanf_s("%d", &cue);
			getchar();
			if (PriorElem(L, cue, &pre) > 0)
				printf("��Ԫ�ص�ǰ����%d��\n", pre);
			else
				printf("����ʧ�ܣ�\n");
			getchar();
			break;
		case 9:
			if (isNull == TRUE) {
				printf("���Ա����ڣ�\n");
				getchar();
				break;
			}
			printf("��������ҵ�Ԫ�أ�");
			scanf_s("%d", &cue);
			getchar();
			if (NextElem(L, cue, &next) > 0)
				printf("��Ԫ�صĺ����%d��\n", next);
			else
				printf("����ʧ�ܣ�\n");
			getchar();
			break;
		case 10:
			if (isNull == TRUE) {
				printf("���Ա����ڣ�\n");
				getchar();
				break;
			}
			printf("����������λ�ã�");
			scanf_s("%d", &index);
			getchar();
			printf("�������������֣�");
			scanf_s("%d", &e);
			getchar();
			if (ListInsert(L, index, e) == OK)
				printf("����ɹ���\n");
			else
				printf("����ʧ�ܣ�\n");
			getchar();
			break;
		case 11:
			if (isNull == TRUE) {
				printf("���Ա����ڣ�\n");
				getchar();
				break;
			}
			printf("������ɾ����λ�ã�");
			scanf_s("%d", &index);
			getchar();
			if (ListDelete(L, index, e) != ERROR)
				printf("ɾ���ɹ���%d�ѱ�ɾ��\n", e);
			else
				printf("ɾ��ʧ�ܣ�\n");
			getchar();
			break;
		case 12:
			if (isNull == TRUE) {
				printf("���Ա����ڣ�\n");
				getchar();
				break;
			}
			ListTrabverse(L);
			getchar();
			break;
		case 0:
			break;
		}//end of switch
	}//end of while
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
	getchar();
}//end of main()

/*--------Funcions---------------*/
status InitList(SqList& L) {
	if (isNull == FALSE) {
		printf("�ѽ�֮ǰ�ı�������½��ձ�");
		getchar();
	}
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem)
		exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	isNull = FALSE;
	return OK;
}

status DestroyList(SqList& L) {
	L.length = 0;
	isNull = TRUE;
	free(L.elem);
	L.elem = NULL;
	return OK;
}

status ClearList(SqList& L) {
	if (!L.elem) return ERROR;
	L.length = 0;
	return OK;
}

status ListEmpty(SqList L) {
	if (L.length == 0) return TRUE;
	else return FALSE;
}

int ListLength(SqList L) {
	if (L.elem) return L.length;
	else return ERROR;
}

status GetElem(SqList L, int i, ElemType& e) {
	if (ListEmpty(L) == TRUE) {
		printf("���Ա�Ϊ�գ�");
		return ERROR;
	}
	if (i >= 1 && i <= ListLength(L)) {
		e = L.elem[i - 1];
		return e;
	}
	else {
		printf("�������󣬱����޸�Ԫ�أ�");
		return ERROR;
	}

}

status Compare(ElemType p, ElemType q) {
	if (p == q) 
		return TRUE;
	else 
		return FALSE;
}

status LocateElem(SqList L, ElemType e, status Compare(ElemType, ElemType)) {
	int index = 1;
	for (index; index <= L.length; index++) {
		if ((*Compare)(L.elem[index - 1], e)) {
			return index;
		}
	}
	return ERROR;
}

status PriorElem(SqList L, ElemType cur_e, ElemType* pre_e) {
	int i;
	for (i = 0; i < L.listsize; i++) {
		if (L.elem[i] == cur_e) {
			if (i == 0) {
				printf("��Ԫ�ز�����ǰ����");
				return ERROR;
			}
			*pre_e = L.elem[i - 1];
			return OK;
		}
	}
	printf("����û�и�Ԫ�أ�");
	return ERROR;

}

status NextElem(SqList L, ElemType cur_e, ElemType* next_e) {
	int i;
	for (i = 0; i < L.listsize - 1; i++) {
		if (L.elem[i] == cur_e) {
			if (i == L.length - 1) {
				printf("�Ѿ�������Ԫ���ˣ�");
				return ERROR;
			}
			*next_e = L.elem[i + 1];
			return OK;
		}
	}
	printf("����û�и�Ԫ�أ�");
	return ERROR;
}

status ListInsert(SqList& L, int i, ElemType e) {
	if (i < 1 || i > L.length + 1) return ERROR;
	if (L.length >= L.listsize) {
		ElemType* newbase = (ElemType*)realloc(L.elem, (L.length + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase) exit(OVERFLOW);
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}
	ElemType* q = &(L.elem[i - 1]);
	for (ElemType* p = &(L.elem[L.length - 1]); p >= q; p--)
	{
		*(p + 1) = *p;
	}
	*q = e;
	L.length += 1;
	return OK;
}

status ListDelete(SqList& L, int i, ElemType& e) {
	if (i < 1 || i > L.length) 
		return ERROR;
	ElemType* p = &(L.elem[i - 1]), * q;
	e = L.elem[i - 1];
	q = L.elem + L.length - 1;
	for (++p; p <= q; ++p)* (p - 1) = *p;
	L.length -= 1;
	return e;

}

status ListTrabverse(SqList L) {
	int i;
	printf("\n-----------all elements -----------------------\n");
	for (i = 0; i < L.length; i++) printf(" %d ", L.elem[i]);
	printf("\n------------------ end ------------------------\n");
	return L.length;
}
