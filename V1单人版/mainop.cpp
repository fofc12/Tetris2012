#include "mainop.h"
#include "draw.h"

//�����������
int Rand(int min, int max)
{
    int random;
    random = rand() % (max - min + 1) + min;
    return random;
}

//Ϊ��̨���鸳ֵ
void setStage(int x, int y, int value)
{
    if(x >= 0 && y >= 0)
        stage[x][y] += value;

}

/*
//WORDת��Ϊ���Ϊ(x,y)�����飬����x,y���ϸ��Ե�ƫ������Ϊ����ִ�к���func
void WORDToArr(WORD b,int x,int y,void (*func)(int x,int y,int value))
{
	int i;

	for(i = 0; i < 16; i++)
    {

       (*func)(x + i % 4 , y + i / 4,(b & 0x8000) > 0);
        b <<= 1;
    }
}*/


//WORDת��Ϊ����
void WORDToArr(WORD b)
{
    int i;

    for(i = 0; i < 16; i++)
    {

        swap[i % 4 ][i / 4] = ((b & 0x8000) > 0);
        b <<= 1;
    }
}


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

int getRightBlankLine(int blockType, int blockDir)
{
    int line = 0;
    WORD value = allBlock[blockType][blockDir];

    WORDToArr(value);

    if(swap[3][0] == 0 && swap[3][1] == 0 && swap[3][2] == 0 && swap[3][3] == 0)line += 1;
    else return line;
    if(swap[2][0] == 0 && swap[2][1] == 0 && swap[2][2] == 0 && swap[2][3] == 0)line += 1;
    else return line;
    if(swap[1][0] == 0 && swap[1][1] == 0 && swap[1][2] == 0 && swap[1][3] == 0)line += 1;
    else return line;
    if(swap[0][0] == 0 && swap[0][1] == 0 && swap[0][2] == 0 && swap[0][3] == 0)line += 1;

    return line;

}

//�õ�����ĵײ�����
int getBottomBlankLine(int blockType, int blockDir)
{
    int line = 0;
    WORD value = allBlock[blockType][blockDir];

    WORDToArr(value);

    if(swap[0][3] == 0 && swap[1][3] == 0 && swap[2][3] == 0 && swap[3][3] == 0)line += 1;
    else return line;
    if(swap[0][2] == 0 && swap[1][2] == 0 && swap[2][2] == 0 && swap[3][2] == 0)line += 1;
    else return line;
    if(swap[0][1] == 0 && swap[1][1] == 0 && swap[2][1] == 0 && swap[3][1] == 0)line += 1;
    else return line;
    if(swap[0][0] == 0 && swap[1][0] == 0 && swap[2][0] == 0 && swap[3][0] == 0)line += 1;

    return line;

}

//��һ�������ƶ�
int moveBlock(int dir, Block *pnowBlock)
{
    int i;
    Block bakBlock = (*pnowBlock);

    bakBlock.x = (bakBlock.x) + (dir == CMD_RIGHT) - (dir == CMD_LEFT);//x�˶�
    (bakBlock.x) = (bakBlock.x) + (bakBlock.x <= 0) -
                   (bakBlock.x > (ROW - B_UNIT +
                                  getRightBlankLine(bakBlock.blockType, bakBlock.blockDir)) + 1); //�����߽�����

    if(dir == CMD_UP)
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


    if (dir == CMD_DOWN)
    {
        i = dropBlock(pnowBlock);

        if(i == FALSE)return FALSE; //move��ʧ��Դ��drop��ʧ��
        else return TRUE;
    }

    return TRUE;
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

//�ڷ�������ʱ����鵽��̨������ȥ
void transformBlock(Block nowBlock)
{
    int i, j;

    WORDToArr(allBlock[nowBlock.blockType][nowBlock.blockDir]);
    for(i = 0; i <= 3; i++)
        for(j = 0; j <= 3; j++)
            setStage(nowBlock.x + i, nowBlock. y + j , swap[i][j]);

}

int detectCollision(Block block)
{
    int i, j;

    WORDToArr(allBlock[block.blockType][block.blockDir]);
    for(i = 0; i <= 3; i++)
        for(j = 0; j <= 3; j++)
        {
            if(block.y >= 1 && stage[block.x+i][block.y+j] == 1 && swap[i][j] == 1) //block.y>=1
                return TRUE;//�ص�
        }
    return FALSE;//��������λ�ò�ͬȷ������ֵ
}


int reachTop(Block nowBlock)
{
    int i, flag = FALSE;

    for(i = 1; i <= 10; i++)
        if(stage[i][0] == 1)
            flag = TRUE;

    return flag;
}

int fullColumn()
{
    int i, j, x, y, flag, count = 0;

    for(i = 1; i <= 20; i++)
    {
        flag = TRUE;
        for(j = 1; j <= 10; j++)
            if(stage[j][i] == 0)flag = FALSE; //һ��û�������û��
        if(flag == TRUE) //�����ǻ���������
        {
            for(y = i; y > 0; y--)
                for(x = 1; x <= 10; x++)
                    stage[x][y] = stage[x][y-1]; //ɾ������

            //	for(x=1;x<=10;x++)
            //			stage[x][0]=0;
            delColumn(i);
            count++;
        }
    }
    if(count > 0)printTetris();
    return count;
}
