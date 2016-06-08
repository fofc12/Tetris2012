#ifndef _TT_BLK_H_
#define _TT_BLK_H_

#include"const.h"

//产生一个俄罗斯方块
Block createBlock(int mode = NORMAL);

Block preToNow(Block previewBlock);

//令一个方块下落
int dropBlock(Block *pnowBlock);

//令一个方块移动
int moveBlock(int dir, Block *pnowBlock);

//在方块落下时将其归到舞台数组中去
void transformBlock(Block nowBlock);

#endif