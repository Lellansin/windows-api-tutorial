
#include <stdio.h> 
#include <windows.h> 

// 指向函数的指针类型
typedef void (*fun_pointer)(void);

// main
VOID main(VOID) 
{ 
	HINSTANCE hDLL; 
	BOOL flagGetFun = FALSE; 
	fun_pointer p;

	// 加载 Dll
	hDLL = LoadLibrary(TEXT("DLLTEST.dll")); 

	// 判断是否加载成功
	if (hDLL != NULL) 
	{ 
		printf("模块加载成功\n");

		// 获得指定导出函数的地址
		p = (fun_pointer) GetProcAddress(hDLL, "helloDLL"); 

		// 判断是否成功
		if (NULL != p) 
		{
			printf("函数获取成功，准备调用函数\n");
			p(); // 成功则调用DLL中的函数
		}else
		{
			printf("函数获取失败！\n");
			printf("error: %u\n", GetLastError()); 
		}
		// 释放DLL 
		if (!FreeLibrary(hDLL))
		{
			printf("DLL释放失败\n");
			printf("error: %u\n", GetLastError()); 
		}		
	}else
	{
		printf("模块加载失败！\n");
		printf("error: %u\n", GetLastError()); 
	}		

	system("pause");
}