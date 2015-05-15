#include <windows.h>

int main()
{
    MessageBox(NULL, (LPCSTR)"hello, windows programming", (LPCSTR)"Title", MB_OK);
    return 0;
}

/*
	如果使用 vc6.0 出现 windows.h 未找到之类的错误
	可以考虑下载完整版或者是加强版的vc6
	地址：http://hi.baidu.com/jsj08/item/fa8ac4c44aafa22947d5c046

	当然使用 visual studio 2010 及以上版本也不错
*/