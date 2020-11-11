#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR -1
#define INFEASIBLE -1
#define OVERFLOW -2

#define MAX_VERTEX_NUM 100
#define LIST_INIT_SIZE 100
#define NUM_MAX 30
typedef int Status;
typedef int ValueType;
typedef int KeyType;
typedef int InfoType;

static bool isNull = TRUE;
static int DeleteNum = 0;
FILE* graph;

typedef struct VertexType/*顶点存放的数据的结构类型*/
{
	KeyType key; /*唯一标识*/
	ValueType value;
}VertexType;

typedef struct ArcNode {
	int adjvex;			//该弧所指向的顶点的位置
	struct ArcNode* nextarc;	//指向下一条弧的指针
	InfoType info;		//该弧相关信息
}ArcNode;

typedef struct VNode {
	VertexType data;		//顶点信息
	ArcNode* firstarc;		//指向第一条依附该顶点的弧的指针
}VNode, AdjList[MAX_VERTEX_NUM];


typedef struct QueueList {
	VNode data[LIST_INIT_SIZE];
	int front;
	int rear;
}queue, * Queue;

typedef struct ALGRAPH {
	AdjList vertices;
	int vexnum, arcnum;		//图的当前节点数和弧数
	int book[MAX_VERTEX_NUM] = { 0 };
} ALG, * ALGraph;


/*Function defined*/

Status CreateGraph(ALGraph* G);					/*创建图*/
Status DestroyGraph(ALGraph* G);				/*销毁图*/
int LocateVex(ALGraph G, KeyType u);				/*查找顶点*/
Status PutVex(ALGraph* G, KeyType u, ValueType v);	/*顶点赋值*/
Status FirstAdjVex(ALGraph G, int index);			/*获得第一邻接点*/
Status NextAdjVex(ALGraph G, int v, int w);			/*获得下一邻接点*/
Status InsertVex(ALGraph* G, VertexType vnode);		/*插入顶点*/
Status DeleteVex(ALGraph* G, KeyType vnode);		/*删除顶点*/
Status InsertArc(ALGraph* G, KeyType v, KeyType w);		/*插入弧*/
Status DeleteArc(ALGraph* G, KeyType v, KeyType w);		/*删除弧*/
Status DFSTraverse(ALGraph* G);			/*深度优先搜索遍历*/
void dfs(ALGraph* G, int i);
Status BFSTraverse(ALGraph* G);			/*广度优先搜索遍历*/
Status Visit(VNode);
void InitQueue(Queue* q);							/*新建队列*/
Status EnQueue(Queue* q, VNode T);					/*入队*/
VNode OutQueue(Queue* q);							/*出队*/


