// 程序名称：同时检测多个按键及平滑按键输入的范例
// 编译环境：Visual C++ 6.0 / 2010，EasyX 惊蛰版
//
#include <graphics.h>

/////////////////////////////////////////////
// 定义常量、枚举量、结构体、全局变量
/////////////////////////////////////////////

#define	CMD_UP			1
#define	CMD_DOWN		2
#define	CMD_LEFT		4
#define	CMD_RIGHT		8
#define	CMD_ZOOMIN		16
#define	CMD_ZOOMOUT		32
#define	CMD_QUIT		64

// 声明圆的坐标和半径
int g_x, g_y, g_r;



/////////////////////////////////////////////
// 函数声明
/////////////////////////////////////////////

void Init();						// 初始化
void Quit();						// 退出
int  GetCommand();					// 获取控制命令
void DispatchCommand(int _cmd);		// 分发控制命令
void OnUp();						// 上移
void OnDown();						// 下移
void OnLeft();						// 左移
void OnRight();						// 右移
void OnZoomIn();					// 放大
void OnZoomOut();					// 缩小



/////////////////////////////////////////////
// 函数定义
/////////////////////////////////////////////

// 主函数
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

// 初始化
void Init()
{
    // 设置绘图屏幕和绘图模式
    initgraph(640, 480);
    setwritemode(R2_XORPEN);

    // 设置圆的初始位置和大小
    g_x = 320;
    g_y = 240;
    g_r = 20;

    // 显示操作说明
    setfont(14, 0, _T("宋体"));
    outtextxy(20, 270, _T("操作说明"));
    outtextxy(20, 290, _T("上：上移"));
    outtextxy(20, 310, _T("下：下移"));
    outtextxy(20, 330, _T("左：左移"));
    outtextxy(20, 350, _T("右：右移"));
    outtextxy(20, 370, _T("左 Shift：放大"));
    outtextxy(20, 390, _T("左 Ctrl：缩小"));
    outtextxy(20, 410, _T("ESC：退出"));
    outtextxy(20, 450, _T("注：可以同时按多个键，但能同时按下的键的数量，受键盘硬件限制"));

    // 画圆
    circle(g_x, g_y, g_r);
}

// 退出
void Quit()
{
    closegraph();
}

// 获取控制命令
/*功能：确定用户当前是否按下了键盘上的一个键 　　
原型：SHORT GetAsyncKeyState(int vKey); 　　short-16bit 16/4=4
参数：nVirtKey指出要检查键的虚键代码。结果的高位指出该键当前是否被按下（是为1，否为0）。 */
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

// 分发控制命令
void DispatchCommand(int _cmd)
{
    if (_cmd & CMD_UP)			OnUp();
    if (_cmd & CMD_DOWN)		OnDown();
    if (_cmd & CMD_LEFT)		OnLeft();
    if (_cmd & CMD_RIGHT)		OnRight();
    if (_cmd & CMD_ZOOMIN)		OnZoomIn();
    if (_cmd & CMD_ZOOMOUT)		OnZoomOut();
}

// 上移
void OnUp()
{
    circle(g_x, g_y, g_r);
    if (g_y <= 0) g_y = 480;
    else g_y -= 2;
    circle(g_x, g_y, g_r);
}

// 下移
void OnDown()
{
    circle(g_x, g_y, g_r);
    if (g_y >= 480) g_y = 0;
    else g_y += 2;
    circle(g_x, g_y, g_r);
}

// 左移
void OnLeft()
{
    circle(g_x, g_y, g_r);
    if (g_x <= 0) g_x = 640;
    else g_x -= 2;
    circle(g_x, g_y, g_r);
}

// 右移
void OnRight()
{
    circle(g_x, g_y, g_r);
    if (g_x >= 640) g_x = 0;
    else g_x += 2;
    circle(g_x, g_y, g_r);
}

// 放大
void OnZoomIn()
{
    circle(g_x, g_y, g_r);
    if (g_r < 100) g_r++;
    circle(g_x, g_y, g_r);
}

// 缩小
void OnZoomOut()
{
    circle(g_x, g_y, g_r);
    if (g_r > 10) g_r--;
    circle(g_x, g_y, g_r);
}