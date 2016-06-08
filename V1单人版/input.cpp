#include"input.h"
#include<windows.h>
#include<conio.h>
#include"draw.h"
#include<stdio.h>

//µÈ´ý¼üÅÌÊäÈë
int waitInput(int *waittime)
{
    static starTime = 0;
    int iDelay = *waittime;
    int i = 0;

    while (iDelay > 0)
    {
        iDelay -= 10;

        if((starTime % STAR_SPEED) == 0)
            drawStar();
        drawStageLine();
        starTime++;

        if (kbhit())
        {
            if (224 == ( i = getch())) 
            {
                switch ( i = getch())
                {
					case 72:i = CMD_UP;break;
					case 80:i = CMD_DOWN;break;
					case 75:i = CMD_LEFT; break;
					case 77: i = CMD_RIGHT; break;
					default:i = CMD_OTHER; break;
                }
            }
            break;
        }
        Sleep(WAITKEY_FUNC_DELAY);
    }

    *waittime = iDelay;

    return i;
}