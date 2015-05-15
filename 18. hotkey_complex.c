
#include <stdio.h>
#include <Windows.h>

int main()
{
	MSG msg = {0};
	HWND hConsole = GetActiveWindow();

	// Ctrl + D
	RegisterHotKey(hConsole,2,MOD_CONTROL | MOD_NOREPEAT,'D');
	// Win键 + Z
	RegisterHotKey(hConsole,2,MOD_WIN | MOD_NOREPEAT,'Z');
	// Ctrl + Alt + S
	RegisterHotKey(hConsole,2,MOD_CONTROL | MOD_ALT | MOD_NOREPEAT,'S');
	// Ctrl + Alt + Shift + A
	RegisterHotKey(hConsole,2,MOD_CONTROL | MOD_ALT | MOD_SHIFT | MOD_NOREPEAT,'A');
	
	// 循环获取操作系统发来的消息
	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		// 当收到快捷键消息时
		if (msg.message == WM_HOTKEY)
		{
			printf("收到 WM_HOTKEY 快捷键消息\n");
			printf("wParam : 0x%x  lParam : 0x%x \n", msg.wParam, msg.lParam);

			switch(LOWORD(msg.lParam)) // 获取低16位的值 
			{
				// 当用户先按 Ctrl
				case MOD_CONTROL:
					switch(HIWORD(msg.lParam))
					{
						case 'D':
							printf("Ctrl + D 被按下！ \n\n");
						break;
					}
				break;

				// 当用户先按 Windows 键
				case MOD_WIN:
					switch(HIWORD(msg.lParam))
					{
						case 'Z':
							printf("Win + Z 被按下！ \n\n");
						break;
					}
				break;

				// 当用户先按 Ctrl + Alt
				case MOD_CONTROL | MOD_ALT:
					switch(HIWORD(msg.lParam)) // 获取高16位的值
					{
						case 'S':
							printf("Ctrl + Alt + S 被按下！ \n\n");
						break;					
					}
				break;

				// 当用户先按 Ctrl + Alt + Shift
				case MOD_CONTROL | MOD_ALT | MOD_SHIFT:
					switch(HIWORD(msg.lParam)) // 获取高16位的值
					{
						case 'A':
							printf("Ctrl + Alt + Shift + A 被按下！ \n\n");
						break;					
					}
				break;
			}
		}
	}
}