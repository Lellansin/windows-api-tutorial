#include <Windows.h>
#include <stdio.h>
 
DWORD WINAPI ThreadProc (LPVOID lpThreadParameter)
{
    while(1)
    {
        printf("%s \n", (char *)lpThreadParameter);
        Sleep(533);
    }
    return 0;
}
 
int main()
{
    DWORD Tid;
    char *PassData;
 
    PassData = "Hello 线程1";
 
    CreateThread(
        NULL,       // 不能被子进程继承
        0,          // 默认堆栈大小
        ThreadProc, // 线程调用函数过程
        PassData,   // 传递参数
        0,          // 创建后立即执行
        &Tid        // 保存创建后的线程ID
    );
 
    printf("线程1 创建成功 线程ID：%u \n", Tid);
 
    PassData = "hi    线程2";
 
    CreateThread(
        NULL,       // 不能被子进程继承
        0,          // 默认堆栈大小
        ThreadProc, // 线程调用函数过程
        PassData,   // 传递参数
        0,          // 创建后立即执行
        &Tid        // 保存创建后的线程ID
    );
 
    printf("线程2 创建成功 线程ID：%u \n", Tid);
 
    system("pause");
    // 主线程暂停在这里等待用户按任意键，其他线程则继续执行
    // 不过一旦按下任意键，主线程退进程，则其他线程均终止
    // 注意这不是因为主线程的原因，在子线程中退进程效果一样
    // 因为线程是归属于进程的，进程退出那么旗下的所有线程也都会终止
 
    return 0;
}