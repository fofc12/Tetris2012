#include"const.h"

//clock_t start,end=0;

int getCmd(int *cmd)
{
    static clock_t timer = 0;
    clock_t nowTime = 0, passedTime = 0;
    int playerNum = 1;
    int valid = FALSE, upValid = FALSE, c = 0;

    passedTime = (nowTime = clock()) - timer;
    valid = ((passedTime / (CLOCKS_PER_SEC / 1000)) >= VALID_CMD_DELAY);
    upValid = ((passedTime / (CLOCKS_PER_SEC / 1000)) >= VALID_CMD_UP_DELAY);



    if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && valid)
    {
        c |= CMD_LEFT;
        timer = nowTime;
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && valid)
    {
        c |= CMD_RIGHT;
        timer = nowTime;
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000 && upValid)
    {
        c |= CMD_UP;
        timer = nowTime;
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000 && valid)
    {
        c |= CMD_DOWN;
        timer = nowTime;
    }
    if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)	c |= CMD_ZOOMIN;
    if (GetAsyncKeyState(VK_LCONTROL) & 0x8000)	c |= CMD_ZOOMOUT;
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)	c |= CMD_QUIT;

    *cmd = c;
    Sleep(GET_CMD_DELAY);

    return playerNum;
}

// ·Ö·¢¿ØÖÆÃüÁî
/*void DispatchCommand(int _cmd)
{
	if (_cmd & CMD_UP)			OnUp();
	if (_cmd & CMD_DOWN)		OnDown();
	if (_cmd & CMD_LEFT)		OnLeft();
	if (_cmd & CMD_RIGHT)		OnRight();
	if (_cmd & CMD_ZOOMIN)		OnZoomIn();
	if (_cmd & CMD_ZOOMOUT)		OnZoomOut();
}*/