#include <windows.h>
#include <stdio.h>    // for printf
void help();
 
int main(int argc, char const *argv[])
{
    int i;
 
    // ������ĿΪ1 ���û�ֻ�����������������յ�һ������
    if (argc == 1)
    {
        help();
        return 0;
    }
 
    // ����ָ��������ָ��Ĳ���
    for (i = 1; i < argc; i++)
    {
        CreateFile(
            argv[i],                // �ļ���
            GENERIC_WRITE,          // д��Ȩ��
            0,                      // ��ֹ�������̷���
            NULL,                   // �ӽ��̲��ɼ̳б����
            CREATE_NEW,             // ��������ʱ�������ļ�
            FILE_ATTRIBUTE_NORMAL,  // ��ͨ�ļ�
            NULL);                  // ������ģ���ļ�
    }
     
     
    return 0;
}
 
void help()
{
    printf("�������ļ���");
    printf("touch <�ļ���1> <�ļ���2> ...");
}