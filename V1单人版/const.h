#ifndef _CONST_H_
#define _CONST_H_

#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<string.h>

//基本布尔值
#define TRUE 1
#define FLASE 0

//前景、背景色
#define BKCLR BLACK
#define FGCLR WHITE
//颜色数组中颜色的个数
#define COLOR_NUM 15


//延时逻辑
#define STAR_SPEED 3//背景的速度（数值越大背景越慢）
#define WAITKEY_FUNC_DELAY 3
#define MIN_DELAY 50
#define INIT_DELAY 850


//大小两种字体
#define L_FONT_LENGTH 80
#define L_FONT_WIDTH (L_FONT_LENGTH/2)
#define L_FONT_TYPE "黑体"
#define S_FONT_LENGTH 16
#define S_FONT_WIDTH (S_FONT_LENGTH/2)
#define S_FONT_TYPE "宋体"

//绘图模式
#define NORMAL 0xfff0
#define PREVIEW 0xfff1
#define CLEAR 0xfff2
#define CANCLE 0xfff3

//屏幕的划分
#define LENGTH 640
#define WIDTH 480
#define G_SPACE_X 200
#define G_SPACE_Y 0
#define LFET_LINE 200
#define RIGHT_LINE (LFET_LINE+ROW*BLOCK_SIZE)

//基本方块
#define ROW 10
#define COLUMN 20
#define B_UNIT 4
#define BLOCK_SIZE 24
#define BLOCK_GAP 2

//方块和预览方块的坐标
#define BIRTH_X 4
#define BIRTH_Y -4
#define PREVIEW_X 14
#define PREVIEW_Y 3

//分数相关
#define SCORE_NUM 4
#define SCORE_POS_X G_SPACE_X+ROW*BLOCK_SIZE+(G_SPACE_X-SCORE_NUM*L_FONT_WIDTH)/2
#define SCORE_POS_Y WIDTH-L_FONT_LENGTH


//表示方块的结构体
typedef struct Block
{
    int x;
    int y;
    int blockType;
    int blockDir;
    int blockCLR;
} Block;


extern Block EMPTY_BLOCK;
extern WORD allBlock[7][4];
extern stage[11][21];
extern swap[4][4];
extern COLORREF color[];
extern char score[];

#endif