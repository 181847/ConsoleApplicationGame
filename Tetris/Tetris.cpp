#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<string.h>
#include <Windows.h>
#include <math.h>
#define PRINTPIX printf("■ ")
#define PRINTSPACE printf(".  ")
#define PRINTEDGE printf("◆ ")
#define PRINTNOTICE printf("◆◆◆◆◆◆◆按任意键回到主菜单◆◆◆◆◆◆◆\n")
#define HIGH 18
#define WIDTH 15
#define BARHI 18
#define BARWI 10
#define CLR system("cls")
#define GOBNUMBER 7

double clamp(const double& target, const double& min, const double& max);
int change(int n);
void printg(int y, int x, int gobn, int shape, int score);
void initialize_canvas();
int check(int y, int x, int gobn, int shape);
void addtocanvas(int y, int x, int gobn, int shape);
int move(int *py, int *px, int *pshape, int gobn1, int *pturn, double cotime);
void checkallline(int *pscore);
void getdown(int n);
char control(double cotime);
void initialize_bar(int high, int width);
void givenumtobar(int n, int gobnext, int goblater);
void printbeep(char *pcab, int n, int m);
void inputpassword();
void helpmenu();



char bar[BARHI][BARWI] = { 0 };
char number[10][5][4] = {
	{ { 0,1,1,0 },{ 1,0,0,1 },{ 1,0,0,1 },{ 1,0,0,1 },{ 0,1,1,0 } },//0
	{ { 0,0,1,0 },{ 0,1,1,0 },{ 0,0,1,0 },{ 0,0,1,0 },{ 0,0,1,0 } },//1
	{ { 1,1,1,0 },{ 0,0,0,1 },{ 0,1,1,0 },{ 1,0,0,0 },{ 1,1,1,1 } },//2
	{ { 1,1,1,0 },{ 0,0,0,1 },{ 0,1,1,0 },{ 0,0,0,1 },{ 1,1,1,0 } },//3
	{ { 1,0,0,1 },{ 1,0,0,1 },{ 1,1,1,1 },{ 0,0,0,1 },{ 0,0,0,1 } },//4
	{ { 1,1,1,1 },{ 1,0,0,0 },{ 1,1,1,1 },{ 0,0,0,1 },{ 1,1,1,0 } },//5
	{ { 0,1,1,0 },{ 1,0,0,0 },{ 1,1,1,0 },{ 1,0,0,1 },{ 0,1,1,0 } },//6
	{ { 1,1,1,1 },{ 0,0,0,1 },{ 0,0,1,0 },{ 0,1,0,0 },{ 0,1,0,0 } },//7
	{ { 0,1,1,0 },{ 1,0,0,1 },{ 0,1,1,0 },{ 1,0,0,1 },{ 0,1,1,0 } },//8
	{ { 0,1,1,0 },{ 1,0,0,1 },{ 0,1,1,1 },{ 0,0,0,1 },{ 0,1,1,0 } },//9
};

char pauseletter[9][22] = {
	{ 2, 2,2,2,2, 2,2,2,2, 2,2,2,2, 2,2,2,2, 2,2,2,2, 2 },
	{ 2, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 2 },
	{ 2, 1,1,1,0, 0,1,1,0, 1,0,0,1, 0,1,1,1, 1,1,1,1, 2 },
	{ 2, 1,0,0,1, 1,0,0,1, 1,0,0,1, 1,0,0,0, 1,0,0,0, 2 },
	{ 2, 1,1,1,0, 1,1,1,1, 1,0,0,1, 0,1,1,0, 1,1,1,1, 2 },
	{ 2, 1,0,0,0, 1,0,0,1, 1,0,0,1, 0,0,0,1, 1,0,0,0, 2 },
	{ 2, 1,0,0,0, 1,0,0,1, 0,1,1,0, 1,1,1,0, 1,1,1,1, 2 },
	{ 2, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 2 },
	{ 2, 2,2,2,2, 2,2,2,2, 2,2,2,2, 2,2,2,2, 2,2,2,2, 2 },
};

