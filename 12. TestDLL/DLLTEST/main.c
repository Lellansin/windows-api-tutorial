
#include <windows.h>
#include "dll.h"

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void* lpReserved)
{
	switch(dwReason)
	{
		// 动态链接库映射到某个进程的地址空间
		case DLL_PROCESS_ATTACH:
			/**
			 * 当DLL刚被加载时触发（LoadLibrary），此处专门用来做初始化工作，
			 * 如果初始化失败可以返回 false 这样DLL就不会被继续加载了
			 **/
		break;

		// 应用程序创建新的线程
		case DLL_THREAD_ATTACH:
			
		break;

		// 应用程序某个线程正常终止
		case DLL_THREAD_DETACH:

		break;
		
		// 动态链接库将被卸载
		case DLL_PROCESS_DETACH:
			/**
			 * 当DLL将要被卸载时触发（FreeLibrary）,此处专门用来做清理工作
			 * 如关闭文件，释放内存空间等
			 **/
		break;
	}
	return 1;
}

void helloDLL(void)
{
	MessageBox(NULL, TEXT("Hello DLL~"), TEXT("Title"), MB_OK);
}