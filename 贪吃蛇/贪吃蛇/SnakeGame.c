#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>
#include"SnakeGame.h"

/*
1、定义蛇的结构体和食物
2、初始化蛇的身体和食物
3、程序流程控制
   蛇和墙的碰撞

   蛇和身体的碰撞

   蛇和食物的碰撞
	 食物消失
	 蛇身体增长
	 分数增长

	蛇方向控制 ASDW

	蛇的移动

	AI 
4、蛇死亡
   打印分数
   排行榜

*/

void ShowUI()
{
	COORD coord;

	for (int i = 0; i < snake.size; i++)
	{
		coord.X = snake.body[i].X;
		coord.Y = snake.body[i].Y;
		//设置控制台光标位置
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		//@ 表示蛇头  * 表示蛇身体
		if (i == 0)
			putchar('@');
		else
			putchar('*');
	}
	
	//去掉蛇尾
	coord.X = lx;
	coord.Y = ly;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar(' ');


	coord.X = food.X;
	coord.Y = food.Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar('#');
}
void InitSnake()
{
	//两节蛇身体
	snake.size = 2;

	//蛇头
	snake.body[0].X = WIDE / 2;
	snake.body[0].Y = HIGH / 2;

	snake.body[1].X = WIDE / 2 - 1;
	snake.body[1].Y = HIGH / 2;

}
void InitFood()
{
	food.X = rand() % WIDE;
	food.Y = rand() % HIGH;
}
void InitWall()
{
	for (int i = 0; i <= HIGH; i++)
	{
		for (int j = 0; j <= WIDE; j++)
		{
			if (j == WIDE)
			{
				printf("|");
			}
			else if (i == HIGH)
			{
				printf("_");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}

void PlayGame()
{
	char key = 'D';
	//蛇和墙的碰撞
	while (snake.body[0].X >= 0 && snake.body[0].X < WIDE
		&& snake.body[0].Y >= 0 && snake.body[0].Y < HIGH )
	{
		ShowUI();
		//方向控制
		//kbhit判断是否有键盘输入
		if (_kbhit())
		{
			key = _getch();
		}

		switch (key)
		{
		case 'a': case 'A':dx = -1; dy = 0; break;
		case 'd': case 'D':dx = 1; dy = 0; break;
		case 's': case 'S':dx = 0; dy = 1; break;
		case 'w': case 'W':dx = 0; dy = -1; break;
		}

		//蛇和身体碰撞
		for (size_t i = 1; i < snake.size; i++)
		{
			if (snake.body[0].X == snake.body[i].X
				&& snake.body[0].Y == snake.body[i].Y)
			{
				return;
			}
		}
		//蛇和食物碰撞
		if (snake.body[0].X == food.X && snake.body[0].Y == food.Y)
		{
			snake.size++;
			score += 10;
			InitFood();
		}

		//蛇的移动
		lx = snake.body[snake.size - 1].X;
		ly = snake.body[snake.size - 1].Y;

		for (size_t i = snake.size - 1; i > 0; i--)
		{
			//用上一节身体给当前身体坐标赋值
			snake.body[i].X = snake.body[i - 1].X;
			snake.body[i].Y = snake.body[i - 1].Y;
		}

		snake.body[0].X += dx;
		snake.body[0].Y += dy;

		Sleep(100);
		//system("cls");
	}
}
int main()
{
	srand((size_t)time(NULL));

	//去掉控制台光标
	CONSOLE_CURSOR_INFO  cci;
	cci.bVisible = FALSE;
	cci.dwSize = sizeof(cci);
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

	InitSnake();
	InitFood();

	InitWall();
	PlayGame();
	//getchar();
	return EXIT_SUCCESS;
}
