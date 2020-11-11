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
typedef struct {  //顺序表（顺序结构）的定义
	ElemType* elem;
	int length;
	int listsize;
}SqList;

extern bool isNull = TRUE;  //全局变量，判定表是否为空

/*-----FUNCTION DEFINE---------*/
status InitList(SqList& L);							//创建表
status DestroyList(SqList& L);						//删除表
status ClearList(SqList& L);						//清空表
status ListEmpty(SqList L);							//判断表是否为空
int ListLength(SqList L);							//表长
status GetElem(SqList L, int i, ElemType& e);         //获得表元素
status LocateElem(SqList L, ElemType e, status(*Compare)(ElemType a, ElemType b));      //定位表元素
status PriorElem(SqList L, ElemType cur, ElemType* pre_e);  		//求前驱
status NextElem(SqList L, ElemType cur, ElemType* next_e);   		//求后继
status ListInsert(SqList& L, int i, ElemType e);             		//插入元素
status ListDelete(SqList& L, int i, ElemType& e);           //删除元素
status ListTrabverse(SqList L);                           //删除表
status Compare(ElemType a, ElemType b);					//比较


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
		printf("    请选择你的操作[0~12]:");
		scanf_s("%d", &op);
		getchar();
		switch (op) {
		case 1:
			if (InitList(L) == OK)
				printf("线性表创建成功！\n");
			else
				printf("线性表创建失败！\n");
			getchar();
			break;
		case 2:
			if (isNull == TRUE) {
				printf("线性表不存在！\n");
				getchar();
				break;
			}
				
			if (DestroyList(L) == OK)
				printf("线性表销毁成功！\n");
			else
				printf("线性表销毁失败！\n");
			getchar();
			break;
		case 3:
			if (isNull == TRUE) {
				printf("线性表不存在！\n");
				getchar();
				break;
			}
			if (ClearList(L) == OK)
				printf("线性表重置为空表成功！\n");
			else
				printf("线性表重置为空表失败！\n");
			getchar();
			break;
		case 4:
			if (isNull == TRUE) {
				printf("线性表不存在！\n");
				getchar();
				break;
			}
			if (ListEmpty(L) == TRUE)
				printf("线性表为空！\n");
			else
				printf("线性表不为空！\n");
			getchar();
			break;
		case 5:
			if (isNull == TRUE) {
				printf("线性表不存在！\n");
				getchar();
				break;
			}
				printf("线性表有%d个元素！\n", ListLength(L));
			getchar();
			break;
		case 6:
			if (isNull == TRUE) {
				printf("线性表不存在！\n");
				getchar();
				break;
			}
			printf("输入想获得的第i个元素：");
			scanf_s("%d", &index);
			getchar();
			if (GetElem(L, index, e) != ERROR)
				printf("线性表的第%d个元素为%d！\n", index, e);
			else
				printf("输入不在范围内！\n");
			getchar();
			break;
		case 7:
			if (isNull == TRUE) {
				printf("线性表不存在！\n");
				getchar();
				break;
			}
			printf("输入想查找的元素：");
			scanf_s("%d", &e);
			getchar();
			if (LocateElem(L, e, Compare) > 0)
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
				printf("线性表不存在！\n");
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
				printf("线性表不存在！\n");
				getchar();
				break;
			}
			printf("输入想插入的位置：");
			scanf_s("%d", &index);
			getchar();
			printf("输入想插入的数字：");
			scanf_s("%d", &e);
			getchar();
			if (ListInsert(L, index, e) == OK)
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
			if (ListDelete(L, index, e) != ERROR)
				printf("删除成功！%d已被删除\n", e);
			else
				printf("删除失败！\n");
			getchar();
			break;
		case 12:
			if (isNull == TRUE) {
				printf("线性表不存在！\n");
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
status InitList(SqList& L) {
	if (isNull == FALSE) {
		printf("已将之前的表清除并新建空表！");
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
		printf("线性表为空！");
		return ERROR;
	}
	if (i >= 1 && i <= ListLength(L)) {
		e = L.elem[i - 1];
		return e;
	}
	else {
		printf("输入有误，表中无该元素！");
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
				printf("该元素不存在前驱！");
				return ERROR;
			}
			*pre_e = L.elem[i - 1];
			return OK;
		}
	}
	printf("表中没有该元素！");
	return ERROR;

}

status NextElem(SqList L, ElemType cur_e, ElemType* next_e) {
	int i;
	for (i = 0; i < L.listsize - 1; i++) {
		if (L.elem[i] == cur_e) {
			if (i == L.length - 1) {
				printf("已经是最后的元素了！");
				return ERROR;
			}
			*next_e = L.elem[i + 1];
			return OK;
		}
	}
	printf("表中没有该元素！");
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