int main(void) {
	int op = 1, index, vp, wp;
	KeyType find, insert;
	ValueType value;
	ALGraph G = NULL;
	VertexType* vnode;
	char filename[NUM_MAX], loadname[NUM_MAX];
	while (op) {
		system("cls");
		printf("\n\n---------------Menu for Linear Table On Graph--------------\n");
		printf("	1. CreateGraph			7.  InsertVex\n");
		printf("	2. DestroyGraph			8.  DeleteVex\n");
		printf("	3. LocateVex			9.  InsertArc\n");
		printf("	4. PutVex			10. DeleteArc \n");
		printf("	5. FirstAdjVex			11. DFSTraverse\n");
		printf("	6. NextAdjVex			12. BFSTraverse\n");
		printf("	0. Exit\n\n");
		printf("----------------------------------------------------------------\n");
		printf("选择你的操作:\n");
		scanf_s("%d", &op);
		getchar();
		switch (op)
		{
		case 1:
			if (CreateGraph(&G) == OK)
				printf("创建成功！\n");
			else
				printf("创建失败！\n");
			getchar();
			break;

		case 2:
			if (isNull == TRUE) {
				printf("图不存在！\n");
				getchar();
				break;
			}
			if (DestroyGraph(&G) == OK)
				printf("销毁成功！\n");
			else
				printf("销毁失败！\n");
			getchar();
			break;

		case 3:
			if (isNull == TRUE) {
				printf("图不存在！\n");
				getchar();
				break;
			}
			printf("请输入你想查找的顶点的关键字：");
			scanf_s("%d", &find);
			getchar();
			index = LocateVex(G, find);
			if (index != ERROR) {
				printf("顶点信息为：   ");
				Visit(G->vertices[index]);
				printf("顶点在邻接表内第%d位.\n", index);
			}
			else {
				printf("查找失败！");
			}
			getchar();
			break;

		case 4:
			if (isNull == TRUE) {
				printf("图不存在！\n");
				getchar();
				break;
			}
			printf("请输入你想赋值的顶点的关键字：");
			scanf_s("%d", &find);
			getchar();
			index = LocateVex(G, find);
			if (index != ERROR) {
				printf("请输入你想赋的值：");
				scanf_s("%d", &value);
				getchar();
			}
			if (PutVex(&G, find, value) == OK)
				printf("赋值成功！\n");
			else
				printf("赋值失败！\n");
			getchar();
			break;

		case 5:
			if (isNull == TRUE) {
				printf("图不存在！\n");
				getchar();
				break;
			}
			printf("请输入你想查找的顶点的位序：");
			scanf_s("%d", &index);
			getchar();
			if (index > G->vexnum + DeleteNum || index < 0) {
				printf("输入位序不符合要求！\n");
				getchar();
				break;
			}
			if (FirstAdjVex(G, index) != ERROR)
				printf("该顶点的第一个临接顶点为： %d！\n", FirstAdjVex(G, index));
			else
				printf("查找失败！\n");
			getchar();
			break;

		case 6:
			if (isNull == TRUE) {
				printf("图不存在！\n");
				getchar();
				break;
			}
			printf("请输入你想查找的顶点v的位序：");
			scanf_s("%d", &vp);
			getchar();
			printf("请输入你想查找的顶点w的位序：");
			scanf_s("%d", &wp);
			getchar();
			if (vp == wp || vp > G->vexnum + DeleteNum || wp > G->vexnum + DeleteNum) {
				printf("输入有误，查找失败。\n");
			}
			else if (NextAdjVex(G, vp, wp) != ERROR) {
				printf("v相对于w的下一个临界顶点的位置为； %d！\n", NextAdjVex(G, vp, wp));
			}
			else
				printf("查找失败！\n");
			getchar();
			break;

		case 7:
			if (isNull == TRUE) {
				printf("图不存在！\n");
				getchar();
				break;
			}
			printf("请输入你想插入的顶点的关键字：");
			scanf_s("%d", &insert);
			getchar();
			printf("请输入你想插入的顶点的值：");
			scanf_s("%d", &value);
			getchar();
			vnode = (VertexType*)malloc(sizeof(VertexType));
			if (!vnode) exit(OVERFLOW);
			vnode->key = insert;
			vnode->value = value;
			if (InsertVex(&G, *vnode) == OK)
				printf("插入成功！\n");
			else
				printf("插入失败！\n");
			getchar();
			break;

		case 8:
			if (isNull == TRUE) {
				printf("图不存在！\n");
				getchar();
				break;
			}
			printf("请输入你想删除的顶点的关键字：");
			scanf_s("%d", &find);
			getchar();
			if (DeleteVex(&G, find) == OK)
				printf("删除成功！\n");
			else
				printf("删除失败！\n");
			getchar();
			break;

		case 9:
			if (isNull == TRUE) {
				printf("图不存在！\n");
				getchar();
				break;
			}
			printf("请输入你想插入的弧尾的关键字：");
			scanf_s("%d", &vp);
			getchar();
			printf("请输入你想插入的弧头的关键字：");
			scanf_s("%d", &wp);
			getchar();
			if (InsertArc(&G, vp, wp) == OK)
				printf("插入成功！\n");
			else
				printf("插入失败！\n");
			getchar();
			break;

		case 10:
			if (isNull == TRUE) {
				printf("图不存在！\n");
				getchar();
				break;
			}
			printf("请输入你想删除的弧尾的关键字：");
			scanf_s("%d", &vp);
			getchar();
			printf("请输入你想删除的弧头的关键字：");
			scanf_s("%d", &wp);
			getchar();
			if (DeleteArc(&G, vp, wp) == OK)
				printf("删除成功！\n");
			else
				printf("删除失败！\n");
			getchar();
			break;

		case 11:
			if (isNull == TRUE) {
				printf("图不存在！\n");
				getchar();
				break;
			}
			printf("对图进行深度优先搜索遍历如下：\n");
			DFSTraverse(&G);
			getchar();
			break;

		case 12:
			if (isNull == TRUE) {
				printf("图不存在！\n");
				getchar();
				break;
			}
			printf("对图进行广度优先搜索遍历如下：\n");
			BFSTraverse(&G);
			getchar();
			break;
		case 0:
			break;
		}
	}
	printf("感谢使用本系统！\n");
	return 0;
}


/*case1: 创建图*/
Status CreateGraph(ALGraph* G) {
	KeyType key;
	ValueType value;
	VNode* vnode = (VNode*)malloc(sizeof(VNode));
	isNull = FALSE;
	*G = (ALGraph)malloc(sizeof(ALG));
	if (!G) exit(OVERFLOW);
	(*G)->vexnum = 0;
	(*G)->arcnum = 0;
	printf("请输入顶点的key值（唯一）：");
	scanf_s("%d", &key);
	getchar();
	printf("请为该顶点赋值：");
	scanf_s("%d", &value);
	getchar();
	if (key) {
		vnode->data.key = key;
		vnode->data.value = value;
		vnode->firstarc = NULL;
	}
	(*G)->vertices[(*G)->vexnum] = *vnode;
	(*G)->vexnum++;
	return OK;
}


