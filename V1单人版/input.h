#ifndef _INPUT_H_
#define _INPUT_H_

/*一些按键，随便定义一些很大的值，防止冲突*/
#define CMD_LEFT     0X123401 /*左*/
#define CMD_RIGHT    0X123402 /*右*/
#define CMD_DOWN     0X123403 /*下*/
#define CMD_UP       0X123404 /*上*/
#define CMD_SPACE    0X123405 /*空格*/
#define CMD_OTHER    0X123406

#include"interface.h"

int waitInput(int *waittime);

#endif

