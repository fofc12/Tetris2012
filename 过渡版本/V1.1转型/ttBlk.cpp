#include "const.h"

/*
#include "ttBlk.h"
#include "ttCal.h"//生成方块要随机数
#include "ttStage.h"//对方块的操作和舞台息息相关
#include "ttIn.h"//操作的具体实现取决于命令*/

extern Block EMPTY_BLOCK;
extern swap[4][4];
extern WORD allBlock[7][4];


//产生一个俄罗斯方块
Block createBlock(int mode)
{
    int x, y, type;
    COLORREF clr;
    Block newBlock = EMPTY_BLOCK;

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
    clr = Rand(0, COLOR_NUM);



    newBlock.x = x;
    newBlock.y = y;
    newBlock.blockType = type;
    newBlock.blockCLR = clr;

    return newBlock;

}


Block preToNow(Block previewBlock)
{
    previewBlock.x = BIRTH_X;
    previewBlock.y = BIRTH_Y;

    return previewBlock;
}

//令一个方块下落
int dropBlock(Block *pnowBlock)
{
    Block bakBlock = (*pnowBlock);
    bakBlock.y++;

    if(
        (
            bakBlock.y >
            (COLUMN - B_UNIT + 1 + getBottomBlankLine(bakBlock.blockType, bakBlock.blockDir))
        )
        || detectCollision(bakBlock)
    )return FALSE;
    else
    {
        (*pnowBlock) = bakBlock;

        return TRUE;
    }
}


//令一个方块移动
int moveBlock(int dir, Block *pnowBlock)
{
    int i;
    Block bakBlock = (*pnowBlock);

    bakBlock.x = (bakBlock.x) + ((dir & CMD_RIGHT) != 0) - ((dir & CMD_LEFT) != 0); //x运动
    (bakBlock.x) = (bakBlock.x) + (bakBlock.x <= 0) -
                   (bakBlock.x > (ROW - B_UNIT +
                                  getRightBlankLine(bakBlock.blockType, bakBlock.blockDir)) + 1); //超出边界修正

    if(dir & CMD_UP)
    {
        (bakBlock.blockDir) = (bakBlock.blockDir) + 1;
        if(bakBlock.blockDir == 4)bakBlock.blockDir = 0;
    }//旋转


    i = detectCollision(bakBlock);
    if(bakBlock.x > (ROW - B_UNIT +
                     getRightBlankLine(bakBlock.blockType, bakBlock.blockDir)
                     + 1)
            ||
            (bakBlock.y >
             (COLUMN - B_UNIT + 1 +
              getBottomBlankLine(bakBlock.blockType, bakBlock.blockDir)
             )
            )
      )i = TRUE;
    if(i == FALSE)(*pnowBlock) = bakBlock; //如果没有发生碰撞则应用新方块


    if (dir & CMD_DOWN)
    {
        i = dropBlock(pnowBlock);

        if(i == FALSE)return FALSE; //move的失败源于drop的失败
        else return TRUE;
    }

    return TRUE;
}


//在方块落下时将其归到舞台数组中去
void transformBlock(Block nowBlock)
{
    int i, j;

    WORDToArr(allBlock[nowBlock.blockType][nowBlock.blockDir]);
    for(i = 0; i <= 3; i++)
        for(j = 0; j <= 3; j++)
            setStage(nowBlock.x + i, nowBlock. y + j , swap[i][j]);

}



