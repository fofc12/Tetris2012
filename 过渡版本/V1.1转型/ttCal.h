#pragma once
#include "const.h"

//随机数发生器
int Rand(int min, int max);

//WORD转化为数组
void WORDToArr(WORD b);

//对数组数操作

//取位数
int length(char a[]);

//反向
void copy(char x[]);

//数组数加运算
void add(char a[], int i);

//数组数转化为普通数
int arrToNum(char a[]);

//分数转化为等待时间
int scoreToWait();

//根据消掉的行数加分
void addScore(int line);

int getRightBlankLine(int blockType, int blockDir);

//得到方块的底部空行
int getBottomBlankLine(int blockType, int blockDir);
