#include <windows.h>
#include <stdio.h>    // for printf
 
#define FILE_DEL_MAX 10
 
void help();
 
struct _del_attr {
    int Force_del;  // ǿ��ɾ��ѡ��
} ;
 
struct _del_list {
    const char *File_to_Del[FILE_DEL_MAX]; // ��ɾ�ļ��б�
    int count;              // ��ɾ�ļ�����
    struct _del_attr Attr;  // ɾ��ѡ��
} Delete_list = {0};
 
int main(int argc, const char *argv[])
{
    int i;
    char cmd;
 
    if(argc == 1)
    {
        help();
    }
 
    // ��������
    for (i = 1; i < argc; i++)
    {
        // ��ȡ����ѡ��
        if( *argv[i] == '-') // �����ǰָ���ַ����ĵ�һ��Ϊ '-'
        {
            if( strcmp( argv[i], "-f" ) == 0 )
            {
                Delete_list.Attr.Force_del = 1;
            }
        } else // �����ļ�·��
        {           
            Delete_list.File_to_Del[Delete_list.count] = argv[i];
            // printf("��ɾ�ļ�·�� [%s] �ѱ���\n", Delete_list.File_to_Del[Delete_list.count]);
            Delete_list.count++;
            // printf("Ŀǰ��ɾ�ļ���Ŀ %d\n", Delete_list.count);
        }
    }
 
    // ������ɾ�ļ��б�
    for (i = 0; i < Delete_list.count; i++)
    {
        if( Delete_list.Attr.Force_del == 1 ) // �Ƿ�ǿ��ɾ��
        {           
            if( !DeleteFile( Delete_list.File_to_Del[i] ) ) // ���������ɾ��ʧ��
            {
                printf("ɾ���ļ�����%x\n",GetLastError());
            }
        }else
        {   // ѯ���Ƿ�ɾ��
            printf("�Ƿ�Ҫɾ���ļ� [%s] ��(y/n)", Delete_list.File_to_Del[i] );
            scanf("%c", &cmd);
            getchar(); // ���ջس�
            if ( cmd == 'y' )
            {
                if( !DeleteFile( Delete_list.File_to_Del[i] ) ) // ���������ɾ��ʧ��
                {
                    printf("ɾ���ļ�����%x\n",GetLastError());
                }else
                {
                    printf("�ļ� [%s] ��ɾ��\n", Delete_list.File_to_Del[i]);
                }
            }
        }
    }
}
 
void help()
{
    printf("ɾ���ļ���\n");  
    printf("rm <�ļ���1> <�ļ���2> ... [-ѡ��]\n"); 
    printf("ѡ� -f ǿ��ɾ��");
}