#include "const.h"

//方块创建
Block createBlk()
{
    Block newBlock;

    newBlock.point = createPt(1, 1); //设置坐标
    newBlock.blockDir = 0;
    newBlock.blockType = Rand(1, TOTAL_BLOCK); //设置类型
    newBlock.blockCLR = color[Rand(0, COLOR_NUM-1)]; //设置颜色

    return newBlock;
}

//方块下落
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

//方块转换
Block preToNow(Block block)
{
    block.point.x = BIRTH_X;
    block.point.y = BIRTH_Y;

    return block;
}


//向上
void OnUp(int playerNum)
{
    Block bakBlock = g_player[playerNum].nowBlk;


    {
        (bakBlock.blockDir) = (bakBlock.blockDir) + 1;
        if(bakBlock.blockDir == 4)bakBlock.blockDir = 0;
    }//旋转

    if(!detectCl(bakBlock, g_player[playerNum].area.state) && !outOfRange(bakBlock))g_player[playerNum].nowBlk = bakBlock;
}

//向左
void OnLeft(int playerNum)
{
    Block bakBlock = (g_player[playerNum].nowBlk);

    bakBlock.point.x--;//x运动
    (bakBlock.point.x) = (bakBlock.point.x) + (bakBlock.point.x <= 0) -
                         (bakBlock.point.x > (ROW - B_UNIT +
                                 getRtBlankLine(bakBlock.blockType, bakBlock.blockDir)) + 1); //超出边界修正

    if(!detectCl(bakBlock, g_player[playerNum].area.state) && !outOfRange(bakBlock))g_player[playerNum].nowBlk = bakBlock;
}

//向右
void OnRight(int playerNum)
{
    Block bakBlock = (g_player[playerNum].nowBlk);

    bakBlock.point.x++;//x运动
    (bakBlock.point.x) = (bakBlock.point.x) + (bakBlock.point.x <= 0) -
                         (bakBlock.point.x > (ROW - B_UNIT +
                                 getRtBlankLine(bakBlock.blockType, bakBlock.blockDir)) + 1); //超出边界修正

    if(!detectCl(bakBlock, g_player[playerNum].area.state) && !outOfRange(bakBlock))g_player[playerNum].nowBlk = bakBlock;
}