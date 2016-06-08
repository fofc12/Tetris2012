#include <graphics.h>

void main()
{
    initgraph(640, 480);

    setcolor(WHITE);
    setfillstyle(RED);

    // BeginBatchDraw();
    for(int i = 50; i < 600; i++)
    {
        circle(i, 100, 40);
        floodfill(i, 100, WHITE);
        // FlushBatchDraw();
        Sleep(10);
        cleardevice();
    }

    // EndBatchDraw();

    closegraph();
}