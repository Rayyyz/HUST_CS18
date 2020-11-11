#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define LIST_INIT_SIZE 1024
#define NUM_MAX  30
typedef int Status;
typedef int TElemType;
typedef char KeyType;

static bool isNull = TRUE;
static int i = -1;

typedef struct ElemType/*������ŵ����ݵĽṹ����*/
{
	KeyType key; /*Ψһ��ʶ*/
	TElemType value;
}ElemType;

typedef struct BiTNode { /*����ÿ�����Ľṹ*/
	ElemType data;
	BiTNode* lchild, * rchild;
}BiTNode, * TNode;


typedef struct QueueList {
	TNode data[LIST_INIT_SIZE];
	int front;
	int rear;
}queue, * Queue;

typedef struct Stack {
	TNode data[LIST_INIT_SIZE];
	int top;
}Stack, * stacknode;

static TNode Findnode = NULL;		/*ȫ�ֱ��������ҽ��*/
static TNode Brothernode = NULL;	/*ȫ�ֱ������ֵܽ��*/
static TNode Parentnode = NULL;		/*ȫ�ֱ�����˫�׽ڵ�*/
FILE* tree = NULL;					/*ȫ�ֱ������ļ�ָ��*/

/*Function defined*/
Status CreateBiTree(TNode* T, char* definition);		/*���ɶ�����*/
Status DestroyBiTree(TNode* T);								/*���ٶ�����*/
Status ReDestroyBiTree(TNode temp);							/*���ٶ�����-�ݹ���*/
Status ClearBiTree(TNode* T);								/*��ն�����*/
Status BiTreeEmpty(TNode T);								/*�ж��ն�����*/
Status BiTreeDepth(TNode T);								/*����������*/
TNode LocateNode(TNode T, KeyType e);						/*���ҽ��*/
Status Assign(TNode* T, KeyType e, TElemType value);		/*��㸳ֵ*/
TNode GetSibling(TNode T, KeyType e);						/*����ֵܽ��*/
TNode GetParent(TNode T, KeyType e);						/*��ø��ڵ�*/
Status InsertNode(TNode* T, KeyType e, int LR, TNode c);	/*������*/
Status DeleteNode(TNode* T, KeyType e);						/*ɾ�����*/
Status PreOrderTraverse(TNode T);							/*ǰ�����*/
Status InOrderTraverse(TNode T);					/*�������*/
Status PostOrderTraverse(TNode T);					/*�������*/
Status LevelOrderTraverse(TNode T);					/*�������*/
Status Visit(TNode T);								/*���ʽ��*/
void InitQueue(Queue* q);							/*�½�����*/
Status EnQueue(Queue* q, TNode T);					/*���*/
TNode OutQueue(Queue* q);							/*����*/
Status SaveTree(TNode T, char* path);				/*������*/
Status ReSaveTree(TNode T);
Status LoadTree(TNode* T, char* path);				/*��ȡ��*/
void InitStack(stacknode* s);					/*����ջ*/
Status push(stacknode* s ,TNode T);				/*��ջ*/
TNode pop(stacknode* s);						/*��ջ*/



