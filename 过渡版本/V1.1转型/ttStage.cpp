#include"const.h"

extern stage[11][21];
extern swap[4][4];
extern WORD allBlock[7][4];

//Ϊ��̨���鸳ֵ
void setStage(int x, int y, int value)
{
    if(x >= 0 && y >= 0)
        stage[x][y] += value;

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