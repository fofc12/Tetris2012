#include"const.h"


#define WBLK_SIZE 44
#define WBLK_GAP 2
#define WBLK_DEPTH 10
#define BASE_SIZE 10

typedef struct WBlk
{
    int x;
    int y;
    int type[3][2];
    int blockCLR;
    //	Area *pArea;//所属的舞台
} WBlock;


int addOne(int num, int flag);//加减运算，flag==1加1，flag==-1减1
void moveWBlk(int *p);

void initWel();
void endWel();
void printTetris();
void drawBlkxy(int x, int y);
void showBase();
void showWBlk(int num);
void showTip();
void showHelp();







