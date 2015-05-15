#include <windows.h>
#include <stdio.h>    // for printf
#include <string.h>   // for string operation
 
int isDirectory(char *path);
void help();
 
int main(int argc, char const *argv[])
{
    char file_src[MAX_PATH]={0};
    char file_dest[MAX_PATH]={0};
 
    // 只输入程序名 和一个参数则调用help
    if (argc <= 2)
    {
        help();
        return 0;
    }
 
    memmove(file_src, argv[1], strlen(argv[1]));
    memmove(file_dest, argv[2], strlen(argv[2]));
 
    if( isDirectory(file_dest) )
    {   // 如果第二个参数是目录, 则拼装新的文件路径
        sprintf(file_dest, "%s\\%s", file_dest, file_src);
    }
 
    if( MoveFile(file_src, file_dest) == 0)
        printf("文件剪切失败！");
     
    return 0;
}
 
// 判断是否为目录
BOOL isDirectory(char *path)
{
    WIN32_FIND_DATA fd;
    BOOL rel = FALSE;
    char *p = path;
     
    // 查找到第一个文件的句柄
    HANDLE hFind = FindFirstFile(path, &fd);
 
    while(*p != '\0') p++;
 
    // 如果结尾是这两种符号就肯定是目录
    if( *(--p) == '\\' || *(p) == '/' ) {
        *p = '\0';
        return TRUE;
    } 
 
    // 判断是否获取错误
    if(hFind != INVALID_HANDLE_VALUE)
    {
        // 文件信息按位与上目录属性, 非目录则全部置零
        if( fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
        {
            rel = TRUE;  
        }
        // 关闭查找句柄
        FindClose(hFind);
    }
    return rel;  
}
 
void help()
{
    printf("剪切文件：\n");
    printf("mv <文件名> <新路径>\n");
    printf("mv <文件名> <新文件名>\n");
    printf("mv <文件名> <新路径\\新文件名>");
}