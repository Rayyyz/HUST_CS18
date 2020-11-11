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

typedef struct ElemType/*树结点存放的数据的结构类型*/
{
	KeyType key; /*唯一标识*/
	TElemType value;
}ElemType;

typedef struct BiTNode { /*树的每个结点的结构*/
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

static TNode Findnode = NULL;		/*全局变量，查找结点*/
static TNode Brothernode = NULL;	/*全局变量，兄弟结点*/
static TNode Parentnode = NULL;		/*全局变量，双亲节点*/
FILE* tree = NULL;					/*全局变量，文件指针*/

/*Function defined*/
Status CreateBiTree(TNode* T, char* definition);		/*生成二叉树*/
Status DestroyBiTree(TNode* T);								/*销毁二叉树*/
Status ReDestroyBiTree(TNode temp);							/*销毁二叉树-递归用*/
Status ClearBiTree(TNode* T);								/*清空二叉树*/
Status BiTreeEmpty(TNode T);								/*判定空二叉树*/
Status BiTreeDepth(TNode T);								/*求二叉树深度*/
TNode LocateNode(TNode T, KeyType e);						/*查找结点*/
Status Assign(TNode* T, KeyType e, TElemType value);		/*结点赋值*/
TNode GetSibling(TNode T, KeyType e);						/*获得兄弟结点*/
TNode GetParent(TNode T, KeyType e);						/*获得父节点*/
Status InsertNode(TNode* T, KeyType e, int LR, TNode c);	/*插入结点*/
Status DeleteNode(TNode* T, KeyType e);						/*删除结点*/
Status PreOrderTraverse(TNode T);							/*前序遍历*/
Status InOrderTraverse(TNode T);					/*中序遍历*/
Status PostOrderTraverse(TNode T);					/*后序遍历*/
Status LevelOrderTraverse(TNode T);					/*按层遍历*/
Status Visit(TNode T);								/*访问结点*/
void InitQueue(Queue* q);							/*新建队列*/
Status EnQueue(Queue* q, TNode T);					/*入队*/
TNode OutQueue(Queue* q);							/*出队*/
Status SaveTree(TNode T, char* path);				/*保存树*/
Status ReSaveTree(TNode T);
Status LoadTree(TNode* T, char* path);				/*读取树*/
void InitStack(stacknode* s);					/*建立栈*/
Status push(stacknode* s ,TNode T);				/*入栈*/
TNode pop(stacknode* s);						/*出栈*/



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
		printf("选择你的操作:\n");
		scanf_s("%d", &op);
		getchar();
		switch (op)
		{
		case 1:
			T = NULL;
			printf("请输入带空子树的前序列：(空结点输入‘#’)\n");
			gets_s(definition);
			if (CreateBiTree(&T, definition) == OK) {
				printf("二叉树创建成功！\n");
			}
			else {
				printf("二叉树创建失败！\n");
			}
			getchar();
			break;

		case 2:
			if (isNull == TRUE) {
				printf("二叉树不存在！\n");
				getchar();
				break;
			}
			if (DestroyBiTree(&T) == OK)
				printf("二叉树销毁成功！\n");
			else
				printf("二叉树销毁失败！\n");
			getchar();
			break;

		case 3:
			if (isNull == TRUE) {
				printf("二叉树不存在！\n");
				getchar();
				break;
			}
			if (ClearBiTree(&T) == TRUE)
				printf("二叉树清空成功！\n");
			else
				printf("二叉树为空！\n");
			getchar();
			break;

		case 4:
			if (isNull == TRUE) {
				printf("二叉树不存在！\n");
				getchar();
				break;
			}
			if (BiTreeEmpty(T) == TRUE)
				printf("二叉树为空！\n");
			else
				printf("二叉树不为空！\n");
			getchar();
			break;

		case 5:
			if (isNull == TRUE) {
				printf("二叉树不存在！\n");
				getchar();
				break;
			}
			if (BiTreeEmpty(T) == TRUE)
				printf("二叉树为空树，深度为0.\n");
			else
				printf("二叉树的深度为%d.\n", BiTreeDepth(T));
			getchar();
			break;

		case 6:
			if (isNull == TRUE) {
				printf("二叉树不存在！\n");
				getchar();
				break;
			}
			printf("输入你想查找的元素的关键字：\n");
			scanf_s("%c", &find);
			getchar();
			FindNode = LocateNode(T, find);
			Findnode = NULL;
			if (!FindNode)
				printf("查找失败！");
			else {
				printf("查找成功！结点信息如下：\n");
				Visit(FindNode);
			}
			getchar();
			break;

		case 7:
			if (isNull == TRUE) {
				printf("二叉树不存在！\n");
				getchar();
				break;
			}
			printf("输入你想赋值的元素的关键字：\n");
			scanf_s("%c", &name);
			getchar();
			printf("输入你想赋予的数值：\n");
			scanf_s("%d", &value);
			getchar();
			if (Assign(&T, name, value) == OK)
				printf("赋值成功！\n");
			else
				printf("赋值失败！\n");
			getchar();
			break;

		case 8:
			if (isNull == TRUE) {
				printf("二叉树不存在！\n");
				getchar();
				break;
			}
			printf("输入你想查找兄弟结点的元素的关键字：\n");
			scanf_s("%c", &find);
			getchar();
			if (BiTreeEmpty(T) == TRUE) {
				printf("二叉树为空！");
				getchar();
				break;
			}
			if (find == T->data.key) {
				printf("查找失败！该结点为树的根结点。\n");
				getchar();
				break;
			}
			if (LocateNode(T, find) == NULL) {
				Findnode = NULL;
				printf("找不到该结点！\n");
				getchar();
				break;
			}
			BrotherNode = GetSibling(T, find);
			Brothernode = NULL;
			if (BrotherNode) {
				printf("查找成功！该结点的兄弟结点信息如下：\n");
				Visit(BrotherNode);
			}
			else
				printf("查找失败！");
			getchar();
			break;

		case 9:
			if (isNull == TRUE) {
				printf("二叉树不存在！\n");
				getchar();
				break;
			}
			printf("输入你想新建的元素的关键字：\n");
			scanf_s("%c", &name);
			getchar();
			printf("输入它对应的数值：\n");
			scanf_s("%d", &value);
			getchar();
			printf("输入你想插入的位置元素的关键字：\n");
			scanf_s("%c", &find);
			getchar();
			printf("你想插入到该元素的左结点还是右结点？(左0右1)：\n");
			scanf_s("%d", &LR);
			getchar();
			if (LocateNode(T, name) != NULL) {
				Findnode = NULL;
				printf("该关键字已有！\n");
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
					printf("插入结点成功！\n");
				}
				else
					printf("插入失败！\n");
			}
			else
				printf("插入失败！\n");
			getchar();
			break;

		case 10:
			if (isNull == TRUE) {
				printf("二叉树不存在！\n");
				getchar();
				break;
			}
			printf("输入你想删除的元素的关键字：\n");
			scanf_s("%c", &name);
			getchar();
			if (LocateNode(T, name) != NULL) {
				FindNode = NULL;
				if (DeleteNode(&T, name) == OK)
					printf("删除结点成功！\n");
				else
					printf("删除失败！\n");
			}
			else
				printf("删除失败！\n");
			getchar();
			break;

		case 11:
			if (isNull == TRUE) {
				printf("二叉树不存在！\n");
				getchar();
				break;
			}
			PreOrderTraverse(T);
			getchar();
			break;

		case 12:
			if (isNull == TRUE) {
				printf("二叉树不存在！\n");
				getchar();
				break;
			}
			InOrderTraverse(T);
			getchar();
			break;

		case 13:
			if (isNull == TRUE) {
				printf("二叉树不存在！\n");
				getchar();
				break;
			}
			PostOrderTraverse(T);
			getchar();
			break;

		case 14:
			if (isNull == TRUE) {
				printf("二叉树不存在！\n");
				getchar();
				break;
			}
			LevelOrderTraverse(T);
			getchar();
			break;
		case 15:
			if (isNull == TRUE) {
				printf("二叉树不存在！\n");
				getchar();
				break;
			}
			printf("请输入想存储的文件名：\n");
			scanf_s("%s", filename, NUM_MAX);
			getchar();
			if (SaveTree(T, filename) == INFEASIBLE)
				printf("保存失败！\n");
			if (SaveTree(T, filename) == ERROR)
				printf("保存失败！\n");
			else
				printf("保存成功！\n");
			getchar();
			break;

		case 16:
			printf("请输入想读取的文件名：\n");
			scanf_s("%s", loadname, NUM_MAX);
			getchar();
			if (LoadTree(&T, loadname) == INFEASIBLE)
				printf("读取失败！\n");
			else
				printf("读取成功！\n");

			getchar();
			break;

		case 0:
			break;
		}
	}
	printf("感谢使用本系统！\n");
	return 0;
}


