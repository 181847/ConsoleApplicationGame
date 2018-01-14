/*��8���ƣ���2���ƣ���4���ƣ���6���ƣ��ɵ���HIGH��WIDTH��ֵ�ı���Ϸ�����С*/
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

#define PRINTWALL printf("�� ")
#define PRINTSPACE printf(".  ")
#define PRINTSNAKE printf("�� ")
#define PRINTDEATH printf("X  ")
#define PRINTFOOD printf("�� ")
#define PRINTHEAD printf("�� ")
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
	int length, y, x, fy, fx;/*lengthΪ����ĳ���     y,xΪ��ͷ������    fy��fxΪʳ��ĵ�����*/
	int counter = 1;
	int direction = UP;/*directionΪ��ͷ�˶�����*/
	int level = -1;
	double limittime = 0.5;
	srand(time(0));


restart:/*�Ӵ˴����¿�ʼ��Ϸ*/
	level = 1;


start:/*�Ӵ˴�������һ��*/


	direction = UP;/*���ó�ʼ���˶��ķ���Ϊ��*/

	length = 2;/*��ʼ��������Ϊ2*/

	y = HIGH - 3; x = 1;/*������ͷ�����꣬�����½ǿ�ʼ*/

	initialize_canvas(&canvas[0][0], HIGH, WIDTH, level);/*���ݵȼ�����ʼ������*/

	givefoodlocation(&fy, &fx);/*��ʳ������� �����ֵ*/

	canvas[y][x] = length;/*��ͷ���괦�Ļ���ֵ��Ϊ�������ȣ�*/

	canvas[y + 1][x] = length - 1;/*��ͷ���괦����һ��Ļ���ֵ��Ϊ��������-1��*/

	canvas[fy][fx] = FOOD;/*ʳ�����괦�Ļ���ֵ��Ϊ��FOOD������־������ʳ��*/

	while (1)
	{
		canvas[fy][fx] = FOOD;


		//printf("test%d\n",counter);


		controll(&direction, &y, &x, 0.5 - 0.08*limittime);/*���뷽�������ĵ�ַ����ͣ��ʱ�䳤�ȣ��û����룬���Ʒ���ĸı䣬һ��ʱ�����ݷ���ı���ͷ����*/


		switch (canvas[y][x])/*�����ͷ�����괦��ʲô*/
		{
		case FOOD:length++;/*�����ȼ�һ*/
			givefoodlocation(&fy, &fx);/*��ʳ�����긳���ֵ*/
			canvas[fy][fx] = FOOD;/*ʳ�����괦�Ļ���ֵ��Ϊ��FOOD������־������ʳ��*/
			break;
		case 1:case SPACE:minuscanvas();
			break;
		default:goto gamerover;/*ײǽ����Ϸ����*/
		}
		CLR;
		canvas[y][x] = length;/*������ĳ��ȸ���ͷ����ı���*/
		printout(&canvas[0][0], HIGH, WIDTH, y, x, 0);/*��ӡ�������ߣ�ʳ��*/
		if (level != -1 && length%TG == 0)/*ÿ�ﵽTG����������һ��*/
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





void initialize_canvas(int*canvas, int n, int m, int level)/*��ʼ������*/
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
			*(canvas + i*m + j) = WALL;/*һ����ǽ*/
		for (int i = n / 4; i<n * 3 / 4; i++)
			*(canvas + i*m + m * 1 / 4) = *(canvas + i*m + m * 2 / 4) = *(canvas + i*m + m * 3 / 4) = WALL;
	}/*������ǽ*/
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
				/*������ͷ���꣬���ӡ��ͷ*/
			{
				if (death == 0) PRINTHEAD;
				else PRINTDEATH;/*��������ͷ��ӡX*/
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
	int to;/*to��ԭ���ķ���ֵ*/
	int td = to = *direction;/*td���ı�ķ���ֵ*/
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
