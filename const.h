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

#pragma comment(lib, "WINMM.LIB")
#define BKIMG "data\\xk.jpg"

#define PLAYER1 1

#define TRUE 1
#define FLASE 0

#define TOTAL_PLAYER 2

#define	CMD_UP			1
#define	CMD_DOWN		2
#define	CMD_LEFT		4
#define	CMD_RIGHT		8
#define	CMD_ZOOMIN		16
#define	CMD_ZOOMOUT		32
#define	CMD_QUIT		64


#define	CMD_UP2			128
#define	CMD_DOWN2		256
#define	CMD_LEFT2		512
#define	CMD_RIGHT2		1024

#define	PLAYER1			1
#define	PLAYER2			2

#define LENGTH 640
#define WIDTH 480
#define G_SPACE_X 200
#define G_SPACE_Y 0
#define LFET_LINE 200
#define RIGHT_LINE (LFET_LINE+ROW*BLOCK_SIZE)

#define GAME_WIDTH ROW*BLOCK_SIZE
#define GAME_LENGTH COLUMN*BLOCK_SIZE

#define ROW 10
#define COLUMN 20
#define B_UNIT 4

#define TOTAL_BLOCK 7
#define BLOCK_SIZE 24
#define BLOCK_GAP 2

#define NORMAL 0xfff0
#define PREVIEW 0xfff1
#define CLEAR 0xfff2
#define CANCLE 0xfff3

#define BKCLR WHITE
#define FGCLR WHITE

#define BIRTH_X 4
#define BIRTH_Y -2

#define COLOR_NUM 15

#define L_FONT_LENGTH 80
#define L_FONT_WIDTH (L_FONT_LENGTH/2)
#define L_FONT_TYPE "黑体"
#define S_FONT_LENGTH 16
#define S_FONT_WIDTH (S_FONT_LENGTH/2)
#define S_FONT_TYPE "宋体"

#define GET_CMD_DELAY 0
#define VALID_CMD_DELAY 80
#define VALID_CMD_UP_DELAY 180
#define MIN_DELAY 20
#define INIT_DELAY 800

#define SCORE_NUM 4
#define SCORE_POS_X G_SPACE_X+ROW*BLOCK_SIZE+(G_SPACE_X-SCORE_NUM*L_FONT_WIDTH)/2
#define SCORE_POS_Y WIDTH-L_FONT_LENGTH

#define TIME_UNIT 400.0

typedef struct Point
{
    int x;
    int y;
} Point;

typedef struct Area
{
    Point areaPoint;
    int state[ROW+2][COLUMN+2];//多2作为缓冲区
} Area;

typedef struct Block
{
    Point point;
    int blockType;
    int blockDir;
    COLORREF blockCLR;
    //	Area *pArea;//所属的舞台
} Block;

typedef struct Player
{
    char name[10];
    int score;
    Area area;
    Block preBlk;
    Block nowBlk;
    bool dropped;
    Point preview;

} Player;

//计时器结构体
typedef struct Timer
{
    clock_t preTime;
    clock_t nowTime;
    clock_t passedTime;
    bool valid;
    bool upValid;
} Timer;


extern IMAGE bkImg;
extern swap[4][4];
extern WORD allBlock[TOTAL_BLOCK+1][4];
extern Player g_player[];
extern COLORREF color[COLOR_NUM];


//包含所有头文件
#include"gameProgress.h"
#include"ttCal.h"
#include"ttIn.h"
#include"ttOut.h"
#include"ttStage.h"
#include "ttBlk.h"

#endif