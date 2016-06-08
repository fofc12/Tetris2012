#ifndef _TT_BLK_H_
#define _TT_BLK_H_

#include"const.h"

Block createBlk();//产生一个俄罗斯方块

bool dropNowBlk(int playerNum);


Block preToNow(Block previewBlock);


void OnUp(int player);

void OnLeft(int player);

void OnRight(int player);

/*
//产生一个俄罗斯方块
Block createBlock(int mode=NORMAL);

Block preToNow(Block previewBlock);

//令num号玩家方块的下落
int dropBlock(int playerNum);

//令num号玩家的方块移动，方向为dir
int moveBlock(int dir, int playerNum);

//在方块落下时将其归到舞台数组中去
void transformBlock(Block nowBlock,Area stage);*/

#endif