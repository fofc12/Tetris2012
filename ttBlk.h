#ifndef _TT_BLK_H_
#define _TT_BLK_H_

#include"const.h"

Block createBlk();//����һ������˹����

bool dropNowBlk(int playerNum);


Block preToNow(Block previewBlock);


void OnUp(int player);

void OnLeft(int player);

void OnRight(int player);

/*
//����һ������˹����
Block createBlock(int mode=NORMAL);

Block preToNow(Block previewBlock);

//��num����ҷ��������
int dropBlock(int playerNum);

//��num����ҵķ����ƶ�������Ϊdir
int moveBlock(int dir, int playerNum);

//�ڷ�������ʱ����鵽��̨������ȥ
void transformBlock(Block nowBlock,Area stage);*/

#endif