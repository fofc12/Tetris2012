#ifndef _INPUT_H_
#define _INPUT_H_

/*һЩ��������㶨��һЩ�ܴ��ֵ����ֹ��ͻ*/
#define CMD_LEFT     0X123401 /*��*/
#define CMD_RIGHT    0X123402 /*��*/
#define CMD_DOWN     0X123403 /*��*/
#define CMD_UP       0X123404 /*��*/
#define CMD_SPACE    0X123405 /*�ո�*/
#define CMD_OTHER    0X123406

#include"interface.h"

int waitInput(int *waittime);

#endif

