
#include <windows.h>

HWND hgWnd;
HHOOK myhook;

/**************************************************************** 
  WH_KEYBOARD hook procedure 
  �I�P���Ӵ������
 ****************************************************************/ 
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) 
{ 	
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
	const char *info = NULL;
	char text[50], data[20];

	PAINTSTRUCT ps;
	HDC hdc;

    if (nCode >= 0)
	{
		if      (wParam == WM_KEYDOWN)		info = "��ͨ���I̧��";
		else if (wParam == WM_KEYUP)		info = "��ͨ���I����";
		else if (wParam == WM_SYSKEYDOWN)	info = "ϵ�y���I̧��";
		else if (wParam == WM_SYSKEYUP)		info = "ϵ�y���I����";

		ZeroMemory(text, sizeof(text));
		ZeroMemory(data, sizeof(data));
		wsprintf(text, "%s - ������ [%04d], ɨ���� [%04d]  ", info, p->vkCode, p->scanCode);
		wsprintf(data, "���IĿ�y�飺 %c  ", p->vkCode);

		hdc = GetDC(hgWnd);			
		TextOut(hdc, 10, 10, text, strlen(text));
		TextOut(hdc, 10, 30, data, strlen(data));
		ReleaseDC(hgWnd,hdc);
	}
    
    return CallNextHookEx(myhook, nCode, wParam, lParam);
} 

// 5. ���ڹ��̴���
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{	
	hgWnd = hwnd;

	switch(msg)
	{
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
    WNDCLASSEX wc;	// http://baike.baidu.com/view/1750396.htm
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
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);	// ͼ��ľ��
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);		// ���ľ��
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);		// ������ˢ�ľ��
    wc.lpszMenuName  = NULL;							// ָ��˵���ָ��
    wc.lpszClassName = szClassName;						// ָ�������Ƶ�ָ��
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);	// �ʹ����������Сͼ��

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

	// ���ü���ȫ�ּ���
	myhook = SetWindowsHookEx( 
		WH_KEYBOARD_LL, // �������͡����̡�
		KeyboardProc,	// ������
		hInstance,		// ��ǰʵ�����
		0				// �������ھ��(NULLΪȫ�ּ���)
	); 

	if(myhook == NULL)
	{		
		wsprintf(text, "���̼���ʧ�ܣ�error : %d \n", GetLastError());
		MessageBox(hwnd, text, TEXT("����"), MB_OK);
	}


    // 5. ��Ϣѭ��
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}
