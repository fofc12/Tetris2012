#include"const.h"
extern Player g_player[];

//clock_t start,end=0;

void getCmd(int *cmd)
{

    int i, c = 0;

    static Timer timer[TOTAL_PLAYER+1];
    for(i = 1; i <= TOTAL_PLAYER; i++)
    {
        timer[i].passedTime = (timer[i].nowTime = clock()) - timer[i].preTime;
        timer[i].valid = ((timer[i].passedTime / (CLOCKS_PER_SEC / 1000)) >= VALID_CMD_DELAY);
        timer[i].upValid = ((timer[i].passedTime / (CLOCKS_PER_SEC / 1000)) >= VALID_CMD_UP_DELAY);
    }


    if (GetAsyncKeyState('A') & 0x8000 && timer[1].valid)
    {
        c |= CMD_LEFT;
        timer[1].preTime = timer[1].nowTime;
    }
    if (GetAsyncKeyState('D') & 0x8000 && timer[1].valid)
    {
        c |= CMD_RIGHT;
        timer[1].preTime = timer[1].nowTime;
    }
    if (GetAsyncKeyState('W') & 0x8000 && timer[1].upValid)
    {
        c |= CMD_UP;    //up
        timer[1].preTime = timer[1].nowTime;
    }
    if (GetAsyncKeyState('S') & 0x8000 && timer[1].valid)
    {
        c |= CMD_DOWN;
        timer[1].preTime = timer[1].nowTime;
    }


    if (GetAsyncKeyState(VK_LEFT) & 0x8000 && timer[2].valid  )
    {
        c |= CMD_LEFT2;
        timer[2].preTime = timer[2].nowTime;
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && timer[2].valid)
    {
        c |= CMD_RIGHT2;
        timer[2].preTime = timer[2].nowTime;
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000 && timer[2].upValid)
    {
        c |= CMD_UP2;    //up
        timer[2].preTime = timer[2].nowTime;
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000 && timer[2].valid)
    {
        c |= CMD_DOWN2;
        timer[2].preTime = timer[2].nowTime;
    }

    if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)	c |= CMD_ZOOMIN;
    if (GetAsyncKeyState(VK_LCONTROL) & 0x8000)	c |= CMD_ZOOMOUT;
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)	c |= CMD_QUIT;

    *cmd = c;
    Sleep(GET_CMD_DELAY);

    // return players;
}

// 分发控制命令
bool DispatchCommand(int playerNum, int _cmd)
{
    bool success = true;

    if(playerNum == 1)
    {
        setorigin(g_player[1].area.areaPoint.x, g_player[1].area.areaPoint.y);
        if (_cmd & CMD_DOWN)		success = dropNowBlk(1); //drop一定要先做
        if (_cmd & CMD_UP)			OnUp(1);
        if (_cmd & CMD_LEFT )		OnLeft(1);
        if (_cmd & CMD_RIGHT )		OnRight(1);
    }

    if(playerNum == 2)
    {
        setorigin(g_player[2].area.areaPoint.x, g_player[2].area.areaPoint.y);
        if (_cmd & CMD_DOWN2)		success = dropNowBlk(2);
        if (_cmd & CMD_UP2)			OnUp(2);
        if (_cmd & CMD_LEFT2)		OnLeft(2);
        if (_cmd & CMD_RIGHT2)		OnRight(2);
    }
    //	if (_cmd & CMD_ZOOMIN)		OnZoomIn();
    //	if (_cmd & CMD_ZOOMOUT)		OnZoomOut();

    return success;
}