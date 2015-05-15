#include <windows.h>
#include <stdio.h>    // for printf
#include <string.h>   // for string operation
 
int isDirectory(char *path);
void help();
 
int main(int argc, char const *argv[])
{
    char file_src[MAX_PATH]={0};
    char file_dest[MAX_PATH]={0};
 
    // ֻ��������� ��һ�����������help
    if (argc <= 2)
    {
        help();
        return 0;
    }
 
    memmove(file_src, argv[1], strlen(argv[1]));
    memmove(file_dest, argv[2], strlen(argv[2]));
 
    if( isDirectory(file_dest) )
    {   // ����ڶ���������Ŀ¼, ��ƴװ�µ��ļ�·��
        sprintf(file_dest, "%s\\%s", file_dest, file_src);
    }
 
    if( CopyFile(file_src, file_dest, 0) == 0)
        printf("�ļ�����ʧ�ܣ�");
     
    return 0;
}
 
// �ж��Ƿ�ΪĿ¼
BOOL isDirectory(char *path)
{
    WIN32_FIND_DATA fd;
    BOOL rel = FALSE;
    char *p = path;
     
    // ���ҵ���һ���ļ��ľ��
    HANDLE hFind = FindFirstFile(path, &fd);
 
    while(*p != '\0') p++;
 
    // �����β�������ַ��žͿ϶���Ŀ¼
    if( *(--p) == '\\' || *(p) == '/' ) {
        *p = '\0';
        return TRUE;
    } 
 
    // �ж��Ƿ��ȡ����
    if(hFind != INVALID_HANDLE_VALUE)
    {
        // �ļ���Ϣ��λ����Ŀ¼����, ��Ŀ¼��ȫ������
        if( fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
        {
            rel = TRUE;  
        }
        // �رղ��Ҿ��
        FindClose(hFind);
    }
    return rel;  
}
 
void help()
{
    printf("�����ļ���\n");
    printf("cp <�ļ���> <��·��>\n");
    printf("cp <�ļ���> <���ļ���>\n");
    printf("cp <�ļ���> <��·��\\���ļ���>");
}