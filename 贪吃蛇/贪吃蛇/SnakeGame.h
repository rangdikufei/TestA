#pragma once

#define WIDE 60
#define HIGH 20
//�߽ṹ���ʼ��
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

//���ݿ��Ƽ��ı��ߵ�λ�� 
int dx = 0;
int dy = 0;

//��¼���һ���ߵ�����
int lx;
int ly;
