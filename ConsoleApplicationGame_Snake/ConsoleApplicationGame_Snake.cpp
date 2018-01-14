/*按8上移，按2下移，按4左移，按6右移，可调整HIGH和WIDTH的值改变游戏画面大小*/
#include"stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

#define FOOD -1
#define WALL -2
#define SPACE 0
#define HIGH 24
#define WIDTH 26

#define PRINTWALL printf("■ ")
#define PRINTSPACE printf(".  ")
#define PRINTSNAKE printf("● ")
#define PRINTDEATH printf("X  ")
#define PRINTFOOD printf("◎ ")
#define PRINTHEAD printf("◆ ")
#define CLR system("cls")

#define UP 1
#define DOWN -1
#define LEFT 2
#define RIGHT -2
#define NOFOOD 0
#define GETFOOD 1
#define TG 5

void initialize_canvas(int*canvas, int n, int m, int level);
void givefoodlocation(int *fy, int *fx);
void printout(int*c, int n, int m, int y, int x, char death);
void controll(int*direction, int*y, int*x, double limittime);
void minuscanvas();
void printpoint(int n, char death);


int canvas[HIGH][WIDTH] = { 0 };

void main()
{
	int length, y, x, fy, fx;/*length为蛇身的长度     y,x为蛇头的坐标    fy，fx为食物的的坐标*/
	int counter = 1;
	int direction = UP;/*direction为蛇头运动方向*/
	int level = -1;
	double limittime = 0.5;
	srand(time(0));


restart:/*从此处重新开始游戏*/
	level = 1;


start:/*从此处跳至下一关*/


	direction = UP;/*设置初始的运动的方向为上*/

	length = 2;/*初始化蛇身长度为2*/

	y = HIGH - 3; x = 1;/*设置蛇头的坐标，从左下角开始*/

	initialize_canvas(&canvas[0][0], HIGH, WIDTH, level);/*根据等级数初始化画布*/

	givefoodlocation(&fy, &fx);/*给食物的坐标 赋随机值*/

	canvas[y][x] = length;/*蛇头坐标处的画布值设为（蛇身长度）*/

	canvas[y + 1][x] = length - 1;/*蛇头坐标处的下一格的画布值设为（蛇身长度-1）*/

	canvas[fy][fx] = FOOD;/*食物坐标处的画布值设为（FOOD），标志这里是食物*/

	while (1)
	{
		canvas[fy][fx] = FOOD;


		//printf("test%d\n",counter);


		controll(&direction, &y, &x, 0.5 - 0.08*limittime);/*输入方向和坐标的地址，暂停的时间长度；用户输入，控制方向的改变，一段时间后根据方向改变蛇头坐标*/


		switch (canvas[y][x])/*检查蛇头的坐标处是什么*/
		{
		case FOOD:length++;/*蛇身长度加一*/
			givefoodlocation(&fy, &fx);/*给食物坐标赋随机值*/
			canvas[fy][fx] = FOOD;/*食物坐标处的画布值设为（FOOD），标志这里是食物*/
			break;
		case 1:case SPACE:minuscanvas();
			break;
		default:goto gamerover;/*撞墙，游戏结束*/
		}
		CLR;
		canvas[y][x] = length;/*将蛇身的长度给蛇头坐标的变量*/
		printout(&canvas[0][0], HIGH, WIDTH, y, x, 0);/*打印画布，蛇，食物*/
		if (level != -1 && length%TG == 0)/*每达到TG长度跳至下一关*/
		{
			level++;
			if (level<5) goto start;
		}
	}
gamerover:CLR;
	minuscanvas();
	printout(&canvas[0][0], HIGH, WIDTH, y, x, 1);
	_getch();
	goto restart;
}





void initialize_canvas(int*canvas, int n, int m, int level)/*初始化画布*/
{
	for (int i = 0; i<n; i++)
		for (int j = 0; j<m; j++)
		{
			if (i == 0 || i == n - 1 || j == 0 || j == m - 1)
				*(canvas + i*m + j) = WALL;
			else
				*(canvas + i*m + j) = SPACE;
		}
	if (level == 1)
		for (int j = m / 3, i = n / 2; j <= m * 2 / 3; j++)
			*(canvas + i*m + j) = WALL;
	else if (level == 2)
	{
		for (int j = m / 4, i = n / 2; j <= m * 3 / 4; j++)
			*(canvas + i*m + j) = WALL;/*一字形墙*/
		for (int i = n / 4; i<n * 3 / 4; i++)
			*(canvas + i*m + m * 1 / 4) = *(canvas + i*m + m * 2 / 4) = *(canvas + i*m + m * 3 / 4) = WALL;
	}/*王字形墙*/
	else if (level == 3)
	{
		for (int i = 1; i <= n*m / 9; i++)
		{
			*(canvas + n*(rand() % n + 1) + (rand() % m + 1)) = WALL;
		}
	}
}

void givefoodlocation(int *fy, int *fx)
{
	do
	{
		*fy = rand() % (HIGH - 3) + 1;
		*fx = rand() % (WIDTH - 3) + 1;
	} while (canvas[*fy][*fx] != SPACE);
}

void printout(int*c, int n, int m, int y, int x, char death)
{
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<m; j++)
		{
			if (i == y&&j == x)
				/*若是蛇头坐标，则打印蛇头*/
			{
				if (death == 0) PRINTHEAD;
				else PRINTDEATH;/*死亡，蛇头打印X*/
				continue;
			}
			switch (*(c + i*m + j))
			{
			case FOOD:PRINTFOOD; break;
			case WALL:PRINTWALL; break;
			case SPACE:PRINTSPACE; break;
			default:PRINTSNAKE; break;
			}
		}
		printf("\n");
	}
}


void minuscanvas()
{
	for (int i = 1; i<HIGH - 1; i++)
		for (int j = 1; j<WIDTH - 1; j++)
			if (canvas[i][j] != 0 && canvas[i][j] != FOOD&&canvas[i][j] != WALL)
				canvas[i][j]--;
}

void controll(int*direction, int*y, int*x, double limittime)
{
	clock_t timenow = clock();
	int to;/*to存原来的方向值*/
	int td = to = *direction;/*td存会改变的方向值*/
	char t, flag = 0;
	while (clock() - timenow<limittime*CLOCKS_PER_SEC)
	{
		if (_kbhit())
		{
			t = _getch();
			switch (t)
			{
			case '8':td = UP; break;
			case '2':td = DOWN; break;
			case '4':td = LEFT; break;
			case '6':td = RIGHT; break;
			case ' ':CLR; _getch();
			}
			fflush(0);
		}
	}
	if ((td + to) == 0) *direction = to;
	else *direction = td;
	switch (*direction)
	{
	case UP:(*y)--; break;
	case DOWN:(*y)++; break;
	case LEFT:(*x)--; break;
	case RIGHT:(*x)++; break;
	}
}
