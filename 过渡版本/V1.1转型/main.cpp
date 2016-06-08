#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<string.h>
#include<math.h>
#include<stdio.h>

#include"const.h"

int pauseState = FALSE;
Block EMPTY_BLOCK = {0, 0, 7, 0, 0};


COLORREF color[COLOR_NUM] = {DARKGRAY ,
                             BLUE, LIGHTBLUE,
                             GREEN, LIGHTGREEN,
                             CYAN, LIGHTCYAN,
                             RED, LIGHTRED,
                             MAGENTA, LIGHTMAGENTA,
                             BROWN, YELLOW ,
                             LIGHTGRAY , DARKGRAY
                            };//��ı���ɫ����ĺ�COLOR_NUM



WORD allBlock[7][4] =
{
    {0xf000, 0x8888, 0xf000, 0x8888},
    {0xcc00, 0xcc00, 0xcc00, 0xcc00},
    {0x88c0, 0xe800, 0xc440, 0x2e00},
    {0x44c0, 0xe200, 0xc880, 0x8e00},
    {0x4e00, 0xe400, 0x4c40, 0x8c80},
    {0x8c40, 0x6c00, 0x8c40, 0x6c00},
    {0x4c80, 0xc600, 0x4c80, 0xc600}
};

int swap[4][4];

int stage[11][21] = {0};

char score[] = "0000";


//��Ϸ�Ľ���
void gameOver();
void gamePause();


void main()
{
    int i = 1, j = 1, temp = 0, timeLeft = 1000, cmd = 0;

    Block nowBlock, previewBlock, tempBlock = EMPTY_BLOCK;


    init();




    initStar();


    previewBlock = createBlock();//������һ������

    while(1)
    {

        drawStage();//������̨



        nowBlock = preToNow(previewBlock);//previewBlock��ΪnowBlock

        tempBlock = previewBlock;
        previewBlock = createBlock(PREVIEW);
        updateBlock(tempBlock, previewBlock);//�����������µ�previewBlock

        while(1)
        {

            showFrame();
            if(pauseState == TRUE)printPause();
            if(nowBlock.y - getBottomBlankLine(nowBlock.blockType, nowBlock.blockDir) + B_UNIT < 1)timeLeft = 0;
            //��������û�г�������̨��ʱ�ĵȴ�

            getCmd(&cmd);
            timeLeft -= 10;

            if(cmd != 0 && pauseState == FALSE)
            {
                tempBlock = nowBlock;
                if(moveBlock(cmd, &nowBlock))
                    updateBlock(tempBlock, nowBlock);
                //             else break;
            }

            if(timeLeft <= 0)
            {
                //	iDelay = scoreToDelay();
                timeLeft = 1000;

                if(pauseState == FALSE)
                {
                    tempBlock = nowBlock; //��¼��ǰ����
                    if(dropBlock(&nowBlock))
                        updateBlock(tempBlock, nowBlock);//drop�ɹ�����ʾ
                    else break;//dropʧ�ܣ���ʾ������ײ���˳�
                }
            }

        }


        transformBlock(nowBlock);
        changeColor(nowBlock);
        addScore(fullColumn());

        if(reachTop(nowBlock))gameOver();

    }

    getch();
    closegraph();
}



void gamePause()
{

    printPause();
    pauseState = (pauseState == FALSE);
    if(pauseState == FALSE)
    {
        setfillstyle(BKCLR, SOLID_FILL);
        bar(SCORE_POS_X + (int)(S_FONT_LENGTH * 2.5), 0, LENGTH, S_FONT_LENGTH);
    }
    //getch();
}


void gameOver()
{
    outtextxy(1, 10, "Game Over!");
    getch();
    Sleep(100000);
}