char overletter[9][18] = {
	{ 2, 2,2,2,2, 2,2,2,2, 2,2,2,2, 2,2,2,2, 2 },
	{ 2, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 2 },
	{ 2, 0,1,1,0, 1,0,0,1, 1,1,1,1, 1,1,1,0, 2 },
	{ 2, 1,0,0,1, 1,0,0,1, 1,0,0,0, 1,0,0,1, 2 },
	{ 2, 1,0,0,1, 0,1,0,1, 1,1,1,1, 1,1,1,0, 2 },
	{ 2, 1,0,0,1, 0,0,1,1, 1,0,0,0, 1,0,0,1, 2 },
	{ 2, 0,1,1,0, 0,0,0,1, 1,1,1,1, 1,0,0,1, 2 },
	{ 2, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 2 },
	{ 2, 2,2,2,2, 2,2,2,2, 2,2,2,2, 2,2,2,2, 2 },
};
char canvas[HIGH][WIDTH];/*画布，用来存储固定了的图像*/
char gob[GOBNUMBER][4][4][4] = {
	{/*长条形*/
		{ { 0,1,0,0 },{ 0,1,0,0 },{ 0,1,0,0 },{ 0,1,0,0 } },
		{ { 0,0,0,0 },{ 1,1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 } },
		{ { 0,1,0,0 },{ 0,1,0,0 },{ 0,1,0,0 },{ 0,1,0,0 } },
		{ { 0,0,0,0 },{ 1,1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 } }
	},

	{/*Z形*/
		{ { 0,0,0,0 },{ 1,0,0,0 },{ 1,1,0,0 },{ 0,1,0,0 } },
		{ { 0,0,0,0 },{ 0,0,0,0 },{ 0,1,1,0 },{ 1,1,0,0 } },
		{ { 0,0,0,0 },{ 1,0,0,0 },{ 1,1,0,0 },{ 0,1,0,0 } },
		{ { 0,0,0,0 },{ 0,0,0,0 },{ 0,1,1,0 },{ 1,1,0,0 } }
	},

	{/*丁字形*/
		{ { 0,0,0,0 },{ 0,1,0,0 },{ 0,1,1,0 },{ 0,1,0,0 } },
		{ { 0,0,0,0 },{ 0,0,0,0 },{ 1,1,1,0 },{ 0,1,0,0 } },
		{ { 0,0,0,0 },{ 0,1,0,0 },{ 1,1,0,0 },{ 0,1,0,0 } },
		{ { 0,0,0,0 },{ 0,1,0,0 },{ 1,1,1,0 },{ 0,0,0,0 } }
		/*
		{{0,0,0,0},{1,0,0,0},{1,1,0,0},{1,0,0,0}},
		{{0,0,0,0},{0,0,0,0},{1,1,1,0},{0,1,0,0}},
		{{0,0,0,0},{0,1,0,0},{1,1,0,0},{0,1,0,0}},
		{{0,0,0,0},{0,0,0,0},{0,1,0,0},{1,1,1,0}}
		*/
	},

	{/*L形*/
		{ { 0,0,0,0 },{ 1,0,0,0 },{ 1,0,0,0 },{ 1,1,0,0 } },
		{ { 0,0,0,0 },{ 0,0,0,0 },{ 1,1,1,0 },{ 1,0,0,0 } },
		{ { 0,0,0,0 },{ 1,1,0,0 },{ 0,1,0,0 },{ 0,1,0,0 } },
		{ { 0,0,0,0 },{ 0,0,0,0 },{ 0,0,1,0 },{ 1,1,1,0 } }
	},

	{/*正方形*/
		{ { 0,0,0,0 },{ 0,0,0,0 },{ 1,1,0,0 },{ 1,1,0,0 } },
		{ { 0,0,0,0 },{ 0,0,0,0 },{ 1,1,0,0 },{ 1,1,0,0 } },
		{ { 0,0,0,0 },{ 0,0,0,0 },{ 1,1,0,0 },{ 1,1,0,0 } },
		{ { 0,0,0,0 },{ 0,0,0,0 },{ 1,1,0,0 },{ 1,1,0,0 } }
	},

	{/*反Z形*/
		{ { 0,0,0,0 },{ 0,1,0,0 },{ 1,1,0,0 },{ 1,0,0,0 } },
		{ { 0,0,0,0 },{ 0,0,0,0 },{ 1,1,0,0 },{ 0,1,1,0 } },
		{ { 0,0,0,0 },{ 0,1,0,0 },{ 1,1,0,0 },{ 1,0,0,0 } },
		{ { 0,0,0,0 },{ 0,0,0,0 },{ 1,1,0,0 },{ 0,1,1,0 } },
	},

	{/*反L形*/
		{ { 0,0,0,0 },{ 0,1,0,0 },{ 0,1,0,0 },{ 1,1,0,0 } },
		{ { 0,0,0,0 },{ 0,0,0,0 },{ 1,0,0,0 },{ 1,1,1,0 } },
		{ { 0,0,0,0 },{ 1,1,0,0 },{ 1,0,0,0 },{ 1,0,0,0 } },
		{ { 0,0,0,0 },{ 0,0,0,0 },{ 1,1,1,0 },{ 0,0,1,0 } }
	},
};






