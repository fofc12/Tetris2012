#pragma once

#include"const.h"

bool detectCl(Block block, int state[ROW+2][COLUMN+2]);
bool outOfRange(Block blk);

void signState(int playerNum, Point pt, Point move);

void saveState(int playerNum, Block block);

int fullColumn(int playerNum);
void newColumn(int playerNum);

bool reachTop(int playerNum);
