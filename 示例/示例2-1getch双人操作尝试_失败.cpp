#include<graphics.h>
#include<conio.h>
#include<stdio.h>

#define CMD_LEFT     0X123401 /*��*/
#define CMD_RIGHT    0X123402 /*��*/
#define CMD_DOWN     0X123403 /*��*/
#define CMD_UP       0X123404 /*��*/
#define CMD_SPACE    0X123405 /*�ո�*/
#define CMD_OTHER    0X123406
#define CMD_NONE	0x123407


typedef struct Player
{
    int x;
    int y;

    char type;
} Player;

Player player[3] = {{0, 0, 0}, {1, 1, 'b'}, {1, 1, 'c'}};
void init()
{
    initgraph(640, 480);


}

void drawplayer(Player player)
{
    if(player.type == 'b')
        bar(player.x, player.y, player.x + 10, player.y + 10);
    else
    {
        circle(player.x, player.y, 10);
    }
}

int getCmd(int *pcmd)
{
    int playerNum = 0, cmd = CMD_NONE;

    //  while (*ptimeLeft > 0)
    // {
    //      *ptimeLeft -= 10;


    if (kbhit())
    {

        *pcmd = getch();

        if('i' == *pcmd || 'j' == *pcmd || 'k' == *pcmd || 'l' == *pcmd)
        {
            playerNum = 2;
            switch (*pcmd)
            {
            case 'i':

                *pcmd = CMD_UP;
                break;
            case 'k':
                *pcmd = CMD_DOWN;
                break;
            case 'j':
                *pcmd = CMD_LEFT;
                break;
            case 'l':
                *pcmd = CMD_RIGHT;
                break;
            default:
                *pcmd = CMD_OTHER;
                break;
            }
        }

        else if('w' == *pcmd || 's' == *pcmd || 'a' == *pcmd || 'd' == *pcmd)
        {
            playerNum = 1;
            switch (*pcmd)
            {
            case 'w':

                *pcmd = CMD_UP;
                break;
            case 's':
                *pcmd = CMD_DOWN;
                break;
            case 'a':
                *pcmd = CMD_LEFT;
                break;
            case 'd':
                *pcmd = CMD_RIGHT;
                break;
            default:
                *pcmd = CMD_OTHER;
                break;
            }


            //		   }
            //        break;
        }
        Sleep(10);
    }

    fflush(stdin);

    //    *waittime = iDelay;

    return playerNum;
}

void echoCmd(int playerNum, int cmd)
{
    switch (cmd)
    {
    case  CMD_UP:
        player[playerNum].y -= 10;
        break;
    case CMD_DOWN:
        player[playerNum].y += 10;
        break;
    case  CMD_LEFT:
        player[playerNum].x -= 10;
        break;
    case  CMD_RIGHT:
        player[playerNum].x += 10;
        break;
    default:
        break;
    }

}

int main()
{
    int playerNum, cmd = 0;

    init();


    while(1)
    {
        playerNum = getCmd(&cmd); //�ȴ�����
        if(playerNum != 0) echoCmd(playerNum, cmd);
        cleardevice();
        drawplayer(player[1]);
        drawplayer(player[2]);
        setfont(14, 0, _T("����"));
        outtextxy(20, 330, _T("�� a/j"));
        outtextxy(20, 350, _T("�ң� d/l"));
        outtextxy(20, 370, _T("�ϣ� w/i"));
        outtextxy(20, 390, _T("�£� s/k"));
        outtextxy(20, 410, _T("ESC���˳�"));
        outtextxy(20, 430, _T("˵�����ýṹ���ķ���ͳһ������������ң����ǡ���"));
        outtextxy(20, 450, _T("��getch��ͬʱ��������ͼ��ʧ���ˣ���û��setwritemode���ò��������ķ�������������"));


    }

    closegraph();
}