void main()
{
	int gobnow, gobnext, goblater, x, y, shape, score, turn;
	double cotime;
	/*gobn代表选择的图形，在０－４之间，turn代表周期数在１～５之间，cotime代表用户可输入的时间长度*/

	//inputpassword();/*输入密码才能继续进行*/
	helpmenu();/*显示提示信息*/
start:
	cotime = 0.2;
	shape = 0;
	score = 0;
	turn = 1;
	srand(time(0));
	score = 0;
	initialize_canvas();/*将画布初始化，留下边框*/
	initialize_bar(BARHI, BARWI);
	gobnow = change(GOBNUMBER);/*得到随机图形的编号*/
	gobnext = change(GOBNUMBER);

	while (1)
	{
		goblater = change(GOBNUMBER);/*无输入；得到下一个随机图形的编号；随机返回０－４之间的数*/
		x = WIDTH / 2 - 1, y = -4;/*初始化坐标值*/

		while (1)
		{
			givenumtobar(score, gobnext, goblater);
			printg(y, x, gobnow, shape, score);	/*输入方块的坐标，方块的类型gobn，方块的朝向shape1，已得分数；打印方块，画布和当前得分；无返回值*/
			if (move(&y, &x, &shape, gobnow, &turn, cotime))
				break;
			/*输入方块坐标，形状，类型和移动的次数；由用户操作移动坐标和改变方向，且每固定移动次数后强制坐标向下移一位，若向下会与画布重复则将方块加入画布，其余操作会重复的则无视操作，移动次数加一；无返回*/
			CLR;
		}
		gobnow = gobnext;
		gobnext = goblater;/*依次将下一个图形的编号前移*/
		if (y == -4) break;/*如果纵坐标为负数时就跳出上一循环，说明方块到顶了，Gamerover*/
		checkallline(&score);/*检查所有满排，清除，向下补*/
		cotime = clamp(cotime * (1.0 - 0.05*score), 1e-5, 1.0);/*减少等待用户输入的时间，加快游戏速度*/
	}
	printbeep(&overletter[0][0], 9, 18);
	printbeep(&bar[7][0], 9, 10);
	_getch();
	goto start;
}







void initialize_canvas()
{
	memset(canvas, 0, HIGH*WIDTH * sizeof(char));
	for (int i = 0; i <= HIGH - 1; i++) canvas[i][WIDTH - 1] = canvas[i][0] = 1;
	for (int i = 0; i <= WIDTH - 1; i++) canvas[HIGH - 1][i] = 1;
}



double clamp(const double& target, const double& min, const double& max)
{
	return target < min
		? min
		: (target > max ? max : target);
}

int change(int n)
{
	return rand() % (n - 1);
}



void printg(int y, int x, int gobn, int shape, int score)/*输入方块的坐标，方块的类型gobn，方块的朝向shape1，已得分数；打印方块，画布和状态栏【包括分数和接下来的图形】；无返回值*/
{
	for (int i = 0; i <= HIGH - 1; i++)
	{
		for (int j = 0; j <= WIDTH - 1; j++)
		{
			if (y <= i&&i <= y + 3 && x <= j&&j <= x + 3)
			{
				if (gob[gobn][shape][i - y][j - x] || canvas[i][j]) PRINTPIX;
				else
					PRINTSPACE;
			}
			else
			{
				if (canvas[i][j]) PRINTPIX;
				else PRINTSPACE;
			}
		}
		if (i <= BARHI - 1)
			for (int k = 0; k <= BARWI - 1; k++)
				if (bar[i][k] == 1) PRINTPIX;
				else if (bar[i][k] == 2)PRINTEDGE;
				else PRINTSPACE;
				printf("\n");
	}
}

int check(int y, int x, int gobn, int shape)/*检查当前方块的位置是否与画布冲突，是则返回１，否则返回０*/
{
	for (int i = y; i <= y + 3; i++)
	{
		if (i<0) continue;
		for (int j = x; j <= x + 3; j++)
			if (gob[gobn][shape][i - y][j - x] && canvas[i][j]) return 1;
	}
	return 0;
}

void addtocanvas(int y, int x, int gobn, int shape)/*将方块固定到画布上*/
{
	CLR;
	for (int i = y; i <= y + 3; i++)
	{
		if (i<0) continue;
		for (int j = x; j <= x + 3; j++)
		{
			canvas[i][j] = (gob[gobn][shape][i - y][j - x] || canvas[i][j]);
		}
	}
}

int move(int *py, int *px, int *pshape, int gobn1, int *pturn, double cotime)
{
	int ty = *py, tx = *px, tshape = *pshape;
	if ((*pturn) % 5 == 0)/*每5次移动就向下移一位*/
	{
		ty++;
		if (check(ty, tx, gobn1, tshape))
		{
			addtocanvas(*py, *px, gobn1, *pshape);
			return 1;
		}
	}
	else
	{
		switch (control(cotime))/*在固定时间内若用户输入则立即返回输入的字符，否则返回０*/
		{
		case '2': ty++;
			if (check(ty, tx, gobn1, tshape))
			{
				addtocanvas(*py, *px, gobn1, *pshape);
				return 1;
			}break;
		case '4': tx--; break;
		case '6': tx++; break;
		case '5': tshape = (tshape + 1) % 4; break;
		case ' ':CLR; printbeep(&pauseletter[0][0], 9, 22); helpmenu(); break;
		default:break;
		}
	}
	if (check(ty, tx, gobn1, tshape)) return 0;
	*py = ty;
	*px = tx;
	*pshape = tshape;
	(*pturn)++;
	return 0;
}

