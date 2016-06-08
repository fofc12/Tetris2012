#ifndef _TT_OUT_H_
#define _TT_OUT_H_


#include"const.h"

void drawSquare(Point squarePoint);

void drawBlk(Block block, int mode = NORMAL);

void refreshBlk(Block blk1, Block blk2);

void drawStage(int playerNum);

void addColumn(int playerNum);
void delColumn(int playerNum, int line);

void drawStageLine();

void printScore(int time);

/*
void printTetris();

//���ƻ����ĺ���϶��������
//void drawSquare(int x, int y, int valid = TRUE);
void drawSquare(Point originPoint,Point squarePoint,bool valid);


void showFrame();

//����̨���������̨
//
void drawGameArea(int playerNum);

void drawStageLine();

//���ƶ���˹����
void drawBlock(int x, int y, int blockType, int mode = NORMAL, int blockDir = 0);

//������һ�����飬�������µķ���
void updateBlock(Block tempBlock, Block nowBlock);

void delColumn(int line);

//void changeColor(Block block);

void printPause();*/


#endif