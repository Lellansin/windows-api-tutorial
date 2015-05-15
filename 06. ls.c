#include <windows.h>
#include <stdio.h>    // for sprintf
#include <string.h>   // for memmove
 
int main(int argc, const char *argv[])
{
    CHAR path[MAX_PATH] = {0};  // 待列路径
    CHAR szFilePath[MAX_PATH];  // 具体查找路径
    HANDLE hListFile;           // 获取到的文件句柄
    WIN32_FIND_DATA fileData;   // 查找到的文件数据 
 
 
    if(argc == 1)   // 只输入程序名则显示当前目录
    {       
        GetCurrentDirectory(MAX_PATH,path);
    }else if(argc == 2) // 指定显示目录则显示指定目录
    {
        memmove(path, argv[1], strlen(argv[1]));
    }
     
    // 复制路径到具体查找路径
    lstrcpy(szFilePath, path);
    // 路径拼接通配符
    lstrcat(szFilePath, "\\*");
 
    // printf("列表路径： [%s] \n", szFilePath);
 
    // 查找路径下第一个文件/目录，获得句柄
    hListFile = FindFirstFile(szFilePath,&fileData);
 
    // 判断句柄是否获取到
    if(hListFile == INVALID_HANDLE_VALUE)
    {
        printf("错误：%d",GetLastError());
        return 1;
    } else {        
        do
        {   // 输出找到的文件名
            printf("%s\t", fileData.cFileName );
        }   // 查找下一个文件, 并获取其信息
        while(FindNextFile(hListFile, &fileData));
    }
    return 0;
}