#include "const.h"

//���鴴��
Block createBlk()
{
    Block newBlock;

    newBlock.point = createPt(1, 1); //��������
    newBlock.blockDir = 0;
    newBlock.blockType = Rand(1, TOTAL_BLOCK); //��������
    newBlock.blockCLR = color[Rand(0, COLOR_NUM-1)]; //������ɫ

    return newBlock;
}

//��������
bool dropNowBlk(int playerNum)
{
    bool success;
    Block tpBlock = g_player[playerNum].nowBlk;

    tpBlock.point.y++;

    if(detectCl(tpBlock, g_player[playerNum].area.state) || outOfRange(tpBlock))
    {
        success = false;

        g_player[playerNum].dropped = true; //�ı�״̬����Ӧ��
    }
    else
    {
        success = true;
        g_player[playerNum].nowBlk = tpBlock; //Ӧ��
    }

    return success;
}

//����ת��
Block preToNow(Block block)
{
    block.point.x = BIRTH_X;
    block.point.y = BIRTH_Y;

    return block;
}


//����
void OnUp(int playerNum)
{
    Block bakBlock = g_player[playerNum].nowBlk;


    {
        (bakBlock.blockDir) = (bakBlock.blockDir) + 1;
        if(bakBlock.blockDir == 4)bakBlock.blockDir = 0;
    }//��ת

    if(!detectCl(bakBlock, g_player[playerNum].area.state) && !outOfRange(bakBlock))g_player[playerNum].nowBlk = bakBlock;
}

//����
void OnLeft(int playerNum)
{
    Block bakBlock = (g_player[playerNum].nowBlk);

    bakBlock.point.x--;//x�˶�
    (bakBlock.point.x) = (bakBlock.point.x) + (bakBlock.point.x <= 0) -
                         (bakBlock.point.x > (ROW - B_UNIT +
                                 getRtBlankLine(bakBlock.blockType, bakBlock.blockDir)) + 1); //�����߽�����

    if(!detectCl(bakBlock, g_player[playerNum].area.state) && !outOfRange(bakBlock))g_player[playerNum].nowBlk = bakBlock;
}

//����
void OnRight(int playerNum)
{
    Block bakBlock = (g_player[playerNum].nowBlk);

    bakBlock.point.x++;//x�˶�
    (bakBlock.point.x) = (bakBlock.point.x) + (bakBlock.point.x <= 0) -
                         (bakBlock.point.x > (ROW - B_UNIT +
                                 getRtBlankLine(bakBlock.blockType, bakBlock.blockDir)) + 1); //�����߽�����

    if(!detectCl(bakBlock, g_player[playerNum].area.state) && !outOfRange(bakBlock))g_player[playerNum].nowBlk = bakBlock;
}