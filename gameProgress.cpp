#include"const.h"

IMAGE bkImg;
Player	g_player[TOTAL_PLAYER+1];//1�����
COLORREF color[COLOR_NUM] = {DARKGRAY ,
                             BLUE, LIGHTBLUE,
                             GREEN, LIGHTGREEN,
                             CYAN, LIGHTCYAN,
                             RED, LIGHTRED,
                             MAGENTA, LIGHTMAGENTA,
                             BROWN, YELLOW ,
                             LIGHTGRAY , DARKGRAY
                            };//��ı���ɫ����ĺ�COLOR_NUM
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

void test() {}

void gameStart(int mode)
{

    bool success;//�Ƿ�����ɹ�����ʧ�ܣ���˵������
    int i, j, k, t = 0;
    int cmd = 0;
    int timeLeft[TOTAL_PLAYER+1] = {0, 1000, 1000};
    Block tpBlk[TOTAL_PLAYER+1];

    gameInit();//��ʼ����Ϸ

    while(1)
    {

        for(i = 1; i <= TOTAL_PLAYER; i++)
        {
            t++;//��ʱ������
            setorigin(0, 0); //����ԭ��
            recoverBk(0, g_player[i].preview.y + 4 * BLOCK_SIZE, 160, 30);
            recoverBk(0, 480 - 30, 160, 30); //�ػ�Ԥ����
            printScore(t);//��ʾ�÷�
            drawStageLine();//���Ʊ߽���
            FlushBatchDraw();//ִ�л�ͼ


            if(g_player[i].dropped == true)
            {

                saveState(i, g_player[i].nowBlk);//���淽��Ĵ���״̬


                if(mode == CLEAR && g_player[1+(i==1)].score >= 100)gameOver(i);
                if(reachTop(i))
                {
                    gameOver(i);
                    continue;
                }//�ж���Ϸ����

                k = fullColumn(i);
                if(k > 0)
                {
                    g_player[i].score += k * k;
                    if(mode == NORMAL && g_player[i].score % 10 == 0)newColumn(1 + (i == 1));
                }//�Ʒ�������

                tpBlk[i] = g_player[i].preBlk; //����Ԥ������
                g_player[i].nowBlk = preToNow(g_player[i].preBlk);//previewBlock��Ϊplayer[1].nowBlk
                g_player[i].preBlk = createBlk(); //�����µ�Ԥ������
                refreshBlk(i, tpBlk[i], g_player[i].preBlk, PREVIEW); //�����µ�previewBlock

                g_player[i].dropped = false;


            }


            getCmd(&cmd);//�������
            timeLeft[i] -= 10;
            for  (j = 1; j <= TOTAL_PLAYER; j++)
            {

                tpBlk[j] = g_player[j].nowBlk;

                success = DispatchCommand(j, cmd);
                if(success)refreshBlk(j, tpBlk[j], g_player[j].nowBlk);
                else continue;

            }//��һ����ҵ�ѭ����Ҫͬʱ�����������

            if(timeLeft[i] <= 0)
            {
                if(mode == NORMAL)timeLeft[i] = INIT_DELAY - (int)(2.5 * g_player[1+(i==1)].score);
                else timeLeft[i] = (int)(INIT_DELAY - (t / 1000.0)); //�ٶȹ���
                if(timeLeft[i] < MIN_DELAY)timeLeft[i] = 3 * MIN_DELAY;

                tpBlk[i] = g_player[i].nowBlk;
                if(i == 1)
                    success = DispatchCommand(1, CMD_DOWN);
                else
                    success = DispatchCommand(2, CMD_DOWN2);
                if(success)refreshBlk(i, tpBlk[i], g_player[i].nowBlk);

            }

        }


    }
    getch();
    closegraph();
}

//Ϊ��ҽṹ�帳ֵ
void setPlayer(int playerNum, char *name, int score, Point areaPoint, Block preBlk, bool dropped, Point preview)
{
    int i, j;

    strcpy(g_player[playerNum].name, name);
    g_player[playerNum].score = score;
    g_player[playerNum].area.areaPoint = areaPoint;
    g_player[playerNum].preBlk = preBlk;//������һ������
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

//��Ϸ��ʼ��
void gameInit()
{
    initgraph(LENGTH, WIDTH);
    setcolor(FGCLR);
    setbkcolor(BKCLR);
    setfillstyle(FGCLR, SOLID_FILL);
    BeginBatchDraw();
    setfont(25, 0, "�����п�");
    setbkmode(TRANSPARENT);
    cleardevice();
    loadimage(&bkImg, BKIMG, LENGTH, WIDTH);
    putimage(0, 0, &bkImg);
    srand((unsigned)time(NULL));//��ʼ������
    setPlayer(1, "player1", 0, createPt(160, 0), createBlk(), true, createPt(10, 10));
    setPlayer(2, "player2", 0, createPt(400, 0), createBlk(), true, createPt(10, 240));
    drawStageLine();
}


//��Ϸ����
void gameOver(int playerNum)
{

    mciSendString("play data\\ace.mp3", NULL, 0, NULL);
    setorigin(g_player[playerNum].area.areaPoint.x, g_player[playerNum].area.areaPoint.y);

    char str[] = "GameOver";
    int i, strLength = 8;

    setcolor(RED);
    setfont(L_FONT_LENGTH, L_FONT_WIDTH, L_FONT_TYPE);	// ��������
    for(i = 0; i < strLength / 2; i++)
        outtextxy((GAME_WIDTH - 4 * L_FONT_WIDTH) / 2 + i * L_FONT_WIDTH, (GAME_LENGTH - 3 * L_FONT_LENGTH) / 2, str[i]);

    for(i = strLength / 2; i < strLength; i++)
        outtextxy((GAME_WIDTH - 4 * L_FONT_WIDTH) / 2 + (i - 4)*L_FONT_WIDTH, (GAME_LENGTH - L_FONT_LENGTH) / 2, str[i]);

    if(playerNum == 1)
        playerNum = 2;
    else playerNum = 1;
    setorigin(g_player[playerNum].area.areaPoint.x, g_player[playerNum].area.areaPoint.y);

    strcpy( str, "You Win!");


    setcolor(GREEN);
    setfont(L_FONT_LENGTH, L_FONT_WIDTH, L_FONT_TYPE);	// ��������
    for(i = 0; i < strLength / 2; i++)
        outtextxy((GAME_WIDTH - 4 * L_FONT_WIDTH) / 2 + i * L_FONT_WIDTH, (GAME_LENGTH - 3 * L_FONT_LENGTH) / 2, str[i]);

    for(i = strLength / 2; i < strLength; i++)
        outtextxy((GAME_WIDTH - 4 * L_FONT_WIDTH) / 2 + (i - 4)*L_FONT_WIDTH, (GAME_LENGTH - L_FONT_LENGTH) / 2, str[i]);

    FlushBatchDraw();
    Sleep(10000);
    getch();
    gameExit();
}

//��Ϸ�˳�
void gameExit()
{
    closegraph();
    printf("Byebye!\n" );
    byebye();
    getch();
}