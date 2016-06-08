#ifndef _MAIN_OP_H_
#define _MAIN_OP_H_

#include"const.h"
#include"draw.h"
#include"input.h"

//�����������
int Rand(int min, int max);

//Ϊ��̨���鸳ֵ
void setStage(int x, int y, int value);

//WORDת��Ϊ���Ϊ(x,y)�����飬����x,y���ϸ��Ե�ƫ������Ϊ����ִ�к���func
void WORDToArr(WORD b);

//��ײ���
int detectCollision(Block bakBlock);

//����һ������˹����
Block createBlock(int mode = NORMAL);

getRightBlankLine(int blockType, int blockDir);

//�õ�����ĵײ�����
getBottomBlankLine(int blockType, int blockDir);

//��һ����������
int moveBlock(int idir, Block *pnowBlock);

int dropBlock(Block *pnowBlock);

//�ڷ�������ʱ����鵽��̨������ȥ
void transformBlock(Block nowBlock);

int reachTop(Block nowBlock);

int fullColumn();

#endif