int main(void) {
	int op = 1, LR;
	TNode T = NULL, FindNode, BrotherNode, SertNode;
	KeyType find, name;
	char definition[NUM_MAX], filename[NUM_MAX], loadname[NUM_MAX];
	TElemType value;
	while (op) {
		system("cls");
		printf("\n\n-----------------Menu for Linear Table On Binary Tree----------------\n");
		printf("		1. CreateBiTree       9. InsertNode\n");
		printf("		2. DestroyBiTree     10. DeleteNode \n");
		printf("		3. ClearBiTree       11. PreOrderTraverse \n");
		printf("		4. BiTreeEmpty       12. InOrderTraverse \n");
		printf("		5. BiTreeDepth       13. PostOrderTraverse\n");
		printf("		6. LocateNode        14. LevelOrderTraverse\n");
		printf("		7. Assign            15. SaveTree\n");
		printf("		8. GetSibling        16. LoadTree\n");
		printf("		0. Exit\n\n");
		printf("-------------------------------------------------------------------------\n");
		printf("ѡ����Ĳ���:\n");
		scanf_s("%d", &op);
		getchar();
		switch (op)
		{
		case 1:
			T = NULL;
			printf("���������������ǰ���У�(�ս�����롮#��)\n");
			gets_s(definition);
			if (CreateBiTree(&T, definition) == OK) {
				printf("�����������ɹ���\n");
			}
			else {
				printf("����������ʧ�ܣ�\n");
			}
			getchar();
			break;

		case 2:
			if (isNull == TRUE) {
				printf("�����������ڣ�\n");
				getchar();
				break;
			}
			if (DestroyBiTree(&T) == OK)
				printf("���������ٳɹ���\n");
			else
				printf("����������ʧ�ܣ�\n");
			getchar();
			break;

		case 3:
			if (isNull == TRUE) {
				printf("�����������ڣ�\n");
				getchar();
				break;
			}
			if (ClearBiTree(&T) == TRUE)
				printf("��������ճɹ���\n");
			else
				printf("������Ϊ�գ�\n");
			getchar();
			break;

		case 4:
			if (isNull == TRUE) {
				printf("�����������ڣ�\n");
				getchar();
				break;
			}
			if (BiTreeEmpty(T) == TRUE)
				printf("������Ϊ�գ�\n");
			else
				printf("��������Ϊ�գ�\n");
			getchar();
			break;

		case 5:
			if (isNull == TRUE) {
				printf("�����������ڣ�\n");
				getchar();
				break;
			}
			if (BiTreeEmpty(T) == TRUE)
				printf("������Ϊ���������Ϊ0.\n");
			else
				printf("�����������Ϊ%d.\n", BiTreeDepth(T));
			getchar();
			break;

		case 6:
			if (isNull == TRUE) {
				printf("�����������ڣ�\n");
				getchar();
				break;
			}
			printf("����������ҵ�Ԫ�صĹؼ��֣�\n");
			scanf_s("%c", &find);
			getchar();
			FindNode = LocateNode(T, find);
			Findnode = NULL;
			if (!FindNode)
				printf("����ʧ�ܣ�");
			else {
				printf("���ҳɹ��������Ϣ���£�\n");
				Visit(FindNode);
			}
			getchar();
			break;

		case 7:
			if (isNull == TRUE) {
				printf("�����������ڣ�\n");
				getchar();
				break;
			}
			printf("�������븳ֵ��Ԫ�صĹؼ��֣�\n");
			scanf_s("%c", &name);
			getchar();
			printf("�������븳�����ֵ��\n");
			scanf_s("%d", &value);
			getchar();
			if (Assign(&T, name, value) == OK)
				printf("��ֵ�ɹ���\n");
			else
				printf("��ֵʧ�ܣ�\n");
			getchar();
			break;

		case 8:
			if (isNull == TRUE) {
				printf("�����������ڣ�\n");
				getchar();
				break;
			}
			printf("������������ֵܽ���Ԫ�صĹؼ��֣�\n");
			scanf_s("%c", &find);
			getchar();
			if (BiTreeEmpty(T) == TRUE) {
				printf("������Ϊ�գ�");
				getchar();
				break;
			}
			if (find == T->data.key) {
				printf("����ʧ�ܣ��ý��Ϊ���ĸ���㡣\n");
				getchar();
				break;
			}
			if (LocateNode(T, find) == NULL) {
				Findnode = NULL;
				printf("�Ҳ����ý�㣡\n");
				getchar();
				break;
			}
			BrotherNode = GetSibling(T, find);
			Brothernode = NULL;
			if (BrotherNode) {
				printf("���ҳɹ����ý����ֵܽ����Ϣ���£�\n");
				Visit(BrotherNode);
			}
			else
				printf("����ʧ�ܣ�");
			getchar();
			break;

		case 9:
			if (isNull == TRUE) {
				printf("�����������ڣ�\n");
				getchar();
				break;
			}
			printf("���������½���Ԫ�صĹؼ��֣�\n");
			scanf_s("%c", &name);
			getchar();
			printf("��������Ӧ����ֵ��\n");
			scanf_s("%d", &value);
			getchar();
			printf("������������λ��Ԫ�صĹؼ��֣�\n");
			scanf_s("%c", &find);
			getchar();
			printf("������뵽��Ԫ�ص����㻹���ҽ�㣿(��0��1)��\n");
			scanf_s("%d", &LR);
			getchar();
			if (LocateNode(T, name) != NULL) {
				Findnode = NULL;
				printf("�ùؼ������У�\n");
				getchar();
				break;
			}
			SertNode = (TNode)malloc(sizeof(BiTNode));
			SertNode->data = { name,value };
			SertNode->lchild = NULL;
			SertNode->rchild = NULL;
			if (LocateNode(T, find) != NULL) {
				Findnode = NULL;
				if (InsertNode(&T, find, LR, SertNode) == OK) {
					printf("������ɹ���\n");
				}
				else
					printf("����ʧ�ܣ�\n");
			}
			else
				printf("����ʧ�ܣ�\n");
			getchar();
			break;

		case 10:
			if (isNull == TRUE) {
				printf("�����������ڣ�\n");
				getchar();
				break;
			}
			printf("��������ɾ����Ԫ�صĹؼ��֣�\n");
			scanf_s("%c", &name);
			getchar();
			if (LocateNode(T, name) != NULL) {
				FindNode = NULL;
				if (DeleteNode(&T, name) == OK)
					printf("ɾ�����ɹ���\n");
				else
					printf("ɾ��ʧ�ܣ�\n");
			}
			else
				printf("ɾ��ʧ�ܣ�\n");
			getchar();
			break;

		case 11:
			if (isNull == TRUE) {
				printf("�����������ڣ�\n");
				getchar();
				break;
			}
			PreOrderTraverse(T);
			getchar();
			break;

		case 12:
			if (isNull == TRUE) {
				printf("�����������ڣ�\n");
				getchar();
				break;
			}
			InOrderTraverse(T);
			getchar();
			break;

		case 13:
			if (isNull == TRUE) {
				printf("�����������ڣ�\n");
				getchar();
				break;
			}
			PostOrderTraverse(T);
			getchar();
			break;

		case 14:
			if (isNull == TRUE) {
				printf("�����������ڣ�\n");
				getchar();
				break;
			}
			LevelOrderTraverse(T);
			getchar();
			break;
		case 15:
			if (isNull == TRUE) {
				printf("�����������ڣ�\n");
				getchar();
				break;
			}
			printf("��������洢���ļ�����\n");
			scanf_s("%s", filename, NUM_MAX);
			getchar();
			if (SaveTree(T, filename) == INFEASIBLE)
				printf("����ʧ�ܣ�\n");
			if (SaveTree(T, filename) == ERROR)
				printf("����ʧ�ܣ�\n");
			else
				printf("����ɹ���\n");
			getchar();
			break;

		case 16:
			printf("���������ȡ���ļ�����\n");
			scanf_s("%s", loadname, NUM_MAX);
			getchar();
			if (LoadTree(&T, loadname) == INFEASIBLE)
				printf("��ȡʧ�ܣ�\n");
			else
				printf("��ȡ�ɹ���\n");

			getchar();
			break;

		case 0:
			break;
		}
	}
	printf("��лʹ�ñ�ϵͳ��\n");
	return 0;
}


