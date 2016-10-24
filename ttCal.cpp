#include"const.h"


//构造点
Point createPt(int x, int y)
{
    Point tp;

    tp.x = x;
    tp.y = y;

    return tp;
}

//随机数发生器
int Rand(int min, int max)
{
    int random;
    random = rand() % (max - min + 1) + min;
    return random;
}

//WORD转化为数组
void WORDToArr(WORD b)
{
    int i;

    for(i = 0; i < 16; i++)
    {

        swap[i % 4 ][i / 4] = ((b & 0x8000) > 0);
        b <<= 1;
    }
}

int length(char a[])
{
    /*返回位数*/
    int c = 0;
    while(*a++)c++;
    return c;
}


void copy(char x[])
{
    /*逆序*/
    char c;
    char *s = x + length(x) - 1; /*指向a的末位*/
    while(s > x)
    {
        c = *s;
        *s-- = *x;
        *x++ = c;
    }
}


void add(char a[], int i)
{
    /*大数a加1*/
    char *s = a;
    copy(a);/*对a逆序处理，便于进位*/
    (*s) += i;
    while(*s > '9') /*如果需要进位*/
    {
        *s -= 10; /*当前位-10*/
        if(*(s + 1))
        {
            s++;
            (*s)++; /*下一位+1*/
        }
        else  /*最后的进位*/
        {
            *(++s) = '1';
            *(++s) = 0;
            break;
        }
    }
    copy(a);/*a逆序还原*/
}


int arrToNum(char a[])
{

    int i = 0, j = 0, temp = 1, ret = 0;
    /*大数a加1*/
    copy(a);/*对a逆序处理，便于进位*/

    for(i = 0; i < length(a); i++)
    {
        temp = 1;
        for(j = 0; j < i; j++)
            temp *= 10;


        ret += (a[i] - '0') * temp;
    }
    copy(a);/*a逆序还原*/

    return ret;

}



int getRtBlankLine(int blockType, int blockDir)
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

//得到方块的底部空行
int getBtBlankLine(int blockType, int blockDir)
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

/*
int scoreToWait()
{

	return 1000;
}




bool noBlkOnScreen(Player player)
{
	if(player.nowBlk.point.y-
			getBottomBlankLine(player.nowBlk.blockType, player.nowBlk.blockDir)
			+B_UNIT<1)
	return true;
	else return false;
}
*/