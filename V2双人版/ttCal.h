#pragma once
#include "const.h"

Point createPt(int x, int y);

//�����������
int Rand(int min, int max);

//WORDת��Ϊ����
void WORDToArr(WORD b);

//������������

//ȡλ��
int length(char a[]);

//����
void copy(char x[]);

//������������
void add(char a[], int i);

//������ת��Ϊ��ͨ��
int arrToNum(char a[]);

int getRtBlankLine(int blockType, int blockDir);

int getBtBlankLine(int blockType, int blockDir);


/*
//����ת��Ϊ�ȴ�ʱ��
int scoreToWait();

//���������������ӷ�
void addScore(int line);

int getRightBlankLine(int blockType, int blockDir);

//�õ�����ĵײ�����
int getBottomBlankLine(int blockType, int blockDir);



bool noBlkOnScreen(Player player);*/