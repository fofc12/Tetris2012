#include"const.h"
#include"draw.h"
#include"mainop.h"
#include<stdio.h>

int scoreToDelay();
IMAGE img;



//绘制游戏边界
void drawStageLine()
{
    moveto(G_SPACE_X, 0);
    lineto(G_SPACE_X, WIDTH);

    moveto(LENGTH - G_SPACE_X, 0);
    lineto(LENGTH - G_SPACE_X, WIDTH);
}

//绘制基本的含空隙的正方形
void drawSquare(int x, int y, int valid)
{
    if(valid == TRUE)
        bar(G_SPACE_X + (x - 1)*BLOCK_SIZE + BLOCK_GAP,
            (y - 1)*BLOCK_SIZE + BLOCK_GAP,
            x * BLOCK_SIZE + G_SPACE_X - BLOCK_GAP,
            y * BLOCK_SIZE - BLOCK_GAP);
}

//由舞台数组绘制舞台
void drawStage()
{
    int i, j;
    setfillstyle(FGCLR);

    for(i = 1; i <= 10; i++)
        for(j = 1; j <= 20; j++)
            if(stage[i][j])drawSquare(i, j);
}

//绘制俄罗斯方块函数1
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

//绘制俄罗斯方块函数2
void drawBlk(Block block, COLORREF blockColor )
{
    int i, j;

    setfillstyle(blockColor, SOLID_FILL);

    WORDToArr(allBlock[block.blockType][block.blockDir]);
    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
            drawSquare(block.x + i, block.y + j, swap[i][j]);

}

//覆盖上一个方块，并绘制新的方块
void updateBlock(Block tempBlock, Block nowBlock)
{
    if((tempBlock.blockType) != 7)
        drawBlock(tempBlock.x, tempBlock.y, tempBlock.blockType, tempBlock.blockCLR , CLEAR, tempBlock.blockDir);
    drawBlock(nowBlock.x, nowBlock.y, nowBlock.blockType, nowBlock.blockCLR, NORMAL, nowBlock.blockDir);
}

//改变颜色
void changeColor(Block block)
{
    int random;

    random = Rand(0, COLOR_NUM - 1);
    drawBlk(block, color[random]);
}

//消行
void delColumn(int line)
{
    getimage(
        &img,   // 保存图像的 IMAGE 对象指针
        G_SPACE_X,         // 要获取图像区域左上角 x 坐标
        G_SPACE_Y,         // 要获取图像区域的左上角 y 坐标
        ROW * BLOCK_SIZE,   // 要获取图像区域的宽度
        (line - 1)*BLOCK_SIZE   // 要获取图像区域的高度
    );

    putimage(
        G_SPACE_X,              // 绘制位置的 x 坐标
        G_SPACE_Y + BLOCK_SIZE,            // 绘制位置的 y 坐标
        &img     // 要绘制的 IMAGE 对象指针
        //	,SRCCOPY  // 三元光栅操作码（详见备注）
    );

    setfillstyle(BKCLR, SOLID_FILL);
    bar(G_SPACE_X, G_SPACE_Y, G_SPACE_X + ROW * BLOCK_SIZE - BLOCK_GAP, G_SPACE_Y + BLOCK_SIZE);
    setfillstyle(FGCLR, SOLID_FILL);

    drawStageLine();
}



//打印分数
void printScore()
{

    setfont(S_FONT_LENGTH, S_FONT_WIDTH, S_FONT_TYPE);
    outtextxy(SCORE_POS_X, SCORE_POS_Y - S_FONT_LENGTH, "得分:");

    char s[10];
    sprintf(s, "%.2f", (1000 / (float)scoreToDelay()));
    moveto(SCORE_POS_X + (int)(4.5 * S_FONT_WIDTH), SCORE_POS_Y - S_FONT_LENGTH);
    outtext("(当前速度");
    outtext(s);
    outtext(")");


    outtextxy(SCORE_POS_X, WIDTH / 2, "作者:");
    outtextxy(SCORE_POS_X, WIDTH / 2 + (int)(1.5 * S_FONT_LENGTH), "   郝运 QQ2642223233");


    setfont(L_FONT_LENGTH, L_FONT_WIDTH, L_FONT_TYPE);
    outtextxy(SCORE_POS_X, SCORE_POS_Y, score); //打印分数;
}

//显示左边的大字
void printTetris()
{
    char str[] = "Tetris";
    int i, strLength = 6;

    setfont(L_FONT_LENGTH, L_FONT_WIDTH, L_FONT_TYPE);	// 设置字体
    for(i = 0; i < strLength; i++)
        outtextxy((G_SPACE_X - L_FONT_WIDTH) / 2, i * L_FONT_LENGTH, str[i]);
}

//打印暂停时的信息
void printPause()
{
    setfont(S_FONT_LENGTH, S_FONT_WIDTH, S_FONT_TYPE);
    outtextxy(SCORE_POS_X + (int)(S_FONT_LENGTH * 2.5), 0, "暂停中任意键继续");
}


//显示边界线,预览提示，分数提示和分数
void showFrame()
{
    moveto(G_SPACE_X, 0);
    lineto(G_SPACE_X, WIDTH);
    moveto(LENGTH - G_SPACE_X, 0);
    lineto(LENGTH - G_SPACE_X, WIDTH);//画游戏界面线

    setfont(S_FONT_LENGTH, S_FONT_WIDTH, S_FONT_TYPE);
    outtextxy(SCORE_POS_X, 0, "预览：");

    printScore();
}


//游戏前的准备工作
void init()
{
    initgraph(LENGTH, WIDTH);
    memset(stage, 0, sizeof(stage));
    setbkcolor(BKCLR);
    cleardevice();
    srand((unsigned)time(NULL));//初始化种子
    printTetris();
    showFrame();
}