/*case1: ����һ���µĶ�����*/
Status CreateBiTree(TNode* T, char* definition) {
	isNull = FALSE;
	i++;
	if (definition[i] != '\0') {
		if (definition[i] == '#') {
			*T = NULL;
			return ERROR;
		}
		else {
			*T = (TNode)malloc(sizeof(BiTNode));
			if ((*T) == NULL) exit(OVERFLOW);
			(*T)->data.key = definition[i];
			(*T)->data.value = 0;
			CreateBiTree(&((*T)->lchild), definition);
			CreateBiTree(&((*T)->rchild), definition);
		}
	}
	return OK;
}

/*case2: ���ٶ�����*/
Status DestroyBiTree(TNode* T) {
	TNode temp;
	temp = *T;
	if (!temp) return ERROR;
	ReDestroyBiTree(temp->lchild);
	ReDestroyBiTree(temp->rchild);
	free(temp);
	T = NULL;
	isNull = TRUE;
	return OK;
}

Status ReDestroyBiTree(TNode t) {
	if (!t) return ERROR;
	ReDestroyBiTree(t->lchild);
	ReDestroyBiTree(t->rchild);
	free(t);
}

/*case3: ��ն�����*/
Status ClearBiTree(TNode* T) {
	if (!T) return ERROR;
	if ((*T)->data.key == '#') return ERROR;
	TNode temp;
	temp = *T;
	ReDestroyBiTree(temp->lchild);
	ReDestroyBiTree(temp->rchild);
	free(temp);
	(*T)->data.key='#';
	return OK;
}


/*case4: �ж϶������Ƿ�Ϊ��*/
Status BiTreeEmpty(TNode T) {
	if (T->data.key == '#') return TRUE;
	else return FALSE;
}

/*case5���ж϶����������*/
Status BiTreeDepth(TNode T) {
	if (!T) return ERROR;
	int L = 0, R = 0;
	L = BiTreeDepth(T->lchild);
	R = BiTreeDepth(T->rchild);
	return R > L ? R + 1 : L + 1;

}

/*case6: �ҵ�Ԫ�����ڽ��*/
TNode LocateNode(TNode T, KeyType e) {
	if (!T) return Findnode;
	if (T->data.key == e)
		Findnode = T;
	else {
		LocateNode(T->lchild, e);
		LocateNode(T->rchild, e);
	}
	return Findnode;
}

