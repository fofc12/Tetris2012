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
                            };//��ı���ɫ����ĺ�COLOR_NUM

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
            if(nowBlock.y - getBottomBlankLine(nowBlock.blockType, nowBlock.blockDir) + B_UNIT < 0)iDelay = 0;
            //��������û�г�������̨��ʱ�ĵȴ�

            key = waitInput(&iDelay); //�ȴ�����
            if (key == 27)  //esc�˳�
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

//��Ϸ����
void gameOver()
{
    outtextxy(120, 200, "Game Over!");
    getch();
    Sleep(10000);
}

//��Ϸ��ͣ
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

//Ԥ���ͷ���ת��Ϊ��ǰ����
Block preToNow(Block previewBlock)
{
    previewBlock.x = BIRTH_X;
    previewBlock.y = BIRTH_Y;

    return previewBlock;
}


////////////////////////////////////////////////������һЩ���㺯��
int length(char a[])
{
    /*����λ��*/
    int c = 0;
    while(*a++)c++;
    return c;
}


void copy(char x[])
{
    /*����*/
    char c;
    char *s = x + length(x) - 1; /*ָ��a��ĩλ*/
    while(s > x)
    {
        c = *s;
        *s-- = *x;
        *x++ = c;
    }
}


void add(char a[], int i)
{
    /*����a��1*/
    char *s = a;
    copy(a);/*��a���������ڽ�λ*/
    (*s) += i;
    while(*s > '9') /*�����Ҫ��λ*/
    {
        *s -= 10; /*��ǰλ-10*/
        if(*(s + 1))
        {
            s++;
            (*s)++; /*��һλ+1*/
        }
        else  /*���Ľ�λ*/
        {
            *(++s) = '1';
            *(++s) = 0;
            break;
        }
    }
    copy(a);/*a����ԭ*/
}

int arrToNum(char a[])
{

    int i = 0, j = 0, temp = 1, ret = 0;

    copy(a);/*��a���������ڽ�λ*/

    for(i = 0; i < length(a); i++)
    {

        temp = 1;
        for(j = 0; j < i; j++)
            temp *= 10;


        ret += (a[i] - '0') * temp;
    }
    copy(a);/*a����ԭ*/

    return ret;

}


//��ʾ����
void addScore(int line)
{
    int point = line * line;

    add(score, point);
}

//����ת��Ϊ�ӳ���ֵ
int scoreToDelay()
{
    int delay = 0;

    delay = INIT_DELAY - 10 * arrToNum(score);

    if(delay < MIN_DELAY)delay = MIN_DELAY;

    return delay;
}