/*case2: 销毁图*/
Status DestroyGraph(ALGraph* G) {
	if (!G) return ERROR;
	isNull = TRUE;
	VNode* vnode;
	ArcNode* del, * temp = NULL;
	for (int i = 0; i < (*G)->vexnum + DeleteNum; i++) {
		del = (*G)->vertices[i].firstarc;
		while (del != NULL) {
			temp = del->nextarc;
			free(del);
			del = temp;
		}
	}
	*G = NULL;
	return OK;
}

/*case3: 查找顶点*/
int LocateVex(ALGraph G, KeyType u) {
	for (int i = 0; i < (*G).vexnum + DeleteNum; i++) {
		if ((*G).vertices[i].data.key == u) {
			return i;
		}
	}
	return ERROR;
}

/*case4: 顶点赋值*/
Status PutVex(ALGraph* G, KeyType u, ValueType v) {
	if (!G) return ERROR;
	for (int i = 0; i < (*G)->vexnum + DeleteNum; i++) {
		if ((*G)->vertices[i].data.key == u) {
			(*G)->vertices[i].data.value = v;
			return OK;
		}
	}
	return ERROR;
}

/*case5：获得第一邻接点*/
Status FirstAdjVex(ALGraph G, int index) {
	ArcNode* arc = NULL;
	if (index < (*G).vexnum + DeleteNum) {
		if ((*G).vertices[index].firstarc) {
			arc = (*G).vertices[index].firstarc;
			return arc->adjvex;
		}
	}
	return ERROR;
}

/*case6: 获得下一邻接点*/
Status NextAdjVex(ALGraph G, int v, int w) {
	ArcNode* arc = NULL;
	if (v == w) 	return ERROR;
	if (v < (*G).vexnum + DeleteNum && w < (*G).vexnum + DeleteNum) {
		arc = (*G).vertices[v].firstarc;
		while (arc) {
			if (arc->adjvex == w && arc->nextarc)
				return arc->nextarc->adjvex;
			arc = arc->nextarc;
		}
	}
	return ERROR;
}

/*case7: 插入顶点*/
Status InsertVex(ALGraph* G, VertexType vnode) {
	if (!G) return ERROR;
	if (LocateVex(*G, vnode.key) != ERROR) {
		printf("该关键字已存在！");
		return ERROR;
	}
	(*G)->vertices[(*G)->vexnum].data = vnode;
	(*G)->vertices[(*G)->vexnum].firstarc = NULL;
	(*G)->vexnum++;
	return OK;
}

/*case8: 删除顶点*/
Status DeleteVex(ALGraph* G, KeyType vnode) {
	if (!G) return ERROR;
	ArcNode* temp;
	int num = 0;
	if (LocateVex(*G, vnode) == ERROR) {
		printf("找不到该顶点！");
		return ERROR;
	}
	for (int i = 0; i < (*G)->vexnum + DeleteNum; i++) {
		temp = (*G)->vertices[i].firstarc;
		if (!temp) continue;
		if ((*G)->vertices[i].data.key == vnode) {//删顶点
			(*G)->vertices[i].data.key = 0;
			(*G)->vexnum--;
			while (temp) {
				num++;
				temp = temp->nextarc;
			}
			(*G)->vertices[i].firstarc = NULL;
			(*G)->arcnum = (*G)->arcnum - num;
			num = 0;
		}
		else {	//删除弧
			if (temp->adjvex == LocateVex(*G, vnode)) {
				(*G)->vertices[i].firstarc = temp->nextarc;
				(*G)->arcnum--;
			}
			while (temp->nextarc) {
				if (temp->nextarc->adjvex == LocateVex(*G, vnode)) {
					temp->nextarc = temp->nextarc->nextarc;
					(*G)->arcnum--;
				}
				temp = temp->nextarc;
			}
		}

	}
	DeleteNum++;
	return OK;
}

