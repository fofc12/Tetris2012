#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<string.h>
#include<math.h>
#include<stdio.h>

#include"const.h"
#include"draw.h"
#include"mainop.h"
#include"input.h"
#include"interface.h"

int pauseState = FALSE;

char score[] = "0000";

Block EMPTY_BLOCK = {0, 0, 7, 0, 0};

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

int stage[11][21] = {0};

int swap[4][4];

COLORREF color[COLOR_NUM] = {DARKGRAY ,
                             BLUE, LIGHTBLUE,
                             GREEN, LIGHTGREEN,
                             CYAN, LIGHTCYAN,
                             RED, LIGHTRED,
                             MAGENTA, LIGHTMAGENTA,
                             BROWN, YELLOW ,
                             LIGHTGRAY , DARKGRAY
                            };//如改变颜色还需改宏COLOR_NUM

void gameOver();
void gamePause();

Block preToNow(Block PreviewBlock);
void addScore(int line);
int scoreToDelay();
int arrToNum(char a[]);


void main()
{
    int i = 1, j = 1, k = 1, temp = 0, key, iDir, iDelay = 1000;
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
            if(nowBlock.y - getBottomBlankLine(nowBlock.blockType, nowBlock.blockDir) + B_UNIT < 0)iDelay = 0;
            //消除方块没有出现在舞台上时的等待

            key = waitInput(&iDelay); //等待输入
            if (key == 27)  //esc退出
            {
                gameOver();
            }
            if(key == 80 || key == 112)
            {
                gamePause();
            }

            if(key == ' ')
            {
                do
                {
                    Sleep(10);
                    tempBlock = nowBlock;
                    k = dropBlock(&nowBlock);
                    if(k)updateBlock(tempBlock, nowBlock);
                }
                while(k);
            }

            switch(key)
            {
            case CMD_UP:
                iDir = key;
                break;

            case CMD_DOWN:
                iDir = key;
                break;

            case CMD_LEFT:
                iDir = key;
                break;

            case CMD_RIGHT:
                iDir = key;
                break;

            default:
                iDir = CMD_OTHER;
                break;
            }

            if(key != 0 && pauseState == FALSE)
            {
                tempBlock = nowBlock;
                if(moveBlock(iDir, &nowBlock))
                    updateBlock(tempBlock, nowBlock);
                //             else break;
            }

            if(iDelay == 0)
            {
                iDelay = scoreToDelay();

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

//游戏结束
void gameOver()
{
    outtextxy(120, 200, "Game Over!");
    getch();
    Sleep(10000);
}

//游戏暂停
void gamePause()
{
    printPause();
    pauseState = (pauseState == FALSE);
    if(pauseState == FALSE)
    {
        setfillstyle(BKCLR, SOLID_FILL);
        bar(SCORE_POS_X + (int)(S_FONT_LENGTH * 2.5), 0, LENGTH, S_FONT_LENGTH);
    }
}

//预览型方块转换为当前方块
Block preToNow(Block previewBlock)
{
    previewBlock.x = BIRTH_X;
    previewBlock.y = BIRTH_Y;

    return previewBlock;
}


////////////////////////////////////////////////以下是一些计算函数
int length(char a[])
{
    /*返回位数*/
    int c = 0;
    while(*a++)c++;
    return c;
}


void copy(char x[])
{
    /*逆序*/
    char c;
    char *s = x + length(x) - 1; /*指向a的末位*/
    while(s > x)
    {
        c = *s;
        *s-- = *x;
        *x++ = c;
    }
}


void add(char a[], int i)
{
    /*大数a加1*/
    char *s = a;
    copy(a);/*对a逆序处理，便于进位*/
    (*s) += i;
    while(*s > '9') /*如果需要进位*/
    {
        *s -= 10; /*当前位-10*/
        if(*(s + 1))
        {
            s++;
            (*s)++; /*下一位+1*/
        }
        else  /*最后的进位*/
        {
            *(++s) = '1';
            *(++s) = 0;
            break;
        }
    }
    copy(a);/*a逆序还原*/
}

int arrToNum(char a[])
{

    int i = 0, j = 0, temp = 1, ret = 0;

    copy(a);/*对a逆序处理，便于进位*/

    for(i = 0; i < length(a); i++)
    {

        temp = 1;
        for(j = 0; j < i; j++)
            temp *= 10;


        ret += (a[i] - '0') * temp;
    }
    copy(a);/*a逆序还原*/

    return ret;

}


//显示分数
void addScore(int line)
{
    int point = line * line;

    add(score, point);
}

//分数转换为延迟数值
int scoreToDelay()
{
    int delay = 0;

    delay = INIT_DELAY - 10 * arrToNum(score);

    if(delay < MIN_DELAY)delay = MIN_DELAY;

    return delay;
}