/*case7: ���������еĽ�㸳ֵ*/
Status Assign(TNode* T, KeyType e, TElemType value) {
	if (!T) return ERROR;
	TNode* cue;
	cue = (TNode*)malloc(sizeof(BiTNode));
	if (!cue) exit(OVERFLOW);
	*cue = LocateNode(*T, e);
	Findnode = NULL;
	if (*cue == NULL) {
		printf("δ�ҵ���㡣\n");
		return ERROR;
	}
	else {
		(*cue)->data.value = value;
		return OK;
	}
}

/*case8: ����ֵܽ��*/
TNode GetSibling(TNode T, KeyType e) {
	if (!T) return Brothernode;
	if (T->lchild && T->lchild->data.key == e) {
		if (T->rchild)
			Brothernode = T->rchild;
		else {
			printf("�ý��û���ֵܽ�㡣");
			return Brothernode;
		}
	}
	else if (T->rchild && T->rchild->data.key == e) {
		if (T->lchild)
			Brothernode = T->lchild;
		else {
			printf("�ý��û���ֵܽ�㡣");
			return Brothernode;
		}
	}
	GetSibling(T->lchild, e);
	GetSibling(T->rchild, e);
	return Brothernode;
}

/*��ø����*/
TNode GetParent(TNode T, KeyType e) {
	if (!T) return Parentnode;
	if (T->lchild && T->lchild->data.key == e)
		Parentnode = T;
	if (T->rchild && T->rchild->data.key == e)
		Parentnode = T;
	GetParent(T->lchild, e);
	GetParent(T->rchild, e);
	return Parentnode;
}

/*case 9: ������*/
Status InsertNode(TNode* T, KeyType e, int LR, TNode c) {
	if (!T) return ERROR;
	TNode newnode;
	newnode = (TNode)malloc(sizeof(BiTNode));
	if (!newnode) exit(OVERFLOW);
	newnode = LocateNode(*T, e);
	Findnode = NULL;
	if (newnode == NULL) {
		printf("δ�ҵ��ؼ���㡣");
		return ERROR;
	}
	if (LR == 0) {
		if (newnode->lchild) c->rchild = newnode->lchild;
		else c->rchild = NULL;
		newnode->lchild = c;
	}
	else if (LR == 1) {
		if (newnode->rchild) c->rchild = newnode->rchild;
		else c->rchild = NULL;
		newnode->rchild = c;
	}
	else {
		printf("LR����������������0��1��");
		return ERROR;
	}
	return OK;
}

/*case 10: ɾ�����*/
Status DeleteNode(TNode* T, KeyType e) {
	if (!(*T)) return ERROR;
	TNode delnode;
	int LR = 0; //�ж�ɾ������Ǹ��ڵ����or�ҽ��
	delnode = LocateNode(*T, e);
	Findnode = NULL;
	if (delnode == NULL) {
		printf("δ�ҵ��ؼ���㡣");
		return ERROR;
	}
	if (delnode == *T) { /*ɾ�����ڵ�*/
		if (delnode->lchild && delnode->rchild) {
			TNode temprchild = (*T)->rchild;
			*T = (*T)->lchild;
			TNode temp = *T;
			while (temp->rchild) {
				temp = temp->rchild;
			}
			temp->rchild = temprchild;
			return OK;
		}
		else if ((!delnode->lchild) && (!delnode->rchild)) {
			isNull = TRUE;
			*T = NULL;
			printf("����ֻ��һ�����ڵ㣬�������ѱ�ɾ����");
			return OK;
		}
		else {
			if ((*T)->lchild)
				(*T) = (*T)->lchild;
			else
				(*T) = (*T)->rchild;
		}
		return OK;
	}

	TNode parentnode = GetParent(*T, e);
	if (parentnode->rchild == delnode) LR = 1;
	if (delnode->lchild && delnode->rchild) {				/*������Ϊ2*/
		TNode tempnode = delnode->lchild;
		if (LR == 0) {
			parentnode->lchild = delnode->lchild;
			while (tempnode->rchild) {
				tempnode = tempnode->rchild;
			}
			tempnode->rchild = delnode->rchild;
			free(delnode);
		}
		if (LR == 1) {
			parentnode->rchild = delnode->lchild;
			while (tempnode->rchild) {
				tempnode = tempnode->rchild;
			}
			tempnode->rchild = delnode->rchild;
			free(delnode);
		}
		return OK;
	}
	else if ((!delnode->lchild) && (!delnode->rchild)) {		/*������Ϊ0*/
		if (LR == 0)
			parentnode->lchild = NULL;
		if (LR == 1)
			parentnode->rchild = NULL;
		free(delnode);
		return OK;
	}
	else {				/*������Ϊ1*/
		if (delnode->lchild) {
			if (LR == 0)
				parentnode->lchild = delnode->lchild;
			else
				parentnode->rchild = delnode->lchild;
		}
		if (delnode->rchild) {
			if (LR == 0)
				parentnode->lchild = delnode->rchild;
			else
				parentnode->rchild = delnode->rchild;
		}
		return OK;

	}
}

