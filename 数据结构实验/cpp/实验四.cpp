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

typedef struct VertexType/*�����ŵ����ݵĽṹ����*/
{
	KeyType key; /*Ψһ��ʶ*/
	ValueType value;
}VertexType;

typedef struct ArcNode {
	int adjvex;			//�û���ָ��Ķ����λ��
	struct ArcNode* nextarc;	//ָ����һ������ָ��
	InfoType info;		//�û������Ϣ
}ArcNode;

typedef struct VNode {
	VertexType data;		//������Ϣ
	ArcNode* firstarc;		//ָ���һ�������ö���Ļ���ָ��
}VNode, AdjList[MAX_VERTEX_NUM];


typedef struct QueueList {
	VNode data[LIST_INIT_SIZE];
	int front;
	int rear;
}queue, * Queue;

typedef struct ALGRAPH {
	AdjList vertices;
	int vexnum, arcnum;		//ͼ�ĵ�ǰ�ڵ����ͻ���
	int book[MAX_VERTEX_NUM] = { 0 };
} ALG, * ALGraph;


/*Function defined*/

Status CreateGraph(ALGraph* G);					/*����ͼ*/
Status DestroyGraph(ALGraph* G);				/*����ͼ*/
int LocateVex(ALGraph G, KeyType u);				/*���Ҷ���*/
Status PutVex(ALGraph* G, KeyType u, ValueType v);	/*���㸳ֵ*/
Status FirstAdjVex(ALGraph G, int index);			/*��õ�һ�ڽӵ�*/
Status NextAdjVex(ALGraph G, int v, int w);			/*�����һ�ڽӵ�*/
Status InsertVex(ALGraph* G, VertexType vnode);		/*���붥��*/
Status DeleteVex(ALGraph* G, KeyType vnode);		/*ɾ������*/
Status InsertArc(ALGraph* G, KeyType v, KeyType w);		/*���뻡*/
Status DeleteArc(ALGraph* G, KeyType v, KeyType w);		/*ɾ����*/
Status DFSTraverse(ALGraph* G);			/*���������������*/
void dfs(ALGraph* G, int i);
Status BFSTraverse(ALGraph* G);			/*���������������*/
Status Visit(VNode);
void InitQueue(Queue* q);							/*�½�����*/
Status EnQueue(Queue* q, VNode T);					/*���*/
VNode OutQueue(Queue* q);							/*����*/


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
		printf("ѡ����Ĳ���:\n");
		scanf_s("%d", &op);
		getchar();
		switch (op)
		{
		case 1:
			if (CreateGraph(&G) == OK)
				printf("�����ɹ���\n");
			else
				printf("����ʧ�ܣ�\n");
			getchar();
			break;

		case 2:
			if (isNull == TRUE) {
				printf("ͼ�����ڣ�\n");
				getchar();
				break;
			}
			if (DestroyGraph(&G) == OK)
				printf("���ٳɹ���\n");
			else
				printf("����ʧ�ܣ�\n");
			getchar();
			break;

		case 3:
			if (isNull == TRUE) {
				printf("ͼ�����ڣ�\n");
				getchar();
				break;
			}
			printf("������������ҵĶ���Ĺؼ��֣�");
			scanf_s("%d", &find);
			getchar();
			index = LocateVex(G, find);
			if (index != ERROR) {
				printf("������ϢΪ��   ");
				Visit(G->vertices[index]);
				printf("�������ڽӱ��ڵ�%dλ.\n", index);
			}
			else {
				printf("����ʧ�ܣ�");
			}
			getchar();
			break;

		case 4:
			if (isNull == TRUE) {
				printf("ͼ�����ڣ�\n");
				getchar();
				break;
			}
			printf("���������븳ֵ�Ķ���Ĺؼ��֣�");
			scanf_s("%d", &find);
			getchar();
			index = LocateVex(G, find);
			if (index != ERROR) {
				printf("���������븳��ֵ��");
				scanf_s("%d", &value);
				getchar();
			}
			if (PutVex(&G, find, value) == OK)
				printf("��ֵ�ɹ���\n");
			else
				printf("��ֵʧ�ܣ�\n");
			getchar();
			break;

		case 5:
			if (isNull == TRUE) {
				printf("ͼ�����ڣ�\n");
				getchar();
				break;
			}
			printf("������������ҵĶ����λ��");
			scanf_s("%d", &index);
			getchar();
			if (index > G->vexnum + DeleteNum || index < 0) {
				printf("����λ�򲻷���Ҫ��\n");
				getchar();
				break;
			}
			if (FirstAdjVex(G, index) != ERROR)
				printf("�ö���ĵ�һ���ٽӶ���Ϊ�� %d��\n", FirstAdjVex(G, index));
			else
				printf("����ʧ�ܣ�\n");
			getchar();
			break;

		case 6:
			if (isNull == TRUE) {
				printf("ͼ�����ڣ�\n");
				getchar();
				break;
			}
			printf("������������ҵĶ���v��λ��");
			scanf_s("%d", &vp);
			getchar();
			printf("������������ҵĶ���w��λ��");
			scanf_s("%d", &wp);
			getchar();
			if (vp == wp || vp > G->vexnum + DeleteNum || wp > G->vexnum + DeleteNum) {
				printf("�������󣬲���ʧ�ܡ�\n");
			}
			else if (NextAdjVex(G, vp, wp) != ERROR) {
				printf("v�����w����һ���ٽ綥���λ��Ϊ�� %d��\n", NextAdjVex(G, vp, wp));
			}
			else
				printf("����ʧ�ܣ�\n");
			getchar();
			break;

		case 7:
			if (isNull == TRUE) {
				printf("ͼ�����ڣ�\n");
				getchar();
				break;
			}
			printf("�������������Ķ���Ĺؼ��֣�");
			scanf_s("%d", &insert);
			getchar();
			printf("�������������Ķ����ֵ��");
			scanf_s("%d", &value);
			getchar();
			vnode = (VertexType*)malloc(sizeof(VertexType));
			if (!vnode) exit(OVERFLOW);
			vnode->key = insert;
			vnode->value = value;
			if (InsertVex(&G, *vnode) == OK)
				printf("����ɹ���\n");
			else
				printf("����ʧ�ܣ�\n");
			getchar();
			break;

		case 8:
			if (isNull == TRUE) {
				printf("ͼ�����ڣ�\n");
				getchar();
				break;
			}
			printf("����������ɾ���Ķ���Ĺؼ��֣�");
			scanf_s("%d", &find);
			getchar();
			if (DeleteVex(&G, find) == OK)
				printf("ɾ���ɹ���\n");
			else
				printf("ɾ��ʧ�ܣ�\n");
			getchar();
			break;

		case 9:
			if (isNull == TRUE) {
				printf("ͼ�����ڣ�\n");
				getchar();
				break;
			}
			printf("�������������Ļ�β�Ĺؼ��֣�");
			scanf_s("%d", &vp);
			getchar();
			printf("�������������Ļ�ͷ�Ĺؼ��֣�");
			scanf_s("%d", &wp);
			getchar();
			if (InsertArc(&G, vp, wp) == OK)
				printf("����ɹ���\n");
			else
				printf("����ʧ�ܣ�\n");
			getchar();
			break;

		case 10:
			if (isNull == TRUE) {
				printf("ͼ�����ڣ�\n");
				getchar();
				break;
			}
			printf("����������ɾ���Ļ�β�Ĺؼ��֣�");
			scanf_s("%d", &vp);
			getchar();
			printf("����������ɾ���Ļ�ͷ�Ĺؼ��֣�");
			scanf_s("%d", &wp);
			getchar();
			if (DeleteArc(&G, vp, wp) == OK)
				printf("ɾ���ɹ���\n");
			else
				printf("ɾ��ʧ�ܣ�\n");
			getchar();
			break;

		case 11:
			if (isNull == TRUE) {
				printf("ͼ�����ڣ�\n");
				getchar();
				break;
			}
			printf("��ͼ����������������������£�\n");
			DFSTraverse(&G);
			getchar();
			break;

		case 12:
			if (isNull == TRUE) {
				printf("ͼ�����ڣ�\n");
				getchar();
				break;
			}
			printf("��ͼ���й�����������������£�\n");
			BFSTraverse(&G);
			getchar();
			break;
		case 0:
			break;
		}
	}
	printf("��лʹ�ñ�ϵͳ��\n");
	return 0;
}


