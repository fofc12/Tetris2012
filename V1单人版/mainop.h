#ifndef _MAIN_OP_H_
#define _MAIN_OP_H_

#include"const.h"
#include"draw.h"
#include"input.h"

//随机数发生器
int Rand(int min, int max);

//为舞台数组赋值
void setStage(int x, int y, int value);

//WORD转化为起点为(x,y)的数组，并用x,y加上各自的偏移量作为参数执行函数func
void WORDToArr(WORD b);

//碰撞检测
int detectCollision(Block bakBlock);

//产生一个俄罗斯方块
Block createBlock(int mode = NORMAL);

getRightBlankLine(int blockType, int blockDir);

//得到方块的底部空行
getBottomBlankLine(int blockType, int blockDir);

//令一个方块下落
int moveBlock(int idir, Block *pnowBlock);

int dropBlock(Block *pnowBlock);

//在方块落下时将其归到舞台数组中去
void transformBlock(Block nowBlock);

int reachTop(Block nowBlock);

int fullColumn();

#endif