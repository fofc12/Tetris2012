#include<graphics.h>
#include<conio.h>
#include<stdio.h>

#define CMD_LEFT     0X123401 /*左*/
#define CMD_RIGHT    0X123402 /*右*/
#define CMD_DOWN     0X123403 /*下*/
#define CMD_UP       0X123404 /*上*/
#define CMD_SPACE    0X123405 /*空格*/
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
        playerNum = getCmd(&cmd); //等待输入
        if(playerNum != 0) echoCmd(playerNum, cmd);
        cleardevice();
        drawplayer(player[1]);
        drawplayer(player[2]);
        setfont(14, 0, _T("宋体"));
        outtextxy(20, 330, _T("左： a/j"));
        outtextxy(20, 350, _T("右： d/l"));
        outtextxy(20, 370, _T("上： w/i"));
        outtextxy(20, 390, _T("下： s/k"));
        outtextxy(20, 410, _T("ESC：退出"));
        outtextxy(20, 430, _T("说明：用结构化的方法统一操作了两个玩家，但是——"));
        outtextxy(20, 450, _T("用getch来同时操作两个图形失败了，且没有setwritemode，用不断清屏的方法导致闪屏。"));


    }

    closegraph();
}