/*case1: ����ͼ*/
Status CreateGraph(ALGraph* G) {
	KeyType key;
	ValueType value;
	VNode* vnode = (VNode*)malloc(sizeof(VNode));
	isNull = FALSE;
	*G = (ALGraph)malloc(sizeof(ALG));
	if (!G) exit(OVERFLOW);
	(*G)->vexnum = 0;
	(*G)->arcnum = 0;
	printf("�����붥���keyֵ��Ψһ����");
	scanf_s("%d", &key);
	getchar();
	printf("��Ϊ�ö��㸳ֵ��");
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


/*case2: ����ͼ*/
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

/*case3: ���Ҷ���*/
int LocateVex(ALGraph G, KeyType u) {
	for (int i = 0; i < (*G).vexnum + DeleteNum; i++) {
		if ((*G).vertices[i].data.key == u) {
			return i;
		}
	}
	return ERROR;
}

/*case4: ���㸳ֵ*/
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

/*case5����õ�һ�ڽӵ�*/
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

/*case6: �����һ�ڽӵ�*/
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

/*case7: ���붥��*/
Status InsertVex(ALGraph* G, VertexType vnode) {
	if (!G) return ERROR;
	if (LocateVex(*G, vnode.key) != ERROR) {
		printf("�ùؼ����Ѵ��ڣ�");
		return ERROR;
	}
	(*G)->vertices[(*G)->vexnum].data = vnode;
	(*G)->vertices[(*G)->vexnum].firstarc = NULL;
	(*G)->vexnum++;
	return OK;
}

/*case8: ɾ������*/
Status DeleteVex(ALGraph* G, KeyType vnode) {
	if (!G) return ERROR;
	ArcNode* temp;
	int num = 0;
	if (LocateVex(*G, vnode) == ERROR) {
		printf("�Ҳ����ö��㣡");
		return ERROR;
	}
	for (int i = 0; i < (*G)->vexnum + DeleteNum; i++) {
		temp = (*G)->vertices[i].firstarc;
		if (!temp) continue;
		if ((*G)->vertices[i].data.key == vnode) {//ɾ����
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
		else {	//ɾ����
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

/*case 9: ���뻡*/
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
				printf("�û��Ѵ��ڡ� ");
				return ERROR;
			}
			temp = temp->nextarc;
		}
		if ((*G)->vertices[temp->adjvex].data.key == w) {
			printf("�û��Ѵ��ڡ� ");
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

/*case 10: ɾ����*/
Status DeleteArc(ALGraph* G, KeyType v, KeyType w) {
	if (!G) return ERROR;
	ArcNode* temp;
	int indexv, indexw;
	if (LocateVex(*G, v) != ERROR && LocateVex(*G, w) != ERROR) {
		indexv = LocateVex(*G, v);
		indexw = LocateVex(*G, w);
		temp = (*G)->vertices[indexv].firstarc;
		if (!temp) {
			printf("�ö��㲻�ǻ�β��");
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
		printf("�����ڴ�vָ��w�Ļ���");
	}
	return ERROR;
}

/*case 11: ���������������*/
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

/*case 12: ���������������*/
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

Status EnQueue(Queue* lq, VNode ch) {		/*���*/
	if ((*lq)->rear >= LIST_INIT_SIZE)
		return ERROR;
	(*lq)->data[(*lq)->rear] = ch;
	(*lq)->rear++;
	return OK;
}

VNode OutQueue(Queue* q) {					/*����*/
	VNode tempnode = (*q)->data[(*q)->front];
	(*q)->front++;
	return tempnode;
}

Status Visit(VNode v) {
	if (v.data.key == 0) return ERROR;
	printf("%d: %d\n", v.data.key, v.data.value);
	return OK;
}
