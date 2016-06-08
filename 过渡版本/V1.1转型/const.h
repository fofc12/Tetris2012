#ifndef _CONST_H_
#define _CONST_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<conio.h>
#include<windows.h>
#include<graphics.h>

#include<time.h>
#include<math.h>


#define TRUE 1
#define FLASE 0

#define	CMD_UP			1
#define	CMD_DOWN		2
#define	CMD_LEFT		4
#define	CMD_RIGHT		8
#define	CMD_ZOOMIN		16
#define	CMD_ZOOMOUT		32
#define	CMD_QUIT		64

#define LENGTH 640
#define WIDTH 480
#define G_SPACE_X 200
#define G_SPACE_Y 0
#define LFET_LINE 200
#define RIGHT_LINE (LFET_LINE+ROW*BLOCK_SIZE)

#define ROW 10
#define COLUMN 20
#define B_UNIT 4

#define BLOCK_SIZE 24
#define BLOCK_GAP 2

#define NORMAL 0xfff0
#define PREVIEW 0xfff1
#define CLEAR 0xfff2
#define CANCLE 0xfff3

#define BKCLR BLACK
#define FGCLR WHITE

#define BIRTH_X 4
#define BIRTH_Y -3
#define PREVIEW_X 14
#define PREVIEW_Y 3

#define COLOR_NUM 15

#define L_FONT_LENGTH 80
#define L_FONT_WIDTH (L_FONT_LENGTH/2)
#define L_FONT_TYPE "黑体"
#define S_FONT_LENGTH 16
#define S_FONT_WIDTH (S_FONT_LENGTH/2)
#define S_FONT_TYPE "宋体"

#define GET_CMD_DELAY 10
#define VALID_CMD_DELAY 50
#define VALID_CMD_UP_DELAY 150
#define MIN_DELAY 50
#define INIT_DELAY 1000

#define SCORE_NUM 4
#define SCORE_POS_X G_SPACE_X+ROW*BLOCK_SIZE+(G_SPACE_X-SCORE_NUM*L_FONT_WIDTH)/2
#define SCORE_POS_Y WIDTH-L_FONT_LENGTH


typedef struct Block
{
    int x;
    int y;
    int blockType;
    int blockDir;
    int blockCLR;
} Block;


//包含所有头文件
#include"ttCal.h"
#include"ttIn.h"
#include"ttOut.h"
#include"ttOther.h"
#include"ttStage.h"
#include "ttBlk.h"

#endif