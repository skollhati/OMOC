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
	TCHAR buffer[BUFFER_SIZE];

	int FromSever_Size = sizeof(FromServer);

	while (1)
	{
		Recv_Size = recvfrom(ClientSocket, (char *)buffer, BUFFER_SIZE, 0, (struct sockaddr*)&FromServer, &FromSever_Size);

		if (Recv_Size == 0)
		{
			cout << "recvForm() error! " << endl;

		}
		pPacket.GetInit(buffer);
		if (Recv_Size >= pPacket.GetSize())
		{
			break;
		}
	}

	cout << "Recv From " << inet_ntoa(FromServer.sin_addr) << endl;
	cout << "DATA : " << buffer << endl;
}

void NetWorkProcess_UDP::SendPacket(TCHAR* Buffer)
{

	pPacket.PutWORD(2);
	pPacket.PutStr(Buffer);
	pPacket.PutSize();

	while (1)
	{
		Send_Size = sendto(ClientSocket, (const char*)Buffer, BUFFER_SIZE, 0, (struct sockaddr*)&ToServer, sizeof(ToServer));

		if (Send_Size == pPacket.m_iLen)
		{
			break;
		}
	}

	pPacket.Init();

}