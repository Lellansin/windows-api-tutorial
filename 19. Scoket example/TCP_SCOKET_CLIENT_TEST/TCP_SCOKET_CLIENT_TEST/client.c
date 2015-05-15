#include <Winsock2.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")

void main()
{
	int err;
	char *message;
	char recvBuf[100];

	SOCKET sockClient; // 客户端 Scoket
	SOCKADDR_IN addrServer; // 服务端地址

	WSADATA wsaData;
	WORD wVersionRequested;

	wVersionRequested = MAKEWORD( 2, 2 );

	err = WSAStartup( wVersionRequested, &wsaData );

	if ( err != 0 )
	{
		return;
	}

	if ( LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 2 )
	{
		// 启动错误，程序结束
		WSACleanup( );
		return;
	}

	// 新建客户端 scoket
	sockClient = socket(AF_INET, SOCK_STREAM, 0);

	// 定义要连接的服务端地址
	addrServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");  // 目标IP (127.0.0.1是本机地址)
	addrServer.sin_family = AF_INET;                           // 协议类型是INET
	addrServer.sin_port = htons(6000);                         // 连接端口1234

	// 让 sockClient 连接到 服务端
	connect(sockClient, (SOCKADDR *)&addrServer, sizeof(SOCKADDR));

	// 从服务端获取数据
	recv(sockClient, recvBuf, 100, 0);

	// 打印数据
	printf("%s\n", recvBuf);

	message = "服务端你好~";

	// 发送数据到服务端
	send(sockClient, message, strlen(message) + 1, 0);

	// 关闭socket
	closesocket(sockClient);
	WSACleanup();

	getchar(); // 暂停
}
