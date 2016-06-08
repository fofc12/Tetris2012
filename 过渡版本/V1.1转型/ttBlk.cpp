#include "const.h"

/*
#include "ttBlk.h"
#include "ttCal.h"//���ɷ���Ҫ�����
#include "ttStage.h"//�Է���Ĳ�������̨ϢϢ���
#include "ttIn.h"//�����ľ���ʵ��ȡ��������*/

extern Block EMPTY_BLOCK;
extern swap[4][4];
extern WORD allBlock[7][4];


//����һ������˹����
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

//��һ����������
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


//��һ�������ƶ�
int moveBlock(int dir, Block *pnowBlock)
{
    int i;
    Block bakBlock = (*pnowBlock);

    bakBlock.x = (bakBlock.x) + ((dir & CMD_RIGHT) != 0) - ((dir & CMD_LEFT) != 0); //x�˶�
    (bakBlock.x) = (bakBlock.x) + (bakBlock.x <= 0) -
                   (bakBlock.x > (ROW - B_UNIT +
                                  getRightBlankLine(bakBlock.blockType, bakBlock.blockDir)) + 1); //�����߽�����

    if(dir & CMD_UP)
    {
        (bakBlock.blockDir) = (bakBlock.blockDir) + 1;
        if(bakBlock.blockDir == 4)bakBlock.blockDir = 0;
    }//��ת


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
    if(i == FALSE)(*pnowBlock) = bakBlock; //���û�з�����ײ��Ӧ���·���


    if (dir & CMD_DOWN)
    {
        i = dropBlock(pnowBlock);

        if(i == FALSE)return FALSE; //move��ʧ��Դ��drop��ʧ��
        else return TRUE;
    }

    return TRUE;
}


//�ڷ�������ʱ����鵽��̨������ȥ
void transformBlock(Block nowBlock)
{
    int i, j;

    WORDToArr(allBlock[nowBlock.blockType][nowBlock.blockDir]);
    for(i = 0; i <= 3; i++)
        for(j = 0; j <= 3; j++)
            setStage(nowBlock.x + i, nowBlock. y + j , swap[i][j]);

}



