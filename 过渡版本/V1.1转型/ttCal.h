#pragma once
#include "const.h"

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

//����ת��Ϊ�ȴ�ʱ��
int scoreToWait();

//���������������ӷ�
void addScore(int line);

int getRightBlankLine(int blockType, int blockDir);

//�õ�����ĵײ�����
int getBottomBlankLine(int blockType, int blockDir);
