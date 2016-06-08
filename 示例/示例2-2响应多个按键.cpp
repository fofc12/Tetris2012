// �������ƣ�ͬʱ�����������ƽ����������ķ���
// ���뻷����Visual C++ 6.0 / 2010��EasyX ���ݰ�
//
#include <graphics.h>

/////////////////////////////////////////////
// ���峣����ö�������ṹ�塢ȫ�ֱ���
/////////////////////////////////////////////

#define	CMD_UP			1
#define	CMD_DOWN		2
#define	CMD_LEFT		4
#define	CMD_RIGHT		8
#define	CMD_ZOOMIN		16
#define	CMD_ZOOMOUT		32
#define	CMD_QUIT		64

// ����Բ������Ͱ뾶
int g_x, g_y, g_r;



/////////////////////////////////////////////
// ��������
/////////////////////////////////////////////

void Init();						// ��ʼ��
void Quit();						// �˳�
int  GetCommand();					// ��ȡ��������
void DispatchCommand(int _cmd);		// �ַ���������
void OnUp();						// ����
void OnDown();						// ����
void OnLeft();						// ����
void OnRight();						// ����
void OnZoomIn();					// �Ŵ�
void OnZoomOut();					// ��С



/////////////////////////////////////////////
// ��������
/////////////////////////////////////////////

// ������
void main()
{
    Init();

    int c;
    do
    {
        c = GetCommand();
        DispatchCommand(c);
        Sleep(10);
    }
    while(!(c & CMD_QUIT));

    Quit();
}

// ��ʼ��
void Init()
{
    // ���û�ͼ��Ļ�ͻ�ͼģʽ
    initgraph(640, 480);
    setwritemode(R2_XORPEN);

    // ����Բ�ĳ�ʼλ�úʹ�С
    g_x = 320;
    g_y = 240;
    g_r = 20;

    // ��ʾ����˵��
    setfont(14, 0, _T("����"));
    outtextxy(20, 270, _T("����˵��"));
    outtextxy(20, 290, _T("�ϣ�����"));
    outtextxy(20, 310, _T("�£�����"));
    outtextxy(20, 330, _T("������"));
    outtextxy(20, 350, _T("�ң�����"));
    outtextxy(20, 370, _T("�� Shift���Ŵ�"));
    outtextxy(20, 390, _T("�� Ctrl����С"));
    outtextxy(20, 410, _T("ESC���˳�"));
    outtextxy(20, 450, _T("ע������ͬʱ�������������ͬʱ���µļ����������ܼ���Ӳ������"));

    // ��Բ
    circle(g_x, g_y, g_r);
}

// �˳�
void Quit()
{
    closegraph();
}

// ��ȡ��������
/*���ܣ�ȷ���û���ǰ�Ƿ����˼����ϵ�һ���� ����
ԭ�ͣ�SHORT GetAsyncKeyState(int vKey); ����short-16bit 16/4=4
������nVirtKeyָ��Ҫ������������롣����ĸ�λָ���ü���ǰ�Ƿ񱻰��£���Ϊ1����Ϊ0���� */
int GetCommand()
{
    int c = 0;

    if (GetAsyncKeyState(VK_LEFT) & 0x8000)		c |= CMD_LEFT;
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)	c |= CMD_RIGHT;
    if (GetAsyncKeyState(VK_UP) & 0x8000)		c |= CMD_UP;
    if (GetAsyncKeyState(VK_DOWN) & 0x8000)		c |= CMD_DOWN;
    if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)	c |= CMD_ZOOMIN;
    if (GetAsyncKeyState(VK_LCONTROL) & 0x8000)	c |= CMD_ZOOMOUT;
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)	c |= CMD_QUIT;

    return c;
}

// �ַ���������
void DispatchCommand(int _cmd)
{
    if (_cmd & CMD_UP)			OnUp();
    if (_cmd & CMD_DOWN)		OnDown();
    if (_cmd & CMD_LEFT)		OnLeft();
    if (_cmd & CMD_RIGHT)		OnRight();
    if (_cmd & CMD_ZOOMIN)		OnZoomIn();
    if (_cmd & CMD_ZOOMOUT)		OnZoomOut();
}

// ����
void OnUp()
{
    circle(g_x, g_y, g_r);
    if (g_y <= 0) g_y = 480;
    else g_y -= 2;
    circle(g_x, g_y, g_r);
}

// ����
void OnDown()
{
    circle(g_x, g_y, g_r);
    if (g_y >= 480) g_y = 0;
    else g_y += 2;
    circle(g_x, g_y, g_r);
}

// ����
void OnLeft()
{
    circle(g_x, g_y, g_r);
    if (g_x <= 0) g_x = 640;
    else g_x -= 2;
    circle(g_x, g_y, g_r);
}

// ����
void OnRight()
{
    circle(g_x, g_y, g_r);
    if (g_x >= 640) g_x = 0;
    else g_x += 2;
    circle(g_x, g_y, g_r);
}

// �Ŵ�
void OnZoomIn()
{
    circle(g_x, g_y, g_r);
    if (g_r < 100) g_r++;
    circle(g_x, g_y, g_r);
}

// ��С
void OnZoomOut()
{
    circle(g_x, g_y, g_r);
    if (g_r > 10) g_r--;
    circle(g_x, g_y, g_r);
}