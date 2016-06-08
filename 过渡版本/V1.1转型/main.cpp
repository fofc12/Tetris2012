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
                            };//如改变颜色还需改宏COLOR_NUM



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


//游戏的进程
void gameOver();
void gamePause();


void main()
{
    int i = 1, j = 1, temp = 0, timeLeft = 1000, cmd = 0;

    Block nowBlock, previewBlock, tempBlock = EMPTY_BLOCK;


    init();




    initStar();


    previewBlock = createBlock();//产生第一个方块

    while(1)
    {

        drawStage();//绘制舞台



        nowBlock = preToNow(previewBlock);//previewBlock变为nowBlock

        tempBlock = previewBlock;
        previewBlock = createBlock(PREVIEW);
        updateBlock(tempBlock, previewBlock);//产生并绘制新的previewBlock

        while(1)
        {

            showFrame();
            if(pauseState == TRUE)printPause();
            if(nowBlock.y - getBottomBlankLine(nowBlock.blockType, nowBlock.blockDir) + B_UNIT < 1)timeLeft = 0;
            //消除方块没有出现在舞台上时的等待

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
                    tempBlock = nowBlock; //记录当前方块
                    if(dropBlock(&nowBlock))
                        updateBlock(tempBlock, nowBlock);//drop成功则显示
                    else break;//drop失败，表示发生碰撞，退出
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