void checkallline(int *pscore)
{
	int flag = 0;
	for (int i = 0; i <= HIGH - 2; i++)
	{
		flag = 0;
		for (int j = 1; j <= WIDTH - 1; j++)
		{
			if (canvas[i][j] == 0)
			{
				flag = 1;/*如果有０，则该排必不满，直接进入下一排检查*/
				break;
			}
		}
		if (flag == 0)
		{
			getdown(i);
			*pscore += 1;
			i--;/*清空这一排后，要继续检查这一排是否仍然满排*/
		}
	}

}

void getdown(int n)/*输入第几排，将这一排以上的点全部向下移一排*/
{
	for (int i = n; i>0; i--)
	{
		for (int j = 1; j <= WIDTH - 2; j++)
			canvas[i][j] = canvas[i - 1][j];
	}
	memset(&canvas[0][1], 0, WIDTH - 2);
}
char control(double cotime)/*无输入；在规定时间内扫描是否有输入；若有输入，则返回输入的字符编码，否则返回０*/
{

	char key = 0;
	int flag = 0;
	int t0 = clock();
	while (clock() - t0<cotime*CLOCKS_PER_SEC)
	{
		/*if (_kbhit())
		{
		key = _getch();
		break;
		}*/
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			Sleep(100);
			return ' ';
		}
		if (GetAsyncKeyState(VK_NUMPAD4) & 0x8000)
		{
			Sleep(100);
			return '4';
		}
		if (GetAsyncKeyState(VK_NUMPAD6) & 0x8000)
		{
			Sleep(100);
			return '6';
		}
		if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
		{
			Sleep(100);
			return '2';
		}
		if (GetAsyncKeyState(VK_NUMPAD5) & 0x8000)
		{
			Sleep(100);
			return '5';
		}
	}
	fflush(0);
	return '0';
}

void initialize_bar(int high, int width)
{
	for (int i = 0; i <= high - 1; i++)
		for (int j = 0; j <= width - 1; j++)
			if (i == 0 || i == (BARHI - 1) || j == 0 || j == (BARWI - 1) || i == (BARHI - 1) / 2)
				bar[i][j] = 2;
}

void givenumtobar(int n, int gobnext, int goblater)
{
	int n1 = n / 10, n2 = n % 10;
	for (int i = 0; i <= 4; i++)
	{
		for (int j = 0; j <= 3; j++)
		{
			bar[(BARHI - 1) / 2 + 2 + i][1 + j] = number[n1][i][j];
			bar[(BARHI - 1) / 2 + 2 + i][5 + j] = number[n2][i][j];
		}
	}
	for (int i = 0; i <= 3; i++)
	{
		for (int j = 0; j <= 3; j++)
		{
			bar[2 + i][1 + j] = gob[gobnext][0][i][j];
			bar[2 + i][5 + j] = gob[goblater][0][i][j];
		}
	}
}
void printbar()
{
	for (int i = 0; i <= BARHI - 1; i++)
	{
		for (int j = 0; j <= BARWI - 1; j++)
			if (bar[i][j] == 1) PRINTPIX;
			else if (bar[i][j] == 2) PRINTEDGE;
			else PRINTSPACE;
			printf("\n");
	}
}

void printbeep(char *pcab, int n, int m)
{
	for (int i = 0; i <= n - 1; i++)
	{
		for (int j = 0; j <= m - 1; j++)
			if (*(pcab + i*m + j) == 1) PRINTPIX;
			else if (*(pcab + i*m + j) == 0) PRINTSPACE;
			else PRINTEDGE;
			printf("\n");
	}
}

void inputpassword()
{
	char password[] = "administrator", getword[20];
	printf("请输入密码：");
input:
	scanf_s("%s", getword, 20);
	if (strcmp(getword, password) == 0)
		CLR;
	else
	{
		CLR;
		printf("密码错误，请重新输入：");
		goto input;
	}
}

void helpmenu()
{
	PRINTNOTICE;
	printf("提示：\n1.游戏中右上角会显示接下来将出现的方块\n2.右下角显示分数\n3.游戏过程中按空格键暂停，按回车键继续\n4.得分越高游戏速度也会越快\n");
	PRINTNOTICE;
	fflush(stdin);
	char c;
	while ((c = _getch()) != '\r' && c != EOF);
}