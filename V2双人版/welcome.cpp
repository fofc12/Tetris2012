#include"const.h"
#include"welcome.h"


int base[BASE_SIZE/2][BASE_SIZE] =
{
    1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
    1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
    1, 0, 0, 1, 0, 1, 1, 1, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

WBlock wBlk[3] =
{
    {1, 1, {1, 0, 1, 0, 1, 1}, LIGHTRED},
    {4, 1, {1, 0, 1, 1, 1, 0}, LIGHTGREEN},
    {7, 1, {1, 0, 1, 1, 0, 1}, YELLOW},

};


int main()
{

    int i, nWBlk = 0, choice = -1;
    initWel();

    while(1)
    {
		loadimage(NULL, BKIMG, LENGTH, WIDTH);
        printTetris();

        moveto(G_SPACE_X, 0);
        lineto(G_SPACE_X, WIDTH);

        showBase();

        showTip();

        for(i = 0; i < 3; i++)
            showWBlk(i);

        if(choice >= 0)
        {
            endWel();
            if(choice == 0 || choice == 1)
            {
                mciSendString("stop data\\game_begin.mp3", NULL, 0, NULL);
                mciSendString("play data\\game_start.mp3 repeat", NULL, 0, NULL);
            }
            switch (choice)
            {
            case 0:
                gameStart(NORMAL);

            case 1:
                gameStart(CLEAR);
            case 2:
                showHelp();
                initWel();
                //			main();
                break;
            };
        }


        if(choice >= 0)
        {
            choice = -1;
            nWBlk = 0;
            continue;
        }
        FlushBatchDraw();
        moveWBlk(&nWBlk);
        for(i = 0; i < 3; i++)
            if(wBlk[i].y == 5)
                choice = i;

        Sleep(10);
        cleardevice();
    }
    return 0;
}


void initWel()
{
    int i;

    initgraph(LENGTH, WIDTH);
//	setcolor(LIGHTBLUE);
	setbkmode(TRANSPARENT);
    BeginBatchDraw();
    //graphdefaults();
    mciSendString("play data\\game_begin.mp3 repeat", NULL, 0, NULL);

    for(i = 0; i < 3; i++)
    {
        wBlk[i].x = 3 * i + 1;
        wBlk[i].y = 1;
    }
}


void endWel()
{
    int i ;

    setcolor(BLACK);
    for(i = 0; i <= WIDTH; i++)
    {
        Sleep(1);
        line(0, i, LENGTH, i);
        FlushBatchDraw();
    }
    EndBatchDraw();
    graphdefaults();
    closegraph();
}

void printTetris()
{
    char str[] = "Tetris";
    int i, strLength = 6;

    setfont(L_FONT_LENGTH, L_FONT_WIDTH, L_FONT_TYPE);	// ��������
    for(i = 0; i < strLength; i++)
        outtextxy((G_SPACE_X - L_FONT_WIDTH) / 2, i * L_FONT_LENGTH, str[i]);
}


int addOne(int num, int flag)
{

    if(flag == 1)
    {
        num++;
        if(num < 0 || num > 2)num = 0;
    }
    if(flag == -1)
    {
        num--;
        if(num < 0 || num > 2)num = 2;
    }

    return num;
}

void moveWBlk(int *p)
{
    int i;
    int wBlkNum = *p;
    i = getch();

    switch (i)
    {
    case 'q':
        gameExit();
        //  case 72:
    case 'w':

        wBlk[wBlkNum].y--;
        wBlk[wBlkNum].y += (wBlk[wBlkNum].y < 0);
        break;
        //   case 80:
    case 's':
        wBlk[wBlkNum].y++;
        wBlk[wBlkNum].y -= (wBlk[wBlkNum].y > BASE_SIZE / 2);
        break;
        //   case 75:
    case 'a':
        wBlk[wBlkNum].x--;
        wBlk[wBlkNum].x += (wBlk[wBlkNum].x < 0);

        break;
        //   case 77:
    case 'd':
        wBlk[wBlkNum].x++;
        wBlk[wBlkNum].x -= (wBlk[wBlkNum].x > BASE_SIZE - 1);
        break;
    }
    //x����
    wBlk[wBlkNum].x += ((wBlk[wBlkNum].x == (wBlkNum * 3) && wBlk[wBlkNum].y > 2) - (wBlk[wBlkNum].x == (wBlkNum * 3 + 2) && wBlk[wBlkNum].y > 2));


    if(wBlk[wBlkNum].x == wBlk[addOne(wBlkNum, 1)].x - 1) //���ƺ��غϣ��˻ز�ת�ƿ���Ȩ
    {
        wBlk[wBlkNum].x--	;
        *p = addOne(*p, 1);
    }
    else if(wBlk[wBlkNum].x == wBlk[addOne(wBlkNum, -1)].x + 1)
    {
        wBlk[wBlkNum].x++;
        *p = addOne(*p, -1);
    }
    else *p = wBlkNum;

}

void drawBlkxy(int x, int y)
{
    int X = x * WBLK_SIZE;
    int Y = y * WBLK_SIZE;

    bar3d(X, Y, X + WBLK_SIZE - WBLK_DEPTH, Y + WBLK_SIZE - WBLK_DEPTH, WBLK_DEPTH, true);
}

void showBase()
{
    setorigin(G_SPACE_X, G_SPACE_Y);
    setfillstyle(BLUE, SOLID_FILL);
    int i, j;

    for(i = 0; i < BASE_SIZE; i++)
        for(j = 0; j < BASE_SIZE / 2; j++)
            if(base[j][i])drawBlkxy(i, j + 5);


    setorigin(0, 0);
}

void showWBlk(int num)
{
    setorigin(G_SPACE_X + wBlk[num].x * WBLK_SIZE, G_SPACE_Y + wBlk[num].y * WBLK_SIZE);
    setfillstyle(wBlk[num].blockCLR, INTERLEAVE_FILL);

    int i, j;

    for(i = 0; i < 2; i++)
        for(j = 0; j < 3; j++)
            if(wBlk[num].type[j][i] == 1)drawBlkxy(i, j);

    setorigin(0, 0);
}

void showTip()
{
    //setorigin(0,0);
    moveto(G_SPACE_X + 1, WIDTH - WBLK_SIZE);
    //	setcolor(RED);


    setfont(WBLK_SIZE, WBLK_SIZE / 2, "����");	// ��������
    outtext("  ����  �Ծ�  ����  ");

    //	 FlushBatchDraw();
    //	setorigin(0,0);
}

void showHelp()
{
    printf("������Ϣ:\n\n"


           "��һ����Ϸ����\n"
           "�տ�ʼ������wasd�ƶ�չʾ���飬���Ӧ�Ŀ�ȱ�����벻ͬ��ѡ��Ҳ���԰�Q�˳���\n\n"
           "��������Ϸ����\n"
           "1P:WASD\n"
           "2P:��������\n\n"
           "��������Ϸ����\n"
           "	���䣺�������µ��ٶ�����һ����ҵĵ÷־�����\n"
           "	һ�������ȵ�������һ�����ʤ����\n"
           "	�Ծ����������µ��ٶ���ʱ�������\n"
           "	һ�������ȵ�100����ʤ����\n"
           "	һ�����鵽����һ�����Ҳʤ��.\n"
           "	���ڵ÷֣���ȥ��һ�е�����ж���÷֣�\n"
           "	����ģʽ�£�һ���÷ָպ���ʮ����һ����һ�С�\n\n"

           "���ģ���������\n"
           "����˹����(˫�˰�)V1.2\n"
           "������Ч���ı���easyXʾ��������Ч���������硣\n"

           "	**\n"
           "	 QQ2********\n"
           "	��************\n"
           "	2012.5\n\n"




          );

    getch();
    //	Sleep(5000);
    getch();
    wBlk[2].y--;

}