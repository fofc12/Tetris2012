#include<graphics.h>
#include<conio.h>
#include<stdlib.h>

#define LENGTH 640
#define WIDTH 480
#define G_SPACE_X 200
#define BLOCK_SIZE 24
#define GAP 2
#define BLOCK_NUM_X 10
#define BLOCK_NUM_Y 20

void main()
{
    int i = 1, j = 1;


    initgraph(LENGTH, WIDTH);
    moveto(G_SPACE_X, 0);
    lineto(G_SPACE_X, WIDTH);

    moveto(LENGTH - G_SPACE_X, 0);
    lineto(LENGTH - G_SPACE_X, WIDTH);


    outtextxy(1, 1, "请按WASD");
    for(i = 1; i < 20; i++)
        outtextxy(1, i * 20, "游戏帮助与说明");

    while(1)
    {
        while(!kbhit())
        {
            switch (getch())
            {
            case 'w':
                j -= 1;
                break;
            case 's':
                j += 1;
                break;
            case 'a':
                i -= 1;
                break;
            case 'd':
                i += 1;
                break;
            case 'z':
                i = 1;
                j = 1;
            }

            //	for(i=1;i<=BLOCK_NUM_X;i++)
            //			for(j=1;j<=BLOCK_NUM_Y;j++)
            bar(G_SPACE_X + (i - 1)*BLOCK_SIZE + GAP, (j - 1)*BLOCK_SIZE + GAP, i * BLOCK_SIZE + G_SPACE_X - GAP, j * BLOCK_SIZE - GAP);
        }
    }
    getch();
    closegraph();
}
