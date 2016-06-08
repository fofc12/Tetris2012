#ifndef _CONST_H_
#define _CONST_H_

#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<string.h>

//��������ֵ
#define TRUE 1
#define FLASE 0

//ǰ��������ɫ
#define BKCLR BLACK
#define FGCLR WHITE
//��ɫ��������ɫ�ĸ���
#define COLOR_NUM 15


//��ʱ�߼�
#define STAR_SPEED 3//�������ٶȣ���ֵԽ�󱳾�Խ����
#define WAITKEY_FUNC_DELAY 3
#define MIN_DELAY 50
#define INIT_DELAY 850


//��С��������
#define L_FONT_LENGTH 80
#define L_FONT_WIDTH (L_FONT_LENGTH/2)
#define L_FONT_TYPE "����"
#define S_FONT_LENGTH 16
#define S_FONT_WIDTH (S_FONT_LENGTH/2)
#define S_FONT_TYPE "����"

//��ͼģʽ
#define NORMAL 0xfff0
#define PREVIEW 0xfff1
#define CLEAR 0xfff2
#define CANCLE 0xfff3

//��Ļ�Ļ���
#define LENGTH 640
#define WIDTH 480
#define G_SPACE_X 200
#define G_SPACE_Y 0
#define LFET_LINE 200
#define RIGHT_LINE (LFET_LINE+ROW*BLOCK_SIZE)

//��������
#define ROW 10
#define COLUMN 20
#define B_UNIT 4
#define BLOCK_SIZE 24
#define BLOCK_GAP 2

//�����Ԥ�����������
#define BIRTH_X 4
#define BIRTH_Y -4
#define PREVIEW_X 14
#define PREVIEW_Y 3

//�������
#define SCORE_NUM 4
#define SCORE_POS_X G_SPACE_X+ROW*BLOCK_SIZE+(G_SPACE_X-SCORE_NUM*L_FONT_WIDTH)/2
#define SCORE_POS_Y WIDTH-L_FONT_LENGTH


//��ʾ����Ľṹ��
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