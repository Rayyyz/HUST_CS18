/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

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

#define LIST_INIT_SIZE 10
#define LISTINCREMENT  10
typedef struct Lnode{  //����Ķ���
	ElemType data;
	struct Lnode* next;
}LNode , *LinkList ;

extern bool isNull = TRUE;

/*-----FUNCTION DEFINE---------*/
status InitList(LinkList* L);							//������
status DestroyList(LinkList* L);						//ɾ����
status ClearList(LinkList* L);						//��ձ�
status ListEmpty(LinkList L);							//�жϱ��Ƿ�Ϊ��
int ListLength(LinkList L);							//��
status GetElem(LinkList L, int i, ElemType* e);         //��ñ�Ԫ��
status LocateElem(LinkList L, ElemType e, status(*Compare)(ElemType a, ElemType b));      //��λ��Ԫ��
status PriorElem(LinkList L, ElemType cur, ElemType* pre_e);  		//��ǰ��
status NextElem(LinkList L, ElemType cur, ElemType* next_e);   		//����
status ListInsert(LinkList* L, int i, ElemType e);             		//����Ԫ��
status ListDelete(LinkList* L, int i, ElemType& e);           //ɾ��Ԫ��
status ListTrabverse(LinkList L);                           //ɾ����
status Compare(ElemType a, ElemType b);					//�Ƚ�



