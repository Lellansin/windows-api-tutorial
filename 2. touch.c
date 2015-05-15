#include <windows.h>
#include <stdio.h>    // for printf
void help();
 
int main(int argc, char const *argv[])
{
    int i;
 
    // 参数数目为1 即用户只输入程序名，程序仅收到一个参数
    if (argc == 1)
    {
        help();
        return 0;
    }
 
    // 遍历指针数组所指向的参数
    for (i = 1; i < argc; i++)
    {
        CreateFile(
            argv[i],                // 文件名
            GENERIC_WRITE,          // 写入权限
            0,                      // 阻止其他进程访问
            NULL,                   // 子进程不可继承本句柄
            CREATE_NEW,             // 仅不存在时创建新文件
            FILE_ATTRIBUTE_NORMAL,  // 普通文件
            NULL);                  // 不适用模板文件
    }
     
     
    return 0;
}
 
void help()
{
    printf("创建新文件：");
    printf("touch <文件名1> <文件名2> ...");
}