#include"const.h"
#include"draw.h"
#include"mainop.h"
#include<stdio.h>

int scoreToDelay();
IMAGE img;



//������Ϸ�߽�
void drawStageLine()
{
    moveto(G_SPACE_X, 0);
    lineto(G_SPACE_X, WIDTH);

    moveto(LENGTH - G_SPACE_X, 0);
    lineto(LENGTH - G_SPACE_X, WIDTH);
}

//���ƻ����ĺ���϶��������
void drawSquare(int x, int y, int valid)
{
    if(valid == TRUE)
        bar(G_SPACE_X + (x - 1)*BLOCK_SIZE + BLOCK_GAP,
            (y - 1)*BLOCK_SIZE + BLOCK_GAP,
            x * BLOCK_SIZE + G_SPACE_X - BLOCK_GAP,
            y * BLOCK_SIZE - BLOCK_GAP);
}

//����̨���������̨
void drawStage()
{
    int i, j;
    setfillstyle(FGCLR);

    for(i = 1; i <= 10; i++)
        for(j = 1; j <= 20; j++)
            if(stage[i][j])drawSquare(i, j);
}

//���ƶ���˹���麯��1
void drawBlock(int x, int y, int blockType, int blockCLR, int mode, int blockDir)
{
    int i, j;

    if(mode == CLEAR)setfillstyle(BKCLR, SOLID_FILL);
    else setfillstyle(FGCLR, SOLID_FILL);

    WORDToArr(allBlock[blockType][blockDir]);
    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
            drawSquare(x + i, y + j, swap[i][j]);

}

//���ƶ���˹���麯��2
void drawBlk(Block block, COLORREF blockColor )
{
    int i, j;

    setfillstyle(blockColor, SOLID_FILL);

    WORDToArr(allBlock[block.blockType][block.blockDir]);
    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
            drawSquare(block.x + i, block.y + j, swap[i][j]);

}

//������һ�����飬�������µķ���
void updateBlock(Block tempBlock, Block nowBlock)
{
    if((tempBlock.blockType) != 7)
        drawBlock(tempBlock.x, tempBlock.y, tempBlock.blockType, tempBlock.blockCLR , CLEAR, tempBlock.blockDir);
    drawBlock(nowBlock.x, nowBlock.y, nowBlock.blockType, nowBlock.blockCLR, NORMAL, nowBlock.blockDir);
}

//�ı���ɫ
void changeColor(Block block)
{
    int random;

    random = Rand(0, COLOR_NUM - 1);
    drawBlk(block, color[random]);
}

//����
void delColumn(int line)
{
    getimage(
        &img,   // ����ͼ��� IMAGE ����ָ��
        G_SPACE_X,         // Ҫ��ȡͼ���������Ͻ� x ����
        G_SPACE_Y,         // Ҫ��ȡͼ����������Ͻ� y ����
        ROW * BLOCK_SIZE,   // Ҫ��ȡͼ������Ŀ��
        (line - 1)*BLOCK_SIZE   // Ҫ��ȡͼ������ĸ߶�
    );

    putimage(
        G_SPACE_X,              // ����λ�õ� x ����
        G_SPACE_Y + BLOCK_SIZE,            // ����λ�õ� y ����
        &img     // Ҫ���Ƶ� IMAGE ����ָ��
        //	,SRCCOPY  // ��Ԫ��դ�����루�����ע��
    );

    setfillstyle(BKCLR, SOLID_FILL);
    bar(G_SPACE_X, G_SPACE_Y, G_SPACE_X + ROW * BLOCK_SIZE - BLOCK_GAP, G_SPACE_Y + BLOCK_SIZE);
    setfillstyle(FGCLR, SOLID_FILL);

    drawStageLine();
}



//��ӡ����
void printScore()
{

    setfont(S_FONT_LENGTH, S_FONT_WIDTH, S_FONT_TYPE);
    outtextxy(SCORE_POS_X, SCORE_POS_Y - S_FONT_LENGTH, "�÷�:");

    char s[10];
    sprintf(s, "%.2f", (1000 / (float)scoreToDelay()));
    moveto(SCORE_POS_X + (int)(4.5 * S_FONT_WIDTH), SCORE_POS_Y - S_FONT_LENGTH);
    outtext("(��ǰ�ٶ�");
    outtext(s);
    outtext(")");


    outtextxy(SCORE_POS_X, WIDTH / 2, "����:");
    outtextxy(SCORE_POS_X, WIDTH / 2 + (int)(1.5 * S_FONT_LENGTH), "   ���� QQ2642223233");


    setfont(L_FONT_LENGTH, L_FONT_WIDTH, L_FONT_TYPE);
    outtextxy(SCORE_POS_X, SCORE_POS_Y, score); //��ӡ����;
}

//��ʾ��ߵĴ���
void printTetris()
{
    char str[] = "Tetris";
    int i, strLength = 6;

    setfont(L_FONT_LENGTH, L_FONT_WIDTH, L_FONT_TYPE);	// ��������
    for(i = 0; i < strLength; i++)
        outtextxy((G_SPACE_X - L_FONT_WIDTH) / 2, i * L_FONT_LENGTH, str[i]);
}

//��ӡ��ͣʱ����Ϣ
void printPause()
{
    setfont(S_FONT_LENGTH, S_FONT_WIDTH, S_FONT_TYPE);
    outtextxy(SCORE_POS_X + (int)(S_FONT_LENGTH * 2.5), 0, "��ͣ�����������");
}


//��ʾ�߽���,Ԥ����ʾ��������ʾ�ͷ���
void showFrame()
{
    moveto(G_SPACE_X, 0);
    lineto(G_SPACE_X, WIDTH);
    moveto(LENGTH - G_SPACE_X, 0);
    lineto(LENGTH - G_SPACE_X, WIDTH);//����Ϸ������

    setfont(S_FONT_LENGTH, S_FONT_WIDTH, S_FONT_TYPE);
    outtextxy(SCORE_POS_X, 0, "Ԥ����");

    printScore();
}


//��Ϸǰ��׼������
void init()
{
    initgraph(LENGTH, WIDTH);
    memset(stage, 0, sizeof(stage));
    setbkcolor(BKCLR);
    cleardevice();
    srand((unsigned)time(NULL));//��ʼ������
    printTetris();
    showFrame();
}