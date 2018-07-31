#pragma once

#define WIDE 60
#define HIGH 20
//蛇结构体初始化
struct BODY
{
	int X;
	int Y;
};
struct SNAKE
{
	struct BODY body[WIDE*HIGH];
	int size;
}snake;

struct FOOD
{
	int X;
	int Y;
}food;

int score = 0;

//根据控制键改变蛇的位置 
int dx = 0;
int dy = 0;

//记录最后一节蛇的坐标
int lx;
int ly;
