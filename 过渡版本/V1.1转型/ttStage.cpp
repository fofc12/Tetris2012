#include"const.h"

extern stage[11][21];
extern swap[4][4];
extern WORD allBlock[7][4];

//为舞台数组赋值
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
                return TRUE;//重叠

        }

    return FALSE;//根据跳出位置不同确定返回值
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
            if(stage[j][i] == 0)flag = FALSE; //一个没有则改行没满
        if(flag == TRUE) //如果标记还保持着真
        {
            for(y = i; y > 0; y--)
                for(x = 1; x <= 10; x++)
                    stage[x][y] = stage[x][y-1]; //删除本行

            //	for(x=1;x<=10;x++)
            //			stage[x][0]=0;
            delColumn(i);
            count++;
        }
    }

    if(count > 0)printTetris();
    return count;

}