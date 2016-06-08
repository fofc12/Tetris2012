// ���뻷����Visual C++ 6.0��EasyX 2011���ݰ�
// http://www.easyx.cn
//
#include "interface.h"


STAR star[MAXSTAR];

// ��ʼ������
void InitStar(int i)
{
    star[i].x = 0;
    star[i].y = rand() % 480;
    star[i].step = (rand() % 5000) / 1000.0 + 1;
    star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);	// �ٶ�Խ�죬��ɫԽ��
    star[i].color = RGB(star[i].color, star[i].color, star[i].color);
}

// �ƶ�����
void MoveStar(int i)
{
    // ����ԭ��������
    putpixel((int)star[i].x, star[i].y, 0);

    // ������λ��
    star[i].x += star[i].step;
    if (star[i].x > 640)	InitStar(i);

    // ��������
    putpixel((int)star[i].x, star[i].y, star[i].color);
}

void initStar()
{

    // ��ʼ����������
    for(int i = 0; i < MAXSTAR; i++)
    {
        InitStar(i);
        star[i].x = rand() % 640;
    }
}

void drawStar()
{


    // �����ǿգ�

    for(int i = 0; i < MAXSTAR; i++)
        MoveStar(i);
    //		Sleep(20);

}
