#include <Windows.h>

void echo(LPSTR str)
{
	MessageBox(NULL, str, TEXT("��ʾ"), MB_OK);
}

// 5. ���ڹ��̴���
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{	
	CHAR text[50];
	switch(msg)
	{
	// ���ڴ�����Ϣ
	case WM_CREATE:
		RegisterHotKey(
			hwnd,	// ע���ݼ��Ĵ��ھ��
			1,		// �ȼ���ʶ�������ȼ���ͻ
			MOD_CONTROL | MOD_NOREPEAT, // Ctrl ��  No Repeat ���ظ�����
			'A'		// A
			); // Ctrl + A
		RegisterHotKey(hwnd, 2, MOD_CONTROL | MOD_NOREPEAT,'B');// Ctrl + B
		RegisterHotKey(hwnd, 3, MOD_ALT | MOD_NOREPEAT,'A');	// Alt + A
		RegisterHotKey(hwnd, 4, MOD_ALT | MOD_NOREPEAT,'B');	// Alt + B
		RegisterHotKey(hwnd, 5, MOD_NOREPEAT,'S');				// ֱ�Ӱ� S
	break;

	// ��ݼ���Ϣ
	case WM_HOTKEY:
		/***
		 * wParam ����ע��ʱ������ȼ���ʶ��
		 * lParam ��λ���(��A��ֵ)����λ�渴�ϼ���ֵ(��Ctrl��ֵ)
		 */
		//wsprintf(text, "wParam : %p  lParam : %p", wParam, lParam);
		//echo(text);

		switch(LOWORD(lParam)) // ��ȡ��16λ��ֵ 
		{
		// ���û��Ȱ� ctrl
		case MOD_CONTROL:

			switch(HIWORD(lParam)) // ��ȡ��16λ��ֵ
			{
				case 'A':
					echo("Ctrl + A �����£�");
				break;
				case 'B':
					echo("Ctrl + B �����£�");
				break;
			}

		break;

		// ���û��Ȱ� Alt
		case MOD_ALT:

			switch(HIWORD(lParam)) // ��ȡ��16λ��ֵ
			{
				case 'A':
					echo("Alt + A �����£�");
				break;
				case 'B':
					echo("Alt + B �����£�");
				break;
			}

		break;

		// û����ϼ�
		case 0: 

			switch(HIWORD(lParam)) // ��ȡ��16λ��ֵ
			{
				case 'S':
					echo("S ������");
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

	// 1. ����ע�ᴰ�ڽṹ��
	wc.cbSize        = sizeof(WNDCLASSEX);				// ע�ᴰ�ڽṹ��Ĵ�С
	wc.style         = 0;								// ���ڵ���ʽ
	wc.lpfnWndProc   = WndProc;							// ָ�򴰿ڴ�����̵ĺ���ָ��
	wc.cbClsExtra    = 0;								// ָ�������ڴ�����ṹ��ĸ����ֽ���
	wc.cbWndExtra    = 0;								// ָ�������ڴ���������ĸ����ֽ���
	wc.hInstance     = hInstance;						// ��ģ���ʵ�����
	wc.hIcon         = LoadIcon(hInstance, IDI_APPLICATION);	// ͼ��ľ��
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);		// ���ľ��
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);		// ������ˢ�ľ��
	wc.lpszMenuName  = NULL;							// ָ��˵���ָ��
	wc.lpszClassName = szClassName;						// ָ�������Ƶ�ָ��
	wc.hIconSm       = LoadIcon(hInstance, IDI_APPLICATION);	// �ʹ����������Сͼ��

	// 2. ʹ�á����ڽṹ�塿ע�ᴰ��
	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("����ע��ʧ�ܣ�"), TEXT("����"), MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// 3. ��������
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,		// ���ڵ���չ���
		szClassName,			// ָ��ע��������ָ��
		TEXT("���ڱ���"),		// ָ�򴰿����Ƶ�ָ��
		WS_OVERLAPPEDWINDOW,	// ���ڷ��
		CW_USEDEFAULT, CW_USEDEFAULT, 350, 200, // ���ڵ� x,y �����Լ����
		NULL,					// �����ڵľ��
		NULL,					// �˵��ľ��
		hInstance,				// Ӧ�ó���ʵ���ľ��
		NULL					// ָ�򴰿ڵĴ�������
		);

	if(hwnd == NULL)
	{
		MessageBox(NULL, TEXT("���ڴ���ʧ��"), TEXT("����"),MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// 4. ��ʾ����
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// 6. ��Ϣѭ��
	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}