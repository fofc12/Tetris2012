#pragma once
#include "const.h"

#define MAXSTAR 200	// ��������

struct STAR
{
    double x;
    int y;
    double step;
    int color;
};

//STAR star[MAXSTAR];

// ��ʼ������
void InitStar(int i);

// �ƶ�����
void MoveStar(int i);

// ������
void initStar();

void drawStar();
