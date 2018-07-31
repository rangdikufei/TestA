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
1�������ߵĽṹ���ʳ��
2����ʼ���ߵ������ʳ��
3���������̿���
   �ߺ�ǽ����ײ

   �ߺ��������ײ

   �ߺ�ʳ�����ײ
	 ʳ����ʧ
	 ����������
	 ��������

	�߷������ ASDW

	�ߵ��ƶ�

	AI 
4��������
   ��ӡ����
   ���а�

*/

void ShowUI()
{
	COORD coord;

	for (int i = 0; i < snake.size; i++)
	{
		coord.X = snake.body[i].X;
		coord.Y = snake.body[i].Y;
		//���ÿ���̨���λ��
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		//@ ��ʾ��ͷ  * ��ʾ������
		if (i == 0)
			putchar('@');
		else
			putchar('*');
	}
	
	//ȥ����β
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
	//����������
	snake.size = 2;

	//��ͷ
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
	//�ߺ�ǽ����ײ
	while (snake.body[0].X >= 0 && snake.body[0].X < WIDE
		&& snake.body[0].Y >= 0 && snake.body[0].Y < HIGH )
	{
		ShowUI();
		//�������
		//kbhit�ж��Ƿ��м�������
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

		//�ߺ�������ײ
		for (size_t i = 1; i < snake.size; i++)
		{
			if (snake.body[0].X == snake.body[i].X
				&& snake.body[0].Y == snake.body[i].Y)
			{
				return;
			}
		}
		//�ߺ�ʳ����ײ
		if (snake.body[0].X == food.X && snake.body[0].Y == food.Y)
		{
			snake.size++;
			score += 10;
			InitFood();
		}

		//�ߵ��ƶ�
		lx = snake.body[snake.size - 1].X;
		ly = snake.body[snake.size - 1].Y;

		for (size_t i = snake.size - 1; i > 0; i--)
		{
			//����һ���������ǰ�������긳ֵ
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

	//ȥ������̨���
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
