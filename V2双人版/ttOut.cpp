#include"const.h"

//�ָ�����
void recoverBk(int x, int y, int w, int h)
{


    IMAGE tpImg;
    SetWorkingImage(&bkImg);
    getimage(&tpImg, x, y, w, h);
    SetWorkingImage(NULL);
    putimage(x, y, &tpImg);
}

//���ƻ����ĺ���϶��������
void drawSquare(int playerNum, Point pt, COLORREF clr, int mode1, int mode2)
{
    setorigin(0, 0);
    int i, j;
    int X = 0, Y = 0;
    float h, s, l, val,val1, val2;

    if(mode2 == NORMAL)	X = g_player[playerNum].area.areaPoint.x, Y = g_player[playerNum].area.areaPoint.y;
    else 	X = g_player[playerNum].preview.x, Y = g_player[playerNum].preview.y;
    if(mode1 == NORMAL)
    {


        RGBtoHSL(clr, &h, &s, &l);
	//	l=(float)(l*1.3);//��������
        for(i = 0; i <= BLOCK_SIZE; i++)
            for(j = 0; j <= BLOCK_SIZE; j++)
            {
             /*   val1 = (float)i / BLOCK_SIZE;
                val2 = (float)j / BLOCK_SIZE;
                val = (val1 + val2) / 2;
				 putpixel(X + (pt.x - 1)*BLOCK_SIZE + i , Y + (pt.y - 1) * BLOCK_SIZE + j , HSLtoRGB(h, val, l));
				*/


				 val1 = (float)i / BLOCK_SIZE;
                val2 = (float)j / BLOCK_SIZE;
                val = (val1 + val2) / 2;
                putpixel(X + (pt.x - 1)*BLOCK_SIZE + i , Y + (pt.y - 1) * BLOCK_SIZE + j , HSLtoRGB(h, s,val));
            }

    }
    else
    {
        int x, y;
        x = (pt.x - 1) * BLOCK_SIZE + X;
        y = (pt.y - 1) * BLOCK_SIZE + Y;
        recoverBk(x, y, BLOCK_SIZE + 1, BLOCK_SIZE + 1);
    }
}

void drawBlk(int playerNum, Block block, int mode1, int mode2)
{
    int i, j;
    Point tempPoint = {0, 0};

    WORDToArr(allBlock[block.blockType][block.blockDir]);
    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
        {
            if(swap[i][j] > 0)
            {
                tempPoint.x = i + block.point.x;
                tempPoint.y = j + block.point.y;
                drawSquare(playerNum, tempPoint, block.blockCLR, mode1, mode2);
            }
        }

}

//�����һ�����飬�������µķ���
void refreshBlk(int playerNum, Block blk1, Block blk2, int mode)
{
    drawBlk(playerNum, blk1, CLEAR, mode);
    drawBlk(playerNum, blk2, NORMAL, mode);

}

//����̨���������̨
void drawStage(int playerNum)
{
    int i, j;
    for(i = 1; i <= ROW; i++)
        for(j = 1; j <= COLUMN; j++)
            if(g_player[playerNum].area.state[i][j] == 0)
                drawSquare(playerNum, createPt(i, j), BKCLR, CLEAR, NORMAL); 
}

void delColumn(int playerNum, int line)
{
    IMAGE img;

    setorigin(g_player[playerNum].area.areaPoint.x, g_player[playerNum].area.areaPoint.y);

    getimage(
        &img,   // ����ͼ��� IMAGE ����ָ��
        0,         // Ҫ��ȡͼ���������Ͻ� x ����
        0,           // Ҫ��ȡͼ����������Ͻ� y ����
        ROW * BLOCK_SIZE,   // Ҫ��ȡͼ������Ŀ��
        (line - 1)*BLOCK_SIZE   // Ҫ��ȡͼ������ĸ߶�
    );

    putimage(
        0,                // ����λ�õ� x ����
        0 + BLOCK_SIZE,            // ����λ�õ� y ����
        &img     // Ҫ���Ƶ� IMAGE ����ָ��
        //	,SRCCOPY  // ��Ԫ��դ�����루�����ע��
    );

    drawStage(playerNum);
}


void addColumn(int playerNum)
{
    IMAGE img;

    setorigin(g_player[playerNum].area.areaPoint.x, g_player[playerNum].area.areaPoint.y);

    getimage(
        &img,   // ����ͼ��� IMAGE ����ָ��
        0,         // Ҫ��ȡͼ���������Ͻ� x ����
        0 + BLOCK_SIZE,         // Ҫ��ȡͼ����������Ͻ� y ����
        ROW * BLOCK_SIZE,   // Ҫ��ȡͼ������Ŀ��
        COLUMN * BLOCK_SIZE // Ҫ��ȡͼ������ĸ߶�
    );

    putimage(
        0,                // ����λ�õ� x ����
        0 ,            // ����λ�õ� y ����
        &img     // Ҫ���Ƶ� IMAGE ����ָ��
        //	,SRCCOPY  // ��Ԫ��դ�����루�����ע��
    );


    drawStage(playerNum);
}


void drawStageLine()
{
    int i;

    setorigin(0, 0);
    setfillstyle(BLUE);
    for(i = 1; i <= TOTAL_PLAYER; i++)
    {
        bar(g_player[i].area.areaPoint.x - 1, 0,
            g_player[i].area.areaPoint.x + 1, LENGTH );

        bar(g_player[i].area.areaPoint.x - 1 + ROW * BLOCK_SIZE, 0,
            g_player[i].area.areaPoint.x + 1 + ROW * BLOCK_SIZE, LENGTH );
    }
}

void printScore(int loopTime)
{

    int i;
    char s[5];
    setorigin(0, 0);
    for (i = 1; i <= TOTAL_PLAYER; i++)
    {

        moveto(g_player[i].preview.x, g_player[i].preview.y + 4 * BLOCK_SIZE);
        outtext("�÷�:");


        sprintf(s, "%d", (g_player[i].score));
        outtext(s);
    }


    moveto(0, WIDTH - BLOCK_SIZE);
    outtext("ʱ�䣺");
    sprintf(s, "%.2f", (loopTime / TIME_UNIT));
    outtext(s);
}
