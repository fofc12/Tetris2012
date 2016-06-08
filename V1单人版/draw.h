#ifndef _DRAW_H_
#define _DRAW_H_


#include"const.h"


void printTetris();

//绘制一些基本的物件
//
void init();

//绘制基本的含空隙的正方形
void drawSquare(int x, int y, int valid = TRUE);

void showFrame();

//由舞台数组绘制舞台
void drawStage();

void drawStageLine();

//绘制俄罗斯方块
void drawBlock(int x, int y, int blockType, int blockCLR, int mode = NORMAL, int blockDir = 0);

//覆盖上一个方块，并绘制新的方块
void updateBlock(Block tempBlock, Block nowBlock);

void delColumn(int line);

void changeColor(Block block);

void printPause();


#endif