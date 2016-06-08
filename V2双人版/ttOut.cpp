#include"const.h"

//恢复背景
void recoverBk(int x, int y, int w, int h)
{


    IMAGE tpImg;
    SetWorkingImage(&bkImg);
    getimage(&tpImg, x, y, w, h);
    SetWorkingImage(NULL);
    putimage(x, y, &tpImg);
}

//绘制基本的含空隙的正方形
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
	//	l=(float)(l*1.3);//调高亮度
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

//清除上一个方块，并绘制新的方块
void refreshBlk(int playerNum, Block blk1, Block blk2, int mode)
{
    drawBlk(playerNum, blk1, CLEAR, mode);
    drawBlk(playerNum, blk2, NORMAL, mode);

}

//由舞台数组绘制舞台
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
        &img,   // 保存图像的 IMAGE 对象指针
        0,         // 要获取图像区域左上角 x 坐标
        0,           // 要获取图像区域的左上角 y 坐标
        ROW * BLOCK_SIZE,   // 要获取图像区域的宽度
        (line - 1)*BLOCK_SIZE   // 要获取图像区域的高度
    );

    putimage(
        0,                // 绘制位置的 x 坐标
        0 + BLOCK_SIZE,            // 绘制位置的 y 坐标
        &img     // 要绘制的 IMAGE 对象指针
        //	,SRCCOPY  // 三元光栅操作码（详见备注）
    );

    drawStage(playerNum);
}


void addColumn(int playerNum)
{
    IMAGE img;

    setorigin(g_player[playerNum].area.areaPoint.x, g_player[playerNum].area.areaPoint.y);

    getimage(
        &img,   // 保存图像的 IMAGE 对象指针
        0,         // 要获取图像区域左上角 x 坐标
        0 + BLOCK_SIZE,         // 要获取图像区域的左上角 y 坐标
        ROW * BLOCK_SIZE,   // 要获取图像区域的宽度
        COLUMN * BLOCK_SIZE // 要获取图像区域的高度
    );

    putimage(
        0,                // 绘制位置的 x 坐标
        0 ,            // 绘制位置的 y 坐标
        &img     // 要绘制的 IMAGE 对象指针
        //	,SRCCOPY  // 三元光栅操作码（详见备注）
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
        outtext("得分:");


        sprintf(s, "%d", (g_player[i].score));
        outtext(s);
    }


    moveto(0, WIDTH - BLOCK_SIZE);
    outtext("时间：");
    sprintf(s, "%.2f", (loopTime / TIME_UNIT));
    outtext(s);
}
