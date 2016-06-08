#include"const.h"
//#include"byebye.cpp"


Player	g_player[TOTAL_PLAYER+1];//1个玩家

COLORREF color[COLOR_NUM] = {DARKGRAY ,
                             BLUE, LIGHTBLUE,
                             GREEN, LIGHTGREEN,
                             CYAN, LIGHTCYAN,
                             RED, LIGHTRED,
                             MAGENTA, LIGHTMAGENTA,
                             BROWN, YELLOW ,
                             LIGHTGRAY , DARKGRAY
                            };//如改变颜色还需改宏COLOR_NUM


WORD allBlock[TOTAL_BLOCK+1][4] =
{
    {0x0000, 0x0000, 0x0000, 0x0000},
    {0xf000, 0x8888, 0xf000, 0x8888},
    {0xcc00, 0xcc00, 0xcc00, 0xcc00},
    {0x88c0, 0xe800, 0xc440, 0x2e00},
    {0x44c0, 0xe200, 0xc880, 0x8e00},
    {0x4e00, 0xe400, 0x4c40, 0x8c80},
    {0x8c40, 0x6c00, 0x8c40, 0x6c00},
    {0x4c80, 0xc600, 0x4c80, 0xc600}
};

int swap[4][4];

void byebye();

void test()
{

}

void main(int mode)
{

    mode = NORMAL;
    bool success;
    int i, j, k, t = 0;
    int cmd = 0;
    int timeLeft[TOTAL_PLAYER+1] = {0, 1000, 1000};
    Block tpBlk[TOTAL_PLAYER+1];

    gameInit();

    while(1)
    {

        for(i = 1; i <= TOTAL_PLAYER; i++)
        {

            t++;
            printScore(t);
            drawStageLine();
            FlushBatchDraw();

            setorigin(g_player[i].area.areaPoint.x, g_player[i].area.areaPoint.y);

            if(g_player[i].dropped == true)
            {

                saveState(i, g_player[i].nowBlk);
                setorigin(g_player[i].area.areaPoint.x, g_player[i].area.areaPoint.y);
                drawStage(i);

                if(mode == CLEAR && g_player[1+(i==1)].score >= 100)
                    gameOver(i);
                if(reachTop(i))
                {
                    gameOver(i);
                    continue;
                }

                k = fullColumn(i);
                if(k > 0)
                {
                    g_player[i].score += k * k;
                    if(mode == NORMAL && g_player[i].score % 10 == 0)newColumn(1 + (i == 1));
                }

                setorigin(g_player[i].preview.x, g_player[i].preview.y);
                tpBlk[i] = g_player[i].preBlk; //备份预览方块
                g_player[i].nowBlk = preToNow(g_player[i].preBlk);//previewBlock变为player[1].nowBlk
                g_player[i].preBlk = createBlk(); //产生新的预览方块
                refreshBlk(tpBlk[i], g_player[i].preBlk);//绘制新的previewBlock

                g_player[i].dropped = false;
                setorigin(g_player[i].area.areaPoint.x, g_player[i].area.areaPoint.y);

            }

            //	drawBlk(g_player[i].nowBlk);




            //if(pauseState==TRUE)printPause();
            //if(noBlkOnScreen(g_player[i]))
            //		timeLeft=0;//消除方块没有出现在舞台上时的等待

            getCmd(&cmd);
            timeLeft[i] -= 10;
            //        if(cmd != 0 && pauseState==FALSE)
            //	if(j==i)
            for  (j = 1; j <= TOTAL_PLAYER; j++)
            {
                //	setorigin(g_player[j].area.areaPoint.x,g_player[j].area.areaPoint.y);
                tpBlk[j] = g_player[j].nowBlk;

                success = DispatchCommand(j, cmd);
                if(success)refreshBlk(tpBlk[j], g_player[j].nowBlk);
                else continue;

                //		setorigin(g_player[i].area.areaPoint.x,g_player[i].area.areaPoint.y);
            }

            if(timeLeft[i] <= 0)
            {
                if(mode == NORMAL)timeLeft[i] = INIT_DELAY;
                //-(int)(2.5*g_player[1+(i==1)].score);
                else timeLeft[i] = (int)(INIT_DELAY - (t / 1000.0)); //速度规则
                if(timeLeft[i] < MIN_DELAY)timeLeft[i] = 3 * MIN_DELAY;

                tpBlk[i] = g_player[i].nowBlk;
                if(i == 1)
                    success = DispatchCommand(1, CMD_DOWN);
                else
                    success = DispatchCommand(2, CMD_DOWN2);
                if(success)refreshBlk(tpBlk[i], g_player[i].nowBlk);
                //				else continue;
            }

        }


    }
    getch();
    closegraph();
}

