#pragma once
#include "const.h"

#define MAXSTAR 200	// 星星总数

struct STAR
{
    double x;
    int y;
    double step;
    int color;
};

//STAR star[MAXSTAR];

// 初始化星星
void InitStar(int i);

// 移动星星
void MoveStar(int i);

// 主函数
void initStar();

void drawStar();
