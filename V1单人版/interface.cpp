// 编译环境：Visual C++ 6.0，EasyX 2011惊蛰版
// http://www.easyx.cn
//
#include "interface.h"


STAR star[MAXSTAR];

// 初始化星星
void InitStar(int i)
{
    star[i].x = 0;
    star[i].y = rand() % 480;
    star[i].step = (rand() % 5000) / 1000.0 + 1;
    star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);	// 速度越快，颜色越亮
    star[i].color = RGB(star[i].color, star[i].color, star[i].color);
}

// 移动星星
void MoveStar(int i)
{
    // 擦掉原来的星星
    putpixel((int)star[i].x, star[i].y, 0);

    // 计算新位置
    star[i].x += star[i].step;
    if (star[i].x > 640)	InitStar(i);

    // 画新星星
    putpixel((int)star[i].x, star[i].y, star[i].color);
}

void initStar()
{

    // 初始化所有星星
    for(int i = 0; i < MAXSTAR; i++)
    {
        InitStar(i);
        star[i].x = rand() % 640;
    }
}

void drawStar()
{


    // 绘制星空，

    for(int i = 0; i < MAXSTAR; i++)
        MoveStar(i);
    //		Sleep(20);

}