int main(void) {
	LinkList L = NULL;
	int op = 1;
	int index;
	ElemType e, cue, pre, next;
	while (op) {
		system("cls");
		printf("\n\n");
		printf("      Menu for Linear Table On Link Structure \n");
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
			if (InitList(&L) == OK)
				printf("�������ɹ���\n");
			else
				printf("������ʧ�ܣ�\n");
			getchar();
			break;
		case 2:
			if (isNull == TRUE) {
				printf("�������ڣ�\n");
				getchar();
				break;
			}

			if (DestroyList(&L) == OK)
				printf("�������ٳɹ���\n");
			else
				printf("��������ʧ�ܣ�\n");
			getchar();
			break;
		case 3:
			if (isNull == TRUE) {
				printf("�������ڣ�\n");
				getchar();
				break;
			}
			if (ClearList(&L) == OK)
				printf("��������Ϊ�ձ�ɹ���\n");
			else
				printf("��������Ϊ�ձ�ʧ�ܣ�\n");
			getchar();
			break;
		case 4:
			if (isNull == TRUE) {
				printf("�������ڣ�\n");
				getchar();
				break;
			}
			if (ListEmpty(L) == TRUE)
				printf("����Ϊ�գ�\n");
			else
				printf("����Ϊ�գ�\n");
			getchar();
			break;
		case 5:
			if (isNull == TRUE) {
				printf("�������ڣ�\n");
				getchar();
				break;
			}
			printf("������%d��Ԫ�أ�\n", ListLength(L));
			getchar();
			break;
		case 6:
			if (isNull == TRUE) {
				printf("�������ڣ�\n");
				getchar();
				break;
			}
			printf("�������õĵ�i��Ԫ�أ�");
			scanf_s("%d", &index);
			getchar();
			if (GetElem(L, index, &e) != ERROR)
				printf("����ĵ�%d��Ԫ��Ϊ%d��\n", index, e);
			else
				printf("���벻�ڷ�Χ�ڣ�\n");
			getchar();
			break;
		case 7:
			if (isNull == TRUE) {
				printf("�������ڣ�\n");
				getchar();
				break;
			}
			printf("��������ҵ�Ԫ�أ�");
			scanf_s("%d", &e);
			getchar();
			if (LocateElem(L, e, Compare) !=ERROR)
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
				printf("�������ڣ�\n");
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
				printf("�������ڣ�\n");
				getchar();
				break;
			}
			printf("����������λ�ã�");
			scanf_s("%d", &index);
			getchar();
			printf("�������������֣�");
			scanf_s("%d", &e);
			getchar();
			if (ListInsert(&L, index, e) == OK)
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
			if (ListDelete(&L, index, e) != ERROR)
				printf("ɾ���ɹ���%d�ѱ�ɾ��\n", e);
			else
				printf("ɾ��ʧ�ܣ�\n");
			getchar();
			break;
		case 12:
			if (isNull == TRUE) {
				printf("�������ڣ�\n");
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
status InitList(LinkList* L) {
	*L = (LinkList)malloc(sizeof(LNode));
	if (*L == NULL)
		exit(OVERFLOW);
	isNull = FALSE;
	(*L)->data = 0;
	(*L)->next = NULL;
	return OK;
}

status DestroyList(LinkList* L) {
	LinkList p ,q ;
	p = *L;
	while (p) {
		q = p->next;
		free(p);
		p = q;
	}
	*L = NULL;
	isNull = TRUE;
	return OK;

}

status ClearList(LinkList* L) {
	LinkList p , q ;
	p = (*L)->next;
	while (p) {
		q = p->next;
		free(p);
		p = q;
	}
	(*L)->next = NULL;
	return OK;
}

status ListEmpty(LinkList L) {
	if (L->next == NULL) return TRUE;
	else return FALSE;
}

int ListLength(LinkList L) {
	int i = 0;
	LinkList p ;
	p = L->next;
	while (p) {
		p = p->next;
		i++;
	}
	return i;
}

status GetElem(LinkList L, int i, ElemType* e) {
	int index = 1;
	LinkList p = L->next;
	if (i < 1 || i > ListLength(L)) {
		return ERROR;
	}
	if (ListEmpty(L) == TRUE) {
		printf("����Ϊ�գ�");
		return ERROR;
	}
	if (i == 1) 
		return p->data;

	while (index < i && p) {
		p = p->next;
		index++;
	}
		*e = p->data;
		return OK;
	
}


status Compare(ElemType p, ElemType q) {
	if (p == q)
		return TRUE;
	else
		return FALSE;
}


status LocateElem(LinkList L, ElemType e, status Compare(ElemType, ElemType)) {
	int index = 1;
	LinkList p = L->next;
	for (index; index <= ListLength(L) && p; index++) {
		if (Compare(p->data,e)== TRUE) {
			return index;
		}
		p = p->next;
	}

	return ERROR;
}


status PriorElem(LinkList L, ElemType cur_e, ElemType* pre_e) {
	int i;
	LinkList p = L->next ;
	while (p->next != NULL && p->next->data != cur_e) {
		p = p->next;
	}
	if (p->next == NULL) {
		return ERROR;
	}
	*pre_e = p->data;
	return OK;
}

status NextElem(LinkList L, ElemType cur_e, ElemType* next_e) {
	int i;
	LinkList p = L->next ;
	while (p->next != NULL && p->data != cur_e) {
		p = p->next;
	}
	if (p->next == NULL) {
		return ERROR;
	}
	*next_e = p->next->data;
	return OK;
}


status ListInsert(LinkList* L, int i, ElemType e) {
	LinkList p, q;
	p = *L;
	int j = 1;
	q = (LinkList)malloc(sizeof(LNode));
	if (q == NULL) exit(OVERFLOW);
	q->data = e;
	if (i == 1) {
		q->next = p->next;
		(*L)->next = q;
		return OK;
	}
	for (p ; j < i && p; j++) {
		p = p->next;
	}
	if (p == NULL || j > i) {
		return ERROR;
	}
	if (p->next == NULL) {
		q->next = NULL;
	}
	else{
		q->next = p->next;
	}
	p->next = q;
	return OK;

}


status ListDelete(LinkList* L, int i, ElemType& e) {
	if (i < 1 || i > ListLength(*L))
		return ERROR;
	LinkList p ,q;
	p = *L;
	int j = 1;
	while (p!=NULL && j < i) {
		p = p->next;
		j++;
	}
	if (p == NULL || j > i) {
		return ERROR;
	}
	q = p->next;
	if (q->next == NULL) {
		p->next = NULL;
		e = q->data;
		free(q);
		return OK;
	}
	else {
		p->next = q->next;
		e = q->data;
		free(q);
		q = NULL;
		return OK;
	}
	return ERROR;
}


status ListTrabverse(LinkList L) {
	LinkList p ;
	p = L->next;
	if (ListLength(L) == 0) {
		printf("��������Ԫ�أ�");
	}
	printf("\n-----------all elements -----------------------\n");
	while (p != NULL) {
		printf(" %d ", p->data);
		p = p->next;
	}
	printf("\n------------------ end ------------------------\n");
	return OK;
}
