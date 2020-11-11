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
typedef struct Lnode{  //链表的定义
	ElemType data;
	struct Lnode* next;
}LNode , *LinkList ;

extern bool isNull = TRUE;

/*-----FUNCTION DEFINE---------*/
status InitList(LinkList* L);							//创建表
status DestroyList(LinkList* L);						//删除表
status ClearList(LinkList* L);						//清空表
status ListEmpty(LinkList L);							//判断表是否为空
int ListLength(LinkList L);							//表长
status GetElem(LinkList L, int i, ElemType* e);         //获得表元素
status LocateElem(LinkList L, ElemType e, status(*Compare)(ElemType a, ElemType b));      //定位表元素
status PriorElem(LinkList L, ElemType cur, ElemType* pre_e);  		//求前驱
status NextElem(LinkList L, ElemType cur, ElemType* next_e);   		//求后继
status ListInsert(LinkList* L, int i, ElemType e);             		//插入元素
status ListDelete(LinkList* L, int i, ElemType& e);           //删除元素
status ListTrabverse(LinkList L);                           //删除表
status Compare(ElemType a, ElemType b);					//比较



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
		printf("    请选择你的操作[0~12]:");
		scanf_s("%d", &op);
		getchar();
		switch (op) {
		case 1:
			if (InitList(&L) == OK)
				printf("链表创建成功！\n");
			else
				printf("链表创建失败！\n");
			getchar();
			break;
		case 2:
			if (isNull == TRUE) {
				printf("链表不存在！\n");
				getchar();
				break;
			}

			if (DestroyList(&L) == OK)
				printf("链表销毁成功！\n");
			else
				printf("链表销毁失败！\n");
			getchar();
			break;
		case 3:
			if (isNull == TRUE) {
				printf("链表不存在！\n");
				getchar();
				break;
			}
			if (ClearList(&L) == OK)
				printf("链表重置为空表成功！\n");
			else
				printf("链表重置为空表失败！\n");
			getchar();
			break;
		case 4:
			if (isNull == TRUE) {
				printf("链表不存在！\n");
				getchar();
				break;
			}
			if (ListEmpty(L) == TRUE)
				printf("链表为空！\n");
			else
				printf("链表不为空！\n");
			getchar();
			break;
		case 5:
			if (isNull == TRUE) {
				printf("链表不存在！\n");
				getchar();
				break;
			}
			printf("链表有%d个元素！\n", ListLength(L));
			getchar();
			break;
		case 6:
			if (isNull == TRUE) {
				printf("链表不存在！\n");
				getchar();
				break;
			}
			printf("输入想获得的第i个元素：");
			scanf_s("%d", &index);
			getchar();
			if (GetElem(L, index, &e) != ERROR)
				printf("链表的第%d个元素为%d！\n", index, e);
			else
				printf("输入不在范围内！\n");
			getchar();
			break;
		case 7:
			if (isNull == TRUE) {
				printf("链表不存在！\n");
				getchar();
				break;
			}
			printf("输入想查找的元素：");
			scanf_s("%d", &e);
			getchar();
			if (LocateElem(L, e, Compare) !=ERROR)
				printf("该元素的位置在%d！\n", LocateElem(L, e, Compare));
			else
				printf("元素不存在！\n");
			getchar();
			break;
		case 8:
			if (isNull == TRUE) {
				printf("线性表不存在！\n");
				getchar();
				break;
			}
			printf("输入想查找的元素：");
			scanf_s("%d", &cue);
			getchar();
			if (PriorElem(L, cue, &pre) > 0)
				printf("该元素的前驱是%d！\n", pre);
			else
				printf("查找失败！\n");
			getchar();
			break;
		case 9:
			if (isNull == TRUE) {
				printf("链表不存在！\n");
				getchar();
				break;
			}
			printf("输入想查找的元素：");
			scanf_s("%d", &cue);
			getchar();
			if (NextElem(L, cue, &next) > 0)
				printf("该元素的后继是%d！\n", next);
			else
				printf("查找失败！\n");
			getchar();
			break;
		case 10:
			if (isNull == TRUE) {
				printf("链表不存在！\n");
				getchar();
				break;
			}
			printf("输入想插入的位置：");
			scanf_s("%d", &index);
			getchar();
			printf("输入想插入的数字：");
			scanf_s("%d", &e);
			getchar();
			if (ListInsert(&L, index, e) == OK)
				printf("插入成功！\n");
			else
				printf("插入失败！\n");
			getchar();
			break;
		case 11:
			if (isNull == TRUE) {
				printf("线性表不存在！\n");
				getchar();
				break;
			}
			printf("输入想删除的位置：");
			scanf_s("%d", &index);
			getchar();
			if (ListDelete(&L, index, e) != ERROR)
				printf("删除成功！%d已被删除\n", e);
			else
				printf("删除失败！\n");
			getchar();
			break;
		case 12:
			if (isNull == TRUE) {
				printf("链表不存在！\n");
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
	printf("欢迎下次再使用本系统！\n");
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
		printf("链表为空！");
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
		printf("链表中无元素！");
	}
	printf("\n-----------all elements -----------------------\n");
	while (p != NULL) {
		printf(" %d ", p->data);
		p = p->next;
	}
	printf("\n------------------ end ------------------------\n");
	return OK;
}