/*case 11: ǰ�����*/
Status PreOrderTraverse(TNode T) {
	if (!T) return ERROR;
	Visit(T);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
	return OK;
}

/*case 12: �������-�ǵݹ�-ʹ��ջʵ��*/
Status InOrderTraverse(TNode T) {
	if (!T) return ERROR;
	stacknode s;
	TNode p = T;
	InitStack(&s);
	while( p || s->top>=0) {
		if (p)
		{
			push(&s, p);
			p = p->lchild;
		}
		else
		{
			p = pop(&s);
			Visit(p);
			p = p->rchild;
		}
	} 
	return OK;
}

/*case 13: �������*/
Status PostOrderTraverse(TNode T) {
	if (!T) return ERROR;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	Visit(T);
	return OK;
}

/*case 14: *�������*/
Status LevelOrderTraverse(TNode T) {
	if (!T) return ERROR;
	Queue q = NULL;
	TNode p = T;
	InitQueue(&q);
	EnQueue(&q, p);
	while (q->front != q->rear) {
		p = q->data[q->front];
		if (p->lchild) EnQueue(&q, p->lchild);
		if (p->rchild) EnQueue(&q, p->rchild);
		Visit(OutQueue(&q));
	}
	return OK;
}

void InitQueue(Queue* q) {
	*q = (Queue)malloc(sizeof(queue));
	if ((*q) == NULL) exit(OVERFLOW);
	(*q)->front = 0;
	(*q)->rear = 0;
}

Status EnQueue(Queue* lq, TNode ch) {		/*���*/
	if ((*lq)->rear >= LIST_INIT_SIZE)
		return ERROR;
	(*lq)->data[(*lq)->rear] = ch;
	(*lq)->rear++;
	return OK;
}


TNode OutQueue(Queue* q) {					/*����*/
	if ((*q)->front == (*q)->rear)
		return ERROR;
	TNode tempnode = (*q)->data[(*q)->front];
	(*q)->front++;
	return tempnode;
}

Status Visit(TNode T) {
	if (T == NULL) return ERROR;
	printf("%c : %d   ", T->data.key, T->data.value);
	return OK;
}

/*case15��������*/
Status SaveTree(TNode T, char* path) {
	if (!T) return ERROR;
	errno_t err = 0;
	err = fopen_s(&tree, path, "wb");
	if (err) {
		printf("·������");
		return INFEASIBLE;
	}
	ReSaveTree(T);
	fclose(tree);
	return OK;
}

Status ReSaveTree(TNode T) {
	if (!T) {
		fprintf(tree, "%c:%d\n",'#',0);
		return ERROR;
	}
	fprintf(tree, "%c:%d\n", T->data.key, T->data.value);
	ReSaveTree(T->lchild);
	ReSaveTree(T->rchild);
	return OK;
}

/*case15����ȡ��*/
Status LoadTree(TNode* T, char* path)
{
	errno_t err = 0;
	err = fopen_s(&tree, path, "rb");
	if (err) {
		printf("·������");
		return INFEASIBLE;
	}
	fseek(tree, 0, SEEK_END);	/*����ļ���С*/
	int filesize = ftell(tree);
	rewind(tree);
	char* space = (char*)malloc(filesize);
	if (filesize == 0) {
		printf("�ļ�Ϊ�ա�");
		return ERROR;
	}
	while (fread(space, filesize, 1, tree))
		printf("%s",space);
	fclose(tree);
	return OK;
}

void InitStack(stacknode* s) {
	*s = (stacknode)malloc(sizeof(Stack));
	if ((*s) == NULL) exit(OVERFLOW);
	(*s)->top = -1;
}

Status push(stacknode* s, TNode T) {	
	if ((*s)->top > LIST_INIT_SIZE) return ERROR;
	(*s)->top++;	
	(*s)->data[(*s)->top] = T;
	return OK;

}

TNode pop(stacknode* s) {
	if ((*s)->top < 0) return ERROR;
	TNode outnode = (*s)->data[(*s)->top];
	(*s)->top--;
	return outnode;
}