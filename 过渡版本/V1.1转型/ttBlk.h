#ifndef _TT_BLK_H_
#define _TT_BLK_H_

#include"const.h"

//����һ������˹����
Block createBlock(int mode = NORMAL);

Block preToNow(Block previewBlock);

//��һ����������
int dropBlock(Block *pnowBlock);

//��һ�������ƶ�
int moveBlock(int dir, Block *pnowBlock);

//�ڷ�������ʱ����鵽��̨������ȥ
void transformBlock(Block nowBlock);

#endif