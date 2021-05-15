#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 3
#define OK 1
#define ERROR 0

extern "C" int RECOMMEND();
extern "C" int FIND_G(char *);
extern "C" int BUY_G();
extern "C" char* GOOD;
char BNAME[10] = "PENG ZC";
char BPASS[10] = "12345";
int AUTH = 0;

typedef struct GOODS
{
	char name[10];
	int off;		//折扣
	double	inp;	//进货价
	double sep;		//出售价
	double num;		//进货数
	double sold;	//已售数量
	double reco;	//推荐度
}GOODS;

GOODS GA[N] = {
	{"BOOK", 9, 25, 36, 100, 20, 0},
	{"CUP", 8, 8, 15, 150, 24, 0},
	{"PEN", 34, 60, 30, 2, 0, 0},
};

void PrintMenu();
bool LOGIN();
int FIND();
bool BUY();
bool ChangeData();

int main()
{
	int op = 0;
	while (op!=6)
	{
		PrintMenu();
		scanf_s("%d", &op );
		getchar();
		switch (op)
		{
		case 1:
			LOGIN();
			break;
		case 2:
			FIND();
			break;
		case 3:
			BUY();
			break;
		case 4:
			RECOMMEND();
			printf("All recommendations calculated.\n");
			break;
		case 5:
			ChangeData();
			break;
		case 6:
			break;
		default:
			printf("Input ERROR!\n");
			break;
		}
	}
	system("pause");
}

//打印菜单
void PrintMenu()
{
	printf("\n----------------SHOP--------------\n");
	printf("USER:");
	if (AUTH == 1)
		printf("%s\n", BNAME);
	else
		printf("CUSTOMER\n");
	printf("GOOD:%s\n", GOOD);	
	printf("1.Login/Relogin\n");
	printf("2.Find a certain good\n");
	printf("3.Purchase\n");
	printf("4.Calculate the recomendation\n");
	printf("5.Change the data of goods\n");
	printf("6.Quit\n");
	printf("Please Enter 1-6 to choose the function:");
}
//登录函数
bool LOGIN()
{
	char INName[10];
	char INPass[10];
	char ch;
	int i = 0;
	printf("Please Input The Name:");
	while ((ch = getchar()) != '\n' && i < 9)//输入名字
	{
		INName[i++] = ch;
	}
	INName[i] = '\0';
	if (strcmp(BNAME, INName) == 0)
	{
		printf("Please Input The Password:");
		i = 0;
		while ((ch = getchar()) != '\n' && i < 9)//输入密码
		{
			INPass[i++] = ch;
		}
		INPass[i] = '\0';
		if (strcmp(BPASS, INPass) == 0)
		{
			AUTH = 1;
			printf("Login success!\n");
			return true;
		}
		AUTH = 0;
		printf("Wrong Password!\n");
		return false;
	}
	else
	{
		AUTH = 0;
		printf("Wrong Name!\n");
		return false;
	}
}

int FIND()
{
	char Fname[10];
	char ch;
	int i = 0;
	printf("Please input the good's name: ");
	while ((ch = getchar()) != '\n' && i < 9)
		Fname[i++] = ch;
	while (i < 10)
		Fname[i++] = 0;

	i = FIND_G(Fname); //调用汇编函数寻找

	if (i == 1)
	{
		printf("Find successful!\n");
		return OK;
	}
	else
	{
		printf("Find failed!\n");
		return ERROR;
	}

}


bool BUY()	//买入当前GOOD商品并计算所有商品推荐度
{
	int i;
	i = BUY_G();
	if (i == 1)
	{
		printf("Buy successful!\n");
		RECOMMEND();
		return true;
	}
	printf("The good has sold out. \n");
	return false;
}


bool ChangeData()
{
	int _off, _inp, _sep, _num, _sold;
	int i;
	if (AUTH != 1)
	{
		printf("Please Login first!\n");
		return false;
	}
	if (GOOD == 0)
	{
		printf("Please choose a good first!\n");
		return false;
	}
	for (i = 0; i < N; i++)
	{
		if (strcmp(GOOD, GA[i].name) == 0)
		{
			printf("Please input new information of %s:\n", GOOD);
			printf("OFF: %4d >> ", GA[i].off );
			scanf_s("%d", &_off);
			printf("InPrice: %4.2lf >> ", GA[i].inp);
			scanf_s("%d", &_inp);
			printf("SellPrice: %4.2lf >> ", GA[i].sep);
			scanf_s("%d", &_sep);
			printf("In num: %4.2lf >> ", GA[i].num);
			scanf_s("%d", &_num);
			printf("Sold num: %4.2lf >> ", GA[i].sold);
			scanf_s("%d", &_sold);

			GA[i].off = _off;
			GA[i].inp = _inp;
			GA[i].sep = _sep;
			GA[i].num = _num;
			GA[i].sold = _sold;
			return true;
		}
	}
	printf("ERROR!\n");
	return false;
}