void setPlayer(int playerNum, char *name, int score, Point areaPoint, Block preBlk, bool dropped, Point preview)
{
    int i, j;

    strcpy(g_player[playerNum].name, name);
    g_player[playerNum].score = score;
    g_player[playerNum].area.areaPoint = areaPoint;
    g_player[playerNum].preBlk = preBlk;//产生第一个方块
    g_player[playerNum].nowBlk.point = createPt(0, 0);
    g_player[playerNum].nowBlk.blockCLR = 0;
    g_player[playerNum].nowBlk.blockDir = 0;
    g_player[playerNum].nowBlk.blockType = 0;
    g_player[playerNum].dropped = dropped;
    g_player[playerNum].preview = preview;

    for(i = 0; i < ROW + 2; i++)
        for(j = 0; j < COLUMN + 2; j++)
            g_player[playerNum].area.state[i][j] = 0;
}

void gameInit()
{
    initgraph(LENGTH, WIDTH);
    setcolor(FGCLR);
    setbkcolor(BKCLR);
    setfillstyle(FGCLR, SOLID_FILL);
    //setbkmode(TRANSPARENT);
    cleardevice();
    //	loadimage(NULL, "bliss.bmp");
    srand((unsigned)time(NULL));//初始化种子
    setPlayer(1, "player1", 0, createPt(160, 0), createBlk(), true, createPt(10, 10));
    setPlayer(2, "player2", 0, createPt(400, 0), createBlk(), true, createPt(10, 240));
    drawStageLine();
}

void gameExit()
{

    closegraph();
    printf(
        "俄罗斯方块双人版(测试2)\n"
        "Made by GoodLuck\n"
        "QQ:2642223233\n"
        "O(∩_∩)O~\n"
        "Thanks for playing!\n"
        "Byebye!\n"
    );
    //byebye();
    getch();
}

void gameOver(int playerNum)
{

    mciSendString("play data\\ace.mp3", NULL, 0, NULL);
    setorigin(g_player[playerNum].area.areaPoint.x, g_player[playerNum].area.areaPoint.y);

    char str[] = "GameOver";
    int i, strLength = 8;

    setcolor(RED);
    setfont(L_FONT_LENGTH, L_FONT_WIDTH, L_FONT_TYPE);	// 设置字体
    for(i = 0; i < strLength / 2; i++)
        //outtextxy((G_SPACE_X-L_FONT_WIDTH)/2,i*L_FONT_LENGTH,str[i]);
        outtextxy((GAME_WIDTH - 4 * L_FONT_WIDTH) / 2 + i * L_FONT_WIDTH, (GAME_LENGTH - 3 * L_FONT_LENGTH) / 2, str[i]);

    for(i = strLength / 2; i < strLength; i++)
        //outtextxy((G_SPACE_X-L_FONT_WIDTH)/2,i*L_FONT_LENGTH,str[i]);
        outtextxy((GAME_WIDTH - 4 * L_FONT_WIDTH) / 2 + (i - 4)*L_FONT_WIDTH, (GAME_LENGTH - L_FONT_LENGTH) / 2, str[i]);

    if(playerNum == 1)
        playerNum = 2;
    else playerNum = 1;
    setorigin(g_player[playerNum].area.areaPoint.x, g_player[playerNum].area.areaPoint.y);

    strcpy( str, "You Win!");
    //  int i, strLength = 8;

    setcolor(GREEN);
    setfont(L_FONT_LENGTH, L_FONT_WIDTH, L_FONT_TYPE);	// 设置字体
    for(i = 0; i < strLength / 2; i++)
        //outtextxy((G_SPACE_X-L_FONT_WIDTH)/2,i*L_FONT_LENGTH,str[i]);
        outtextxy((GAME_WIDTH - 4 * L_FONT_WIDTH) / 2 + i * L_FONT_WIDTH, (GAME_LENGTH - 3 * L_FONT_LENGTH) / 2, str[i]);

    for(i = strLength / 2; i < strLength; i++)
        //outtextxy((G_SPACE_X-L_FONT_WIDTH)/2,i*L_FONT_LENGTH,str[i]);
        outtextxy((GAME_WIDTH - 4 * L_FONT_WIDTH) / 2 + (i - 4)*L_FONT_WIDTH, (GAME_LENGTH - L_FONT_LENGTH) / 2, str[i]);

    FlushBatchDraw();
    Sleep(10000);
    getch();
    gameExit();
}

