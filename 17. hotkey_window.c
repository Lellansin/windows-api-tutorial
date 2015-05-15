#include <Windows.h>

void echo(LPSTR str)
{
	MessageBox(NULL, str, TEXT("提示"), MB_OK);
}

// 5. 窗口过程处理
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{	
	CHAR text[50];
	switch(msg)
	{
	// 窗口创建消息
	case WM_CREATE:
		RegisterHotKey(
			hwnd,	// 注册快捷键的窗口句柄
			1,		// 热键标识符避免热键冲突
			MOD_CONTROL | MOD_NOREPEAT, // Ctrl 键  No Repeat 不重复发送
			'A'		// A
			); // Ctrl + A
		RegisterHotKey(hwnd, 2, MOD_CONTROL | MOD_NOREPEAT,'B');// Ctrl + B
		RegisterHotKey(hwnd, 3, MOD_ALT | MOD_NOREPEAT,'A');	// Alt + A
		RegisterHotKey(hwnd, 4, MOD_ALT | MOD_NOREPEAT,'B');	// Alt + B
		RegisterHotKey(hwnd, 5, MOD_NOREPEAT,'S');				// 直接按 S
	break;

	// 快捷键消息
	case WM_HOTKEY:
		/***
		 * wParam 保存注册时定义的热键标识符
		 * lParam 高位存键(如A的值)，低位存复合键的值(如Ctrl的值)
		 */
		//wsprintf(text, "wParam : %p  lParam : %p", wParam, lParam);
		//echo(text);

		switch(LOWORD(lParam)) // 获取低16位的值 
		{
		// 当用户先按 ctrl
		case MOD_CONTROL:

			switch(HIWORD(lParam)) // 获取高16位的值
			{
				case 'A':
					echo("Ctrl + A 被按下！");
				break;
				case 'B':
					echo("Ctrl + B 被按下！");
				break;
			}

		break;

		// 当用户先按 Alt
		case MOD_ALT:

			switch(HIWORD(lParam)) // 获取高16位的值
			{
				case 'A':
					echo("Alt + A 被按下！");
				break;
				case 'B':
					echo("Alt + B 被按下！");
				break;
			}

		break;

		// 没有组合键
		case 0: 

			switch(HIWORD(lParam)) // 获取高16位的值
			{
				case 'S':
					echo("S 被按下");
				break;
			}

		break;		

		}		
	break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;
	char text[30];

	const char szClassName[] = "myWindowClass";

	// 1. 设置注册窗口结构体
	wc.cbSize        = sizeof(WNDCLASSEX);				// 注册窗口结构体的大小
	wc.style         = 0;								// 窗口的样式
	wc.lpfnWndProc   = WndProc;							// 指向窗口处理过程的函数指针
	wc.cbClsExtra    = 0;								// 指定紧跟在窗口类结构后的附加字节数
	wc.cbWndExtra    = 0;								// 指定紧跟在窗口事例后的附加字节数
	wc.hInstance     = hInstance;						// 本模块的实例句柄
	wc.hIcon         = LoadIcon(hInstance, IDI_APPLICATION);	// 图标的句柄
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);		// 光标的句柄
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);		// 背景画刷的句柄
	wc.lpszMenuName  = NULL;							// 指向菜单的指针
	wc.lpszClassName = szClassName;						// 指向类名称的指针
	wc.hIconSm       = LoadIcon(hInstance, IDI_APPLICATION);	// 和窗口类关联的小图标

	// 2. 使用【窗口结构体】注册窗口
	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("窗口注册失败！"), TEXT("错误"), MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// 3. 创建窗口
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,		// 窗口的扩展风格
		szClassName,			// 指向注册类名的指针
		TEXT("窗口标题"),		// 指向窗口名称的指针
		WS_OVERLAPPEDWINDOW,	// 窗口风格
		CW_USEDEFAULT, CW_USEDEFAULT, 350, 200, // 窗口的 x,y 坐标以及宽高
		NULL,					// 父窗口的句柄
		NULL,					// 菜单的句柄
		hInstance,				// 应用程序实例的句柄
		NULL					// 指向窗口的创建数据
		);

	if(hwnd == NULL)
	{
		MessageBox(NULL, TEXT("窗口创建失败"), TEXT("错误"),MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// 4. 显示窗口
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// 6. 消息循环
	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}