/*case1: 构建一个新的二叉树*/
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

/*case2: 销毁二叉树*/
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

/*case3: 清空二叉树*/
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


/*case4: 判断二叉树是否为空*/
Status BiTreeEmpty(TNode T) {
	if (T->data.key == '#') return TRUE;
	else return FALSE;
}

/*case5：判断二叉树的深度*/
Status BiTreeDepth(TNode T) {
	if (!T) return ERROR;
	int L = 0, R = 0;
	L = BiTreeDepth(T->lchild);
	R = BiTreeDepth(T->rchild);
	return R > L ? R + 1 : L + 1;

}

/*case6: 找到元素所在结点*/
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

/*case7: 给二叉树中的结点赋值*/
Status Assign(TNode* T, KeyType e, TElemType value) {
	if (!T) return ERROR;
	TNode* cue;
	cue = (TNode*)malloc(sizeof(BiTNode));
	if (!cue) exit(OVERFLOW);
	*cue = LocateNode(*T, e);
	Findnode = NULL;
	if (*cue == NULL) {
		printf("未找到结点。\n");
		return ERROR;
	}
	else {
		(*cue)->data.value = value;
		return OK;
	}
}

/*case8: 获得兄弟结点*/
TNode GetSibling(TNode T, KeyType e) {
	if (!T) return Brothernode;
	if (T->lchild && T->lchild->data.key == e) {
		if (T->rchild)
			Brothernode = T->rchild;
		else {
			printf("该结点没有兄弟结点。");
			return Brothernode;
		}
	}
	else if (T->rchild && T->rchild->data.key == e) {
		if (T->lchild)
			Brothernode = T->lchild;
		else {
			printf("该结点没有兄弟结点。");
			return Brothernode;
		}
	}
	GetSibling(T->lchild, e);
	GetSibling(T->rchild, e);
	return Brothernode;
}

