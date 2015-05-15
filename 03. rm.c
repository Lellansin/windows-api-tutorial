#include <windows.h>
#include <stdio.h>    // for printf
 
#define FILE_DEL_MAX 10
 
void help();
 
struct _del_attr {
    int Force_del;  // 强制删除选项
} ;
 
struct _del_list {
    const char *File_to_Del[FILE_DEL_MAX]; // 待删文件列表
    int count;              // 待删文件数量
    struct _del_attr Attr;  // 删除选项
} Delete_list = {0};
 
int main(int argc, const char *argv[])
{
    int i;
    char cmd;
 
    if(argc == 1)
    {
        help();
    }
 
    // 遍历参数
    for (i = 1; i < argc; i++)
    {
        // 获取参数选项
        if( *argv[i] == '-') // 如果当前指向字符串的第一个为 '-'
        {
            if( strcmp( argv[i], "-f" ) == 0 )
            {
                Delete_list.Attr.Force_del = 1;
            }
        } else // 保存文件路径
        {           
            Delete_list.File_to_Del[Delete_list.count] = argv[i];
            // printf("待删文件路径 [%s] 已保存\n", Delete_list.File_to_Del[Delete_list.count]);
            Delete_list.count++;
            // printf("目前待删文件数目 %d\n", Delete_list.count);
        }
    }
 
    // 遍历待删文件列表
    for (i = 0; i < Delete_list.count; i++)
    {
        if( Delete_list.Attr.Force_del == 1 ) // 是否强制删除
        {           
            if( !DeleteFile( Delete_list.File_to_Del[i] ) ) // 如果非零则删除失败
            {
                printf("删除文件错误：%x\n",GetLastError());
            }
        }else
        {   // 询问是否删除
            printf("是否要删除文件 [%s] ？(y/n)", Delete_list.File_to_Del[i] );
            scanf("%c", &cmd);
            getchar(); // 回收回车
            if ( cmd == 'y' )
            {
                if( !DeleteFile( Delete_list.File_to_Del[i] ) ) // 如果非零则删除失败
                {
                    printf("删除文件错误：%x\n",GetLastError());
                }else
                {
                    printf("文件 [%s] 已删除\n", Delete_list.File_to_Del[i]);
                }
            }
        }
    }
}
 
void help()
{
    printf("删除文件：\n");  
    printf("rm <文件名1> <文件名2> ... [-选项]\n"); 
    printf("选项： -f 强制删除");
}