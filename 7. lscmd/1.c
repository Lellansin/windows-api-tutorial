
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
#include <Windows.h>;
#include <stdio.h>;
 
void welcome();
 
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
 
        printf("接收到命令：[%s]", Command_str);
    }
}
 
void welcome()
{
    printf("Lellansin's CMD Tool [版本 0.0.1]\n");
    printf("学习自制 (c) www.lellansin.com 欢迎交流\n");
}