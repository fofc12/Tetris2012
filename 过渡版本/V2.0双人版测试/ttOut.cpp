#include"const.h"

//extern Block EMPTY_BLOCK;
extern WORD allBlock[TOTAL_BLOCK+1][4];
//extern stage[11][21];
extern COLORREF color[];
//extern char score[];
extern Player g_player[];

extern swap[4][4];


//绘制基本的含空隙的正方形
void drawSquare(Point squarePoint)
{
    //setorigin(originPoint.x,originPoint.y);

    //	if(valid == TRUE)
    bar(
        (squarePoint.x - 1)*BLOCK_SIZE + BLOCK_GAP,
        (squarePoint.y - 1)*BLOCK_SIZE + BLOCK_GAP,
        squarePoint.x * BLOCK_SIZE - BLOCK_GAP,
        squarePoint.y * BLOCK_SIZE - BLOCK_GAP
    );

    //	setorigin(0,0);
}

void drawBlk(Block block, int mode)
{
    int i, j;
    Point tempPoint = {0, 0};

    if(mode == CLEAR)setfillstyle(BKCLR, SOLID_FILL);
    else setfillstyle(block.blockCLR, SOLID_FILL);

    WORDToArr(allBlock[block.blockType][block.blockDir]);
    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
        {
            if(swap[i][j] > 0)
            {
                tempPoint.x = i + block.point.x;
                tempPoint.y = j + block.point.y;
                drawSquare(tempPoint);
            }
        }

    if(mode == CLEAR)setfillstyle(FGCLR, SOLID_FILL);
}

//清除上一个方块，并绘制新的方块
void refreshBlk(Block blk1, Block blk2)
{
    //if((tempBlock.blockType) != 7)
    drawBlk(blk1, CLEAR);
    drawBlk(blk2, NORMAL);
}

//由舞台数组绘制舞台
void drawStage(int playerNum)
{
    int i, j;
    setfillstyle(color[Rand(0, COLOR_NUM-1)]);

    //	setorigin(g_player[i].area.areaPoint.x,g_player[i].area.areaPoint.y);
    for(i = 1; i <= ROW; i++)
        for(j = 1; j <= COLUMN; j++)
            if(g_player[playerNum].area.state[i][j] > 0)drawSquare(createPt(i, j)); //i不能与playerNum混起来
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


    setfillstyle(BKCLR, SOLID_FILL);
    bar(0, 0, 0 + ROW * BLOCK_SIZE - BLOCK_GAP, 0 + BLOCK_SIZE);
    setfillstyle(FGCLR, SOLID_FILL);
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


    setfillstyle(BKCLR, SOLID_FILL);
    bar(0,  (ROW - 1) * BLOCK_SIZE, 0 + ROW * BLOCK_SIZE - BLOCK_GAP, ROW * BLOCK_SIZE);
    setfillstyle(FGCLR, SOLID_FILL);
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


/*
void printTetris()
{
	char str[]="Tetris";
	int i,strLength=6;



	setfont(L_FONT_LENGTH,L_FONT_WIDTH,L_FONT_TYPE);	// 设置字体
	for(i=0;i<strLength;i++)
		outtextxy((G_SPACE_X-L_FONT_WIDTH)/2,i*L_FONT_LENGTH,str[i]);
}

//绘制一些基本的物件
//






//绘制基本的含空隙的正方形
void drawSquare(Point originPoint,Point squarePoint,bool valid)
{
	setorigin(originPoint.x,originPoint.y);

	if(valid == TRUE)
        bar(
			(squarePoint.x - 1)*BLOCK_SIZE + BLOCK_GAP,
            (squarePoint.y - 1)*BLOCK_SIZE + BLOCK_GAP,
            squarePoint.x * BLOCK_SIZE - BLOCK_GAP,
            squarePoint.y * BLOCK_SIZE - BLOCK_GAP
			);

	setorigin(0,0);
}



//绘制俄罗斯方块
void drawBlock(int x, int y, int blockType, int mode, int blockDir)
{
    int i, j;
	Point tempPoint={0,0};


    if(mode == CLEAR)setfillstyle(BKCLR, SOLID_FILL);
    else setfillstyle(FGCLR, SOLID_FILL);

    WORDToArr(allBlock[blockType][blockDir]);
    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
		{
tempPoint.x=i;tempPoint.y=j;
            drawSquare(g_player[i].pstage->areaPoint,tempPoint,swap[i][j]>0);}

}

//绘制俄罗斯方块
void drawBlk(Block block,COLORREF blockColor )
{
    int i, j;
		Point tempPoint={0,0};

   setfillstyle(blockColor, SOLID_FILL);

    WORDToArr(allBlock[block.blockType][block.blockDir]);
    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
				{
tempPoint.x=i;tempPoint.y=j;
drawSquare(block.point,tempPoint, swap[i][j]>0);}

}

//覆盖上一个方块，并绘制新的方块
void updateBlock(Block tempBlock, Block nowBlk)
{
    if((tempBlock.blockType) != 7)
        drawBlock(tempBlock.point.x, tempBlock.point.y, tempBlock.blockType, CLEAR, tempBlock.blockDir);
    drawBlock(nowBlk.point.x, nowBlk.point.y, nowBlk.blockType, NORMAL, nowBlk.blockDir);
}

void delColumn(int line)
{
	getimage(
		&img,   // 保存图像的 IMAGE 对象指针
		G_SPACE_X,         // 要获取图像区域左上角 x 坐标
		G_SPACE_Y,         // 要获取图像区域的左上角 y 坐标
		ROW*BLOCK_SIZE,     // 要获取图像区域的宽度
		(line-1)*BLOCK_SIZE     // 要获取图像区域的高度
			);

	putimage(
		G_SPACE_X,              // 绘制位置的 x 坐标
		G_SPACE_Y+BLOCK_SIZE,              // 绘制位置的 y 坐标
		&img     // 要绘制的 IMAGE 对象指针
	//	,SRCCOPY  // 三元光栅操作码（详见备注）
			);


	setfillstyle(BKCLR,SOLID_FILL);
	bar(G_SPACE_X,G_SPACE_Y,G_SPACE_X+ROW*BLOCK_SIZE-BLOCK_GAP,G_SPACE_Y+BLOCK_SIZE);
	setfillstyle(FGCLR,SOLID_FILL);
//	bar(G_SPACE_X+PREVIEW_X*BLOCK_SIZE,G_SPACE_Y+PREVIEW_Y*BLOCK_SIZE,
//	G_SPACE_X+PREVIEW_X*BLOCK_SIZE+B_UNIT*BLOCK_SIZE,G_SPACE_Y+PREVIEW_Y*BLOCK_SIZE+B_UNIT*BLOCK_SIZE);

	drawStageline();



}

void changeColor(Block block)
{
		int random;

		random=Rand(0,COLOR_NUM-1);
		drawBlk(block,color[random]);
}


/*void printScore()
{

	setfont(S_FONT_LENGTH,S_FONT_WIDTH,S_FONT_TYPE);
	outtextxy(SCORE_POS_X,SCORE_POS_Y-S_FONT_LENGTH,"得分:");

	outtextxy(SCORE_POS_X,WIDTH/2,"作者:");
	outtextxy(SCORE_POS_X,WIDTH/2+(int)(1.5*S_FONT_LENGTH),"   郝运 QQ2642223233");


	setfont(L_FONT_LENGTH,L_FONT_WIDTH,L_FONT_TYPE);
	outtextxy(SCORE_POS_X,SCORE_POS_Y,score);//打印分数;
}*/

/*
//显示边界线,预览提示，分数提示和分数
void showFrame()
{
	moveto(G_SPACE_X, 0);
    lineto(G_SPACE_X, WIDTH);
	moveto(LENGTH - G_SPACE_X, 0);
    lineto(LENGTH - G_SPACE_X, WIDTH);//画游戏界面线

	setfont(S_FONT_LENGTH,S_FONT_WIDTH,S_FONT_TYPE);
	outtextxy(SCORE_POS_X,0,"预览：");

//	printScore();



}

void printPause()
{
		setfont(S_FONT_LENGTH,S_FONT_WIDTH,S_FONT_TYPE);
	outtextxy(SCORE_POS_X+(int)(S_FONT_LENGTH*2.5),0,"暂停中任意键继续");

}*/