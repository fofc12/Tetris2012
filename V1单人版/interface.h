#ifndef _INTERFACE_H_
#define _INTERFACE_H_

// ���뻷����Visual C++ 6.0��EasyX 2011���ݰ�
// http://www.easyx.cn
//
#include <graphics.h>
#include <time.h>
#include <conio.h>

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

#endif