/*case 9: 插入弧*/
Status InsertArc(ALGraph* G, KeyType v, KeyType w) {
	if (!G) return ERROR;
	int insert;
	ArcNode* temp, * p;
	if (LocateVex(*G, v) != ERROR && LocateVex(*G, w) != ERROR) {
		insert = LocateVex(*G, v);
		temp = (*G)->vertices[insert].firstarc;
		if (!temp) {
			(*G)->vertices[insert].firstarc = (ArcNode*)malloc(sizeof(ArcNode));
			(*G)->vertices[insert].firstarc->adjvex = LocateVex(*G, w);
			(*G)->vertices[insert].firstarc->info = 0;
			(*G)->vertices[insert].firstarc->nextarc = NULL;
			(*G)->arcnum++;
			return OK;
		}
		while (temp->nextarc) {
			if ((*G)->vertices[temp->adjvex].data.key == w) {
				printf("该弧已存在。 ");
				return ERROR;
			}
			temp = temp->nextarc;
		}
		if ((*G)->vertices[temp->adjvex].data.key == w) {
			printf("该弧已存在。 ");
			return ERROR;
		}
		p = temp;
		temp = temp->nextarc;
		temp = (ArcNode*)malloc(sizeof(ArcNode));
		temp->adjvex = LocateVex(*G, w);
		temp->info = 0;
		temp->nextarc = NULL;
		p->nextarc = temp;
		(*G)->arcnum++;
		return OK;
	}
	return ERROR;

}

/*case 10: 删除弧*/
Status DeleteArc(ALGraph* G, KeyType v, KeyType w) {
	if (!G) return ERROR;
	ArcNode* temp;
	int indexv, indexw;
	if (LocateVex(*G, v) != ERROR && LocateVex(*G, w) != ERROR) {
		indexv = LocateVex(*G, v);
		indexw = LocateVex(*G, w);
		temp = (*G)->vertices[indexv].firstarc;
		if (!temp) {
			printf("该顶点不是弧尾！");
			return ERROR;
		}
		if (temp && temp->adjvex == indexw) {
			(*G)->vertices[indexv].firstarc = temp->nextarc;
			(*G)->arcnum--;
			return OK;
		}
		while (temp->nextarc) {
			if (temp->nextarc->adjvex == indexw) {
				temp->nextarc = temp->nextarc->nextarc;
				(*G)->arcnum--;
				return OK;
			}
			temp = temp->nextarc;
		}
		printf("不存在从v指向w的弧！");
	}
	return ERROR;
}

/*case 11: 深度优先搜索遍历*/
Status DFSTraverse(ALGraph* G) {
	if (!G) return ERROR;
	int i = 0;
	for (int j = 0; j < MAX_VERTEX_NUM; j++) (*G)->book[j] = 0;
	for (i = 0; i < (*G)->vexnum + DeleteNum; i++) {
		if (!(*G)->book[i])
			dfs(G, i);
	}
	return OK;
}

void dfs(ALGraph* G, int i) {
	ArcNode* a;
	(*G)->book[i] = 1;
	Visit((*G)->vertices[i]);
	a = (*G)->vertices[i].firstarc;

	while (a) {
		if ((*G)->book[a->adjvex] == 0)
		{
			dfs(G, a->adjvex);
		}
		a = a->nextarc;
	}

}

/*case 12: 广度优先搜索遍历*/
Status BFSTraverse(ALGraph* G) {
	if (!G) return ERROR;
	Queue q;
	ArcNode* arc;
	int i = 0;
	VNode v = (*G)->vertices[0];
	for (int j = 0; j < MAX_VERTEX_NUM; j++) (*G)->book[j] = 0;
	InitQueue(&q);
	EnQueue(&q, v);
	while (q->front != q->rear) {
		v = OutQueue(&q);
		if ((*G)->book[LocateVex(*G, v.data.key)] == 0) {
			Visit(v);
			(*G)->book[LocateVex(*G, v.data.key)] = 1;
		}
		arc = v.firstarc;
		while (arc) {
			if ((*G)->book[arc->adjvex] == 0) {
				Visit((*G)->vertices[arc->adjvex]);
				(*G)->book[arc->adjvex] = 1;
				EnQueue(&q, (*G)->vertices[arc->adjvex]);
			}
			arc = arc->nextarc;
		}
	}
	for (i = 0; i < (*G)->vexnum + DeleteNum; i++) {
		if (!(*G)->book[i])
			Visit((*G)->vertices[i]);
	}
	return OK;
}

void InitQueue(Queue* q) {
	*q = (Queue)malloc(sizeof(queue));
	if ((*q) == NULL) exit(OVERFLOW);
	(*q)->front = 0;
	(*q)->rear = 0;
}

Status EnQueue(Queue* lq, VNode ch) {		/*入队*/
	if ((*lq)->rear >= LIST_INIT_SIZE)
		return ERROR;
	(*lq)->data[(*lq)->rear] = ch;
	(*lq)->rear++;
	return OK;
}

VNode OutQueue(Queue* q) {					/*出队*/
	VNode tempnode = (*q)->data[(*q)->front];
	(*q)->front++;
	return tempnode;
}

Status Visit(VNode v) {
	if (v.data.key == 0) return ERROR;
	printf("%d: %d\n", v.data.key, v.data.value);
	return OK;
}