/*获得父结点*/
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

/*case 9: 插入结点*/
Status InsertNode(TNode* T, KeyType e, int LR, TNode c) {
	if (!T) return ERROR;
	TNode newnode;
	newnode = (TNode)malloc(sizeof(BiTNode));
	if (!newnode) exit(OVERFLOW);
	newnode = LocateNode(*T, e);
	Findnode = NULL;
	if (newnode == NULL) {
		printf("未找到关键结点。");
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
		printf("LR的输入有误。请输入0或1。");
		return ERROR;
	}
	return OK;
}

/*case 10: 删除结点*/
Status DeleteNode(TNode* T, KeyType e) {
	if (!(*T)) return ERROR;
	TNode delnode;
	int LR = 0; //判断删除结点是父节点的左or右结点
	delnode = LocateNode(*T, e);
	Findnode = NULL;
	if (delnode == NULL) {
		printf("未找到关键结点。");
		return ERROR;
	}
	if (delnode == *T) { /*删除根节点*/
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
			printf("该树只有一个根节点，二叉树已被删除！");
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
	if (delnode->lchild && delnode->rchild) {				/*结点度数为2*/
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
	else if ((!delnode->lchild) && (!delnode->rchild)) {		/*结点度数为0*/
		if (LR == 0)
			parentnode->lchild = NULL;
		if (LR == 1)
			parentnode->rchild = NULL;
		free(delnode);
		return OK;
	}
	else {				/*结点度数为1*/
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

/*case 11: 前序遍历*/
Status PreOrderTraverse(TNode T) {
	if (!T) return ERROR;
	Visit(T);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
	return OK;
}

/*case 12: 中序遍历-非递归-使用栈实现*/
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

/*case 13: 后序遍历*/
Status PostOrderTraverse(TNode T) {
	if (!T) return ERROR;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	Visit(T);
	return OK;
}

/*case 14: *按层遍历*/
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

Status EnQueue(Queue* lq, TNode ch) {		/*入队*/
	if ((*lq)->rear >= LIST_INIT_SIZE)
		return ERROR;
	(*lq)->data[(*lq)->rear] = ch;
	(*lq)->rear++;
	return OK;
}


TNode OutQueue(Queue* q) {					/*出队*/
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

/*case15：保存树*/
Status SaveTree(TNode T, char* path) {
	if (!T) return ERROR;
	errno_t err = 0;
	err = fopen_s(&tree, path, "wb");
	if (err) {
		printf("路径错误。");
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

/*case15：读取树*/
Status LoadTree(TNode* T, char* path)
{
	errno_t err = 0;
	err = fopen_s(&tree, path, "rb");
	if (err) {
		printf("路径错误。");
		return INFEASIBLE;
	}
	fseek(tree, 0, SEEK_END);	/*求得文件大小*/
	int filesize = ftell(tree);
	rewind(tree);
	char* space = (char*)malloc(filesize);
	if (filesize == 0) {
		printf("文件为空。");
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