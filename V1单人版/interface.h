#ifndef _INTERFACE_H_
#define _INTERFACE_H_

// 编译环境：Visual C++ 6.0，EasyX 2011惊蛰版
// http://www.easyx.cn
//
#include <graphics.h>
#include <time.h>
#include <conio.h>

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

#endif