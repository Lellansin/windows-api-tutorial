
#include <stdio.h>
#include <Windows.h>

int main()
{
	HWND act = GetActiveWindow();

	if (RegisterHotKey(
		act,	// 注册快捷键的窗口句柄
		2,		// 热键标识符避免热键冲突
		MOD_CONTROL | MOD_NOREPEAT, // Ctrl 键  No Repeat 不重复发送
		'A'		// A
		))  
	{
		printf("快捷键 Ctrl + A 注册成功! \n\n");
	}

	MSG msg = {0};
	// 循环获取操作系统发来的消息
	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		// 当收到快捷键消息时
		if (msg.message == WM_HOTKEY)
		{
			printf("收到 WM_HOTKEY 快捷键消息\n");
			CHAR text[50];
			wsprintf(text, "wParam : 0x%x  lParam : 0x%x \n", msg.wParam, msg.lParam);
			printf(text);
		}
	}
}