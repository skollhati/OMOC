#include "NetworkProcess_UDP.h"
#pragma comment(lib,"ws2_32.lib")
#include <iostream>
using namespace std;

NetWorkProcess_UDP::NetWorkProcess_UDP()
{
	short port_num = 8800;
	if (WSAStartup(0x202, &wsaData) == SOCKET_ERROR)
	{
		cout << "WinSock initialize fault" << endl;
		WSACleanup();
	}

	memset(&ToServer, 0, sizeof(ToServer));
	memset(&FromServer, 0, sizeof(FromServer));

	ToServer.sin_family = AF_INET;
	ToServer.sin_addr.s_addr = inet_addr("127.0.0.1");
	ToServer.sin_port = htons(port_num);

	ClientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (ClientSocket == INVALID_SOCKET)
	{
		cout << "socket creation fault" << endl;
		closesocket(ClientSocket);
		WSACleanup();
		exit(0);
	}

	
}

void NetWorkProcess_UDP::ReceivePacket()
{


}

void NetWorkProcess_UDP::SendPacket(TCHAR* Buffer)
{
	pPacket.PutWORD(2);
	pPacket.PutStr(Buffer);
	pPacket.PutSize();
	Send_Size = sendto(ClientSocket, (const char*)Buffer, BUFFER_SIZE, 0, (struct sockaddr*)&ToServer, sizeof(ToServer));
	
	
	if (Send_Size != pPacket.m_iLen)
	{

	}

}