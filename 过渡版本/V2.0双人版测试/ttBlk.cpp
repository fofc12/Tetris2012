#include "const.h"

extern swap[4][4];
extern WORD allBlock[TOTAL_BLOCK+1][4];
extern Player g_player[];
extern COLORREF color[COLOR_NUM];


Block createBlk()
{
    Block newBlock;

    newBlock.point = createPt(1, 1); //设置坐标
    newBlock.blockDir = 0;
    newBlock.blockType = Rand(1, TOTAL_BLOCK); //设置类型
    newBlock.blockCLR = color[Rand(0, COLOR_NUM-1)]; //设置颜色

    return newBlock;
}

bool dropNowBlk(int playerNum)
{
    bool success;
    Block tpBlock = g_player[playerNum].nowBlk;

    tpBlock.point.y++;

    if(detectCl(tpBlock, g_player[playerNum].area.state) || outOfRange(tpBlock))
    {
        success = false;

        g_player[playerNum].dropped = true; //改变状态，不应用
    }
    else
    {
        success = true;
        g_player[playerNum].nowBlk = tpBlock; //应用
    }

    return success;
}

Block preToNow(Block block)
{
    block.point.x = BIRTH_X;
    block.point.y = BIRTH_Y;

    return block;
}



void OnUp(int playerNum)
{
    Block bakBlock = g_player[playerNum].nowBlk;


    {
        (bakBlock.blockDir) = (bakBlock.blockDir) + 1;
        if(bakBlock.blockDir == 4)bakBlock.blockDir = 0;
    }//旋转

    if(!detectCl(bakBlock, g_player[playerNum].area.state) && !outOfRange(bakBlock))g_player[playerNum].nowBlk = bakBlock;
}


void OnLeft(int playerNum)
{
    Block bakBlock = (g_player[playerNum].nowBlk);

    bakBlock.point.x--;//x运动
    (bakBlock.point.x) = (bakBlock.point.x) + (bakBlock.point.x <= 0) -
                         (bakBlock.point.x > (ROW - B_UNIT +
                                 getRtBlankLine(bakBlock.blockType, bakBlock.blockDir)) + 1); //超出边界修正

    if(!detectCl(bakBlock, g_player[playerNum].area.state) && !outOfRange(bakBlock))g_player[playerNum].nowBlk = bakBlock;
}

void OnRight(int playerNum)
{
    Block bakBlock = (g_player[playerNum].nowBlk);

    bakBlock.point.x++;//x运动
    (bakBlock.point.x) = (bakBlock.point.x) + (bakBlock.point.x <= 0) -
                         (bakBlock.point.x > (ROW - B_UNIT +
                                 getRtBlankLine(bakBlock.blockType, bakBlock.blockDir)) + 1); //超出边界修正

    if(!detectCl(bakBlock, g_player[playerNum].area.state) && !outOfRange(bakBlock))g_player[playerNum].nowBlk = bakBlock;
}


/*
//产生一个俄罗斯方块
Block createBlock(int mode)
{
    int x, y, type;
	COLORREF clr;
    Block newBlock;

    if(mode == NORMAL)
    {
        x = BIRTH_X;
        y = BIRTH_Y;
    }
    else
    {
        x = PREVIEW_X;
        y = PREVIEW_Y;
    }
    type = Rand(0, 6);
	clr=Rand(0,COLOR_NUM);



    newBlock.point.x = x;
    newBlock.point.y = y;
	 newBlock.blockType = type;
	 newBlock.blockCLR=clr;

    return newBlock;

}




//令一个方块下落
int dropBlock(int playerNum)
{
    Block bakBlock = (g_player[playerNum].nowBlk);
    bakBlock.point.y++;

    if(
		(
			bakBlock.point.y >
			(COLUMN - B_UNIT + 1 +getBottomBlankLine(bakBlock.blockType, bakBlock.blockDir))
		)
		|| detectCollision(bakBlock,*g_player[playerNum].pstage)
	  )return FALSE;
    else
    {
        (g_player[playerNum].nowBlk) = bakBlock;

        return TRUE;
    }
}


//令一个方块移动
int moveBlock(int dir, int playerNum)
{
	int i;
    Block bakBlock=(g_player[playerNum].nowBlk);

    bakBlock.point.x = (bakBlock.point.x) + ((dir & CMD_RIGHT)!=0) - ((dir & CMD_LEFT)!=0);//x运动
    (bakBlock.point.x) = (bakBlock.point.x) + (bakBlock.point.x <= 0) -
					 (bakBlock.point.x > (ROW-B_UNIT+
						getRightBlankLine(bakBlock.blockType,bakBlock.blockDir))+1);//超出边界修正

	if(dir & CMD_UP)
    {
        (bakBlock.blockDir) = (bakBlock.blockDir) + 1;
        if(bakBlock.blockDir == 4)bakBlock.blockDir = 0;
    }//旋转


	i=(detectCollision(bakBlock,*g_player[playerNum].pstage) || outOfRange(bakBlock));
	if(i==FALSE)(g_player[playerNum].nowBlk)=bakBlock;//如果没有发生碰撞则应用新方块


	if (dir & CMD_DOWN)
	{
		i=dropBlock(playerNum);

	if(i==FALSE)return FALSE;//move的失败源于drop的失败
    else return TRUE;}

	return TRUE;
}


//在方块落下时将其归到舞台数组中去
void transformBlock(Block blk,Area stage)
{
    int i, j;
	Point tempPoint={0,0};

    WORDToArr(allBlock[blk.blockType][blk.blockDir]);
    for(i = 0; i <= 3; i++)
        for(j = 0; j <= 3; j++)
		{
			tempPoint.x=blk.point.x;
			tempPoint.y=blk.point.y;
            setStage(tempPoint, swap[i][j],stage);
		}

}*/



