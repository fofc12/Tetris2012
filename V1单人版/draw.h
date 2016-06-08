#ifndef _DRAW_H_
#define _DRAW_H_


#include"const.h"


void printTetris();

//����һЩ���������
//
void init();

//���ƻ����ĺ���϶��������
void drawSquare(int x, int y, int valid = TRUE);

void showFrame();

//����̨���������̨
void drawStage();

void drawStageLine();

//���ƶ���˹����
void drawBlock(int x, int y, int blockType, int blockCLR, int mode = NORMAL, int blockDir = 0);

//������һ�����飬�������µķ���
void updateBlock(Block tempBlock, Block nowBlock);

void delColumn(int line);

void changeColor(Block block);

void printPause();


#endif