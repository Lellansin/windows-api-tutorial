
#include <windows.h>
#include "dll.h"

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void* lpReserved)
{
	switch(dwReason)
	{
		// ��̬���ӿ�ӳ�䵽ĳ�����̵ĵ�ַ�ռ�
		case DLL_PROCESS_ATTACH:
			/**
			 * ��DLL�ձ�����ʱ������LoadLibrary�����˴�ר����������ʼ��������
			 * �����ʼ��ʧ�ܿ��Է��� false ����DLL�Ͳ��ᱻ����������
			 **/
		break;

		// Ӧ�ó��򴴽��µ��߳�
		case DLL_THREAD_ATTACH:
			
		break;

		// Ӧ�ó���ĳ���߳�������ֹ
		case DLL_THREAD_DETACH:

		break;
		
		// ��̬���ӿ⽫��ж��
		case DLL_PROCESS_DETACH:
			/**
			 * ��DLL��Ҫ��ж��ʱ������FreeLibrary��,�˴�ר��������������
			 * ��ر��ļ����ͷ��ڴ�ռ��
			 **/
		break;
	}
	return 1;
}

void helloDLL(void)
{
	MessageBox(NULL, TEXT("Hello DLL~"), TEXT("Title"), MB_OK);
}