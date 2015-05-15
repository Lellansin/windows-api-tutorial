#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib,"ws2_32.lib")

void Help( void );

int main(int argc, char *argv[])
{
	WORD wVersion = MAKEWORD(2, 0);
	WSADATA wsaData;

	//sockaddr_in�ṹ��
	struct sockaddr_in sin;

	int iFromPort;
	int iToPort;
	int iNowPort;
	char *cHost;

	HOSTENT *host_entry;
	char *host_name;
	char host_address[256];

	SOCKET s;

	int iOpenPort = 0;
	int port[256], i;

	if (argc != 4)
	{
		Help();
		return -1;
	}

	iFromPort = atoi(argv[2]);
	iToPort = atoi(argv[3]);
	host_name = argv[1];

	if (iFromPort > iToPort || iFromPort < 0 || iFromPort > 65535 || iToPort < 0 || iToPort > 65535)
	{
		printf("��ʼ�˿ڲ��ܴ��ڽ����˿�,�ҷ�ΧΪ��1--65535 ");
		return 0;
	}

	if ( WSAStartup(wVersion , &wsaData) )
	{
		printf("��ʼ��ʧ�ܣ�");
		return -1;
	}

	host_entry = gethostbyname(host_name);

	if (host_entry != 0)
	{
		wsprintf( host_address, "%d.%d.%d.%d",
			(host_entry->h_addr_list[0][0] & 0x00ff),
			(host_entry->h_addr_list[0][1] & 0x00ff),
			(host_entry->h_addr_list[0][2] & 0x00ff),
			(host_entry->h_addr_list[0][3] & 0x00ff)
			);
		printf("\n�������ƣ�%s  ������ַ��%s \n", host_name, host_address);
	}

	cHost = host_address;

	printf("======= ��ʼɨ�� ======= \n");

	for (iNowPort = iFromPort; iNowPort <= iToPort; iNowPort++)
	{
		s = socket(AF_INET, SOCK_STREAM, 0);
		if (s == INVALID_SOCKET)
		{
			printf("create socket() failed!");
			WSACleanup();
		}

		sin.sin_family = AF_INET;
		sin.sin_port = htons(iNowPort);
		sin.sin_addr.S_un.S_addr = inet_addr(cHost);

		if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR)
		{
			printf("%s -> %d:δ���� \n", cHost, iNowPort);
			closesocket(s);
		}
		else
		{
			printf("%s -> %d:���� \n", cHost, iNowPort);
			port[iOpenPort] = iNowPort;
			iOpenPort ++;
			closesocket(s);
		}
	}

	printf("======= ɨ���� ======= \n");
	printf("������%s ɨ�赽%d���˿�,�ֱ��ǣ� \n", host_name, iOpenPort);

	for ( i = 0; i < iOpenPort; i++)
	{
		printf("%d ", port[i]);
	}

	//�ر�socket
	closesocket(s);
	WSACleanup();
	return 0;
}

//��������
void Help()
{
	printf("Usage: \n");
	printf("Port.exe <TargetIP> <BeginPort> <EndPort> \n");
	printf("Example: \n");
	printf("Port.exe 127.0.0.1 100 200 ");
}