#include <windows.h>
#include <stdio.h>
 
void help();
 
int main(int argc, char const *argv[])
{
    int ProcessID;
    HANDLE hProcess;
 
    // 如果只有一个参数
    if(argc == 1)
    {
        help();
        return 0;
    }
 
    // 如果有两个参数
    if(argc == 2)
    {
        // 获取进程id
        ProcessID = atoi(argv[1]);
        // 获取进程句柄
        hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, (DWORD)ProcessID );
        // 终止进程
        TerminateProcess(hProcess, 0);
    }
}
 
void help()
{
    printf("终止进程\n");
    printf("kill <进程id>\n");
}