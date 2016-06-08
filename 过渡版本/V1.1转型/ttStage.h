#pragma once

#include"const.h"

//为舞台数组赋值
void setStage(int x, int y, int value);
int detectCollision(Block block);

int reachTop(Block nowBlock);

int fullColumn();