
#include <stdio.h> 
#include <windows.h> 

// ָ������ָ������
typedef void (*fun_pointer)(void);

// main
VOID main(VOID) 
{ 
	HINSTANCE hDLL; 
	BOOL flagGetFun = FALSE; 
	fun_pointer p;

	// ���� Dll
	hDLL = LoadLibrary(TEXT("DLLTEST.dll")); 

	// �ж��Ƿ���سɹ�
	if (hDLL != NULL) 
	{ 
		printf("ģ����سɹ�\n");

		// ���ָ�����������ĵ�ַ
		p = (fun_pointer) GetProcAddress(hDLL, "helloDLL"); 

		// �ж��Ƿ�ɹ�
		if (NULL != p) 
		{
			printf("������ȡ�ɹ���׼�����ú���\n");
			p(); // �ɹ������DLL�еĺ���
		}else
		{
			printf("������ȡʧ�ܣ�\n");
			printf("error: %u\n", GetLastError()); 
		}
		// �ͷ�DLL 
		if (!FreeLibrary(hDLL))
		{
			printf("DLL�ͷ�ʧ��\n");
			printf("error: %u\n", GetLastError()); 
		}		
	}else
	{
		printf("ģ�����ʧ�ܣ�\n");
		printf("error: %u\n", GetLastError()); 
	}		

	system("pause");
}