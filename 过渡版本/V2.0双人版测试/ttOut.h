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

//绘制基本的含空隙的正方形
//void drawSquare(int x, int y, int valid = TRUE);
void drawSquare(Point originPoint,Point squarePoint,bool valid);


void showFrame();

//由舞台数组绘制舞台
//
void drawGameArea(int playerNum);

void drawStageLine();

//绘制俄罗斯方块
void drawBlock(int x, int y, int blockType, int mode = NORMAL, int blockDir = 0);

//覆盖上一个方块，并绘制新的方块
void updateBlock(Block tempBlock, Block nowBlock);

void delColumn(int line);

//void changeColor(Block block);

void printPause();*/


#endif