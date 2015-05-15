#include <Winsock2.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")

void main()
{
    int err; // 错误信息
    int len;

    char sendBuf[100]; // 发送至客户端的字符串
    char recvBuf[100]; // 接受客户端返回的字符串

    SOCKET sockServer;     // 服务端 Socket
    SOCKADDR_IN addrServer;// 服务端地址
    SOCKET sockClient;     // 客户端 Scoket
    SOCKADDR_IN addrClient;// 客户端地址

    WSADATA wsaData;       // winsock 结构体
    WORD wVersionRequested;// winsock 的版本

    // 配置 Windows Socket版本
    wVersionRequested = MAKEWORD( 2, 2 );

    // 初始化 Windows Socket
    err = WSAStartup( wVersionRequested, &wsaData );

    if ( err != 0 )
    {
        // 启动错误，程序结束
        return;
    }

    /*
     * 确认WinSock DLL支持2.2
     * 请注意如果DLL支持的版本大于2.2至2.2
     * 它仍然会返回wVersion2.2的版本
     */

    if ( LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 2 )
    {
        // 启动错误，程序结束
        WSACleanup(); // 终止Winsock 2 DLL (Ws2_32.dll) 的使用
        return;
    }

    // 定义服务器端socket
    sockServer = socket(AF_INET, SOCK_STREAM, 0);

    //  设置服务端 socket
    addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY); // 本机IP
    addrServer.sin_family = AF_INET;                   // 协议类型是INET
    addrServer.sin_port = htons(6000);                 // 绑定端口6000

    // 将服务器端socket绑定在本地端口
    bind(sockServer, (SOCKADDR *)&addrServer, sizeof(SOCKADDR));

    // Listen 监听端口
    listen(sockServer, 5); // 5 为等待连接数目

    printf("服务器已启动:\n监听中...\n");

    len = sizeof(SOCKADDR);

    while (1)
    {
        // accept 会阻塞进程，直到有客户端连接上来为止
        sockClient = accept(sockServer, (SOCKADDR *)&addrClient, &len);
        // 当客户端连接上来时, 拼接如下字符串        
        sprintf(sendBuf, "欢迎 ip: %s 的用户连接, 这里是 Lellansin 的服务器\n", inet_ntoa(addrClient.sin_addr));
        // 向客户端发送字符串
        send(sockClient, sendBuf, strlen(sendBuf) + 1, 0);
        // 获取客户端返回的数据
        recv(sockClient, recvBuf, 100, 0);
        // 打印客户端返回的数据
        printf("%s\n", recvBuf);
        // 关闭socket
        closesocket(sockClient);
    }
}
