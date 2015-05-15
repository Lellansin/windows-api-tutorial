#include <Windows.h>;
#include <stdio.h>;
#include <string.h>;  // for strcmp
#include <stdlib.h>;  // for exit
 
void welcome();
void command_switch(char *cmd_str);
BOOL CreateChildProcess(char *cmd_str);
 
int main()
{
    char Command_str[MAX_PATH];
    DWORD Command_len;
    HANDLE hConsoleInput;  
 
    // 获取输出流的句柄
    hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);  
 
    // 输出欢迎信息
    welcome();
 
    while(1)
    {
        // 清空命令字符串
        ZeroMemory(&Command_str, MAX_PATH);
        // 输出提示符
        printf("\nLscmd>;");
        // 读取输入流
        ReadFile( 
            hConsoleInput,  // 文件句柄
            Command_str,    // 获取内容的缓冲字符数组
            MAX_PATH,       // 缓冲数组大小
            &Command_len,   // 实际读出的大小
            NULL);
 
        command_switch(Command_str);
    }
}
 
void command_switch(char *cmd_str)
{
    char *pstr = cmd_str;
 
    // 遍历到换行之前
    while(*pstr != '\r' && *pstr != '\n')
    {
        *pstr++;
    }
    // 覆盖换行
    *pstr = '\0';
    // printf("收到命令：[%s]\n", cmd_str);
 
    // 判断命令
    if( strcmp(cmd_str, "hi") == 0 )
    {
        printf("你好~ 欢迎使用 Lellansin 的cmd工具\n");
    } else if ( strcmp( cmd_str, "exit" ) == 0 )
    {
        exit(0);
    }else
    {
        // 创建子进程
        CreateChildProcess(cmd_str);
    }
}
 
BOOL CreateChildProcess(char *cmd_str)
{
    STARTUPINFO start_info;
    PROCESS_INFORMATION process_info;
    BOOL flag;
 
    // 将启动信息结构清零 ( 相当于 memset 0, 不过效率更高 )
    ZeroMemory( &start_info, sizeof(start_info) );
    // 设置结构大小，cb属性应为结构的大小
    start_info.cb = sizeof(start_info);
    // 将进程信息结构清零
    ZeroMemory( &process_info, sizeof(process_info) );
 
    flag = CreateProcess( 
        NULL,           // 不传程序路径, 使用命令行
        cmd_str,        // 命令行命令
        NULL,           // 不继承进程句柄(默认)
        NULL,           // 不继承线程句柄(默认)
        FALSE,          // 不继承句柄(默认)
        0,              // 没有创建标志(默认)
        NULL,           // 使用默认环境变量
        NULL,           // 使用父进程的目录
        &start_info,    // STARTUPINFO 结构
        &process_info );// PROCESS_INFORMATION 保存相关信息
 
    if ( !flag )
    {
        // 创建失败
        printf( "Error: 命令未找到 (%d).\n", GetLastError() );
        return 0;
    }
 
    // 等待子进程结束
    // 使用到了通过 PROCESS_INFORMATION 结构体获取子进程的句柄 hProcess
    WaitForSingleObject( process_info.hProcess, INFINITE );
    // 关闭进程句柄和线程句柄
    CloseHandle( process_info.hProcess );
    CloseHandle( process_info.hThread );
 
    return 1;
}
 
void welcome()
{
    printf("Lellansin's CMD Tool [版本 0.0.1]\n");
    printf("学习自制 (c) www.lellansin.com 欢迎交流\n");
}