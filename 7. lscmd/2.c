#include <Windows.h>;
#include <stdio.h>;
#include <string.h>;  // for strcmp
#include <stdlib.h>;  // for exit
 
void welcome();
void command_switch(char *cmd_str);
 
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
        memset(&Command_str, 0, MAX_PATH);
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
    char cmd_tmp[MAX_PATH]={0};
    char *pstr = cmd_str, *ptmp = cmd_tmp;
 
    // 一直赋值到换行之前
    while(*pstr != '\r' && *pstr != '\n')
    {
        *ptmp++ = *pstr++;
    }
    // printf("收到命令：[%s]\n", cmd_tmp);
 
    // 判断命令
    if( strcmp(cmd_tmp, "hi") == 0 )
    {
        printf("你好~");
    } else if ( strcmp( cmd_tmp, "exit" ) == 0 )
    {
        exit(0);
    }else
    {
        printf("Error: 命令未找到\n");
    }
}
 
void welcome()
{
    printf("Lellansin's CMD Tool [版本 0.0.1]\n");
    printf("学习自制 (c) www.lellansin.com 欢迎交流\n");
}