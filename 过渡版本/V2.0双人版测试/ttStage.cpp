#include"const.h"

//extern stage[11][21];
extern swap[4][4];
extern WORD allBlock[TOTAL_BLOCK+1][4];
extern Player g_player[];



bool detectCl(Block blk, int state[ROW+2][COLUMN+2])
{

    int i, j;

    WORDToArr(allBlock[blk.blockType][blk.blockDir]);
    for(i = 0; i <= 3; i++)
        for(j = 0; j <= 3; j++)
        {
            if(blk.point.y >= 1 && state[blk.point.x+i][blk.point.y+j] == 1 && swap[i][j] == 1) //block.y>=1
                return true;//重叠

        }

    //根据跳出位置不同确定返回值
    return false;
}


bool outOfRange(Block blk)
{
    bool ret = false;

    if(blk.point.x > (ROW - B_UNIT + getRtBlankLine(blk.blockType, blk.blockDir) + 1)
            || (blk.point.y > (COLUMN - B_UNIT + 1 + getBtBlankLine(blk.blockType, blk.blockDir))))
        ret = true;

    if	(
        blk.point.y >
        (COLUMN - B_UNIT + 1 + getBtBlankLine(blk.blockType, blk.blockDir))
    )ret = true;


    return ret;

}

//为舞台数组赋值
void signState(int playerNum, Point pt, Point move)
{
    if(pt.x >= 0 && pt.y >= 0 && pt.x + move.x <= ROW + 1 && pt.y + move.y <= COLUMN + 1)
        g_player[playerNum].area.state[pt.x+move.x][pt.y+move.y] = 1;

}

void saveState(int playerNum, Block block)
{
    int i, j;

    WORDToArr(allBlock[block.blockType][block.blockDir]);
    for(i = 0; i <= 3; i++)
        for(j = 0; j <= 3; j++)
            if(block.blockType != 0 && swap[i][j] > 0)signState(playerNum, createPt(block.point.x, block.point.y) , createPt(i, j) );

}

int fullColumn(int playerNum)
{
    int i, j, x, y, flag, count = 0;

    for(i = 1; i <= COLUMN; i++)
    {
        flag = TRUE;
        for(j = 1; j <= ROW; j++)
            if(g_player[playerNum].area.state[j][i] == 0)flag = FALSE; //一个没有则改行没满
        if(flag == TRUE) //如果标记还保持着真
        {
            for(y = i; y > 0; y--)
                for(x = 1; x <= ROW; x++)
                    g_player[playerNum].area.state[x][y] = g_player[playerNum].area.state[x][y-1]; //删除本行

            delColumn(playerNum, i);
            count++;
        }
    }

    if(count > 0 && playerNum == 1)mciSendString("play data\\cat.mp3", NULL, 0, NULL);
    if(count > 0 && playerNum == 2)mciSendString("play data\\dog.mp3", NULL, 0, NULL);
    if(count > 0 && g_player[1].score <= 0 && g_player[2].score <= 0)
    {
        mciSendString("play data\\1FB.mp3", NULL, 0, NULL);
        return (count + 2);
    }

    if(count == 2)mciSendString("play data\\2DK.mp3", NULL, 0, NULL);
    if(count == 3)mciSendString("play data\\3TK.mp3", NULL, 0, NULL);
    if(count == 4)mciSendString("play data\\4UK.mp3", NULL, 0, NULL);

    return count;

}

void newColumn(int playerNum)
{
    int i,  x, y, count = 0;
    g_player[playerNum].nowBlk.point.y--;

    for(y = 0; y < 20; y++)
        for(x = 1; x <= ROW; x++)
            g_player[playerNum].area.state[x][y] = g_player[playerNum].area.state[x][y+1];


    for(i = 1; i <= 10; i++)
    {
        g_player[playerNum].area.state[i][20] = Rand(0, 1);
    }

    //	drawBlk(tpBlk,CLEAR);
    addColumn(playerNum);
    drawStage(playerNum);
}


bool reachTop(int playerNum)
{
    int i;
    bool flag = false;

    for(i = 1; i <= 10; i++)
        if(g_player[playerNum].area.state[i][0] == 1)
            flag = true;

    return flag;
}


/*

int detectCollision(Block blk,Area stage)
{
	int i,j;

    WORDToArr(allBlock[blk.blockType][blk.blockDir]);
    for(i = 0; i <= 3; i++)
        for(j = 0; j <= 3; j++)
		{
			if(blk.point.y>=1 && stage.state[blk.point.x+i][blk.point.y+j]==1 && swap[i][j]==1)//block.y>=1
				return TRUE;//重叠

		}

	return FALSE;//根据跳出位置不同确定返回值
}





*/