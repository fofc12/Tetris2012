#pragma once

#include"const.h"

//Ϊ��̨���鸳ֵ
void setStage(int x, int y, int value);
int detectCollision(Block block);

int reachTop(Block nowBlock);

int fullColumn();