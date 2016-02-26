#include "NetworkProcess_UDP.h"
#pragma comment(lib,"ws2_32.lib")
#include <iostream>
using namespace std;

NetWorkProcess_UDP::NetWorkProcess_UDP()
{
	short port_num = 8800;
	wUserCount = 0;
	
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
	WORD wUserNum;
	while (1)
	{
		Recv_Size = recvfrom(ClientSocket, (char *)buffer, BUFFER_SIZE, 0, (struct sockaddr*)&FromServer, &FromSever_Size);

		if (Recv_Size == 0)
		{
			cout << "recvForm() error! " << endl;
			continue;
		}
		
		wUserNum = CheckUserNum(inet_ntoa(FromServer.sin_addr), FromServer.sin_port);
		
		UDPRecive(wUserNum,,);
	}

	cout << "Recv From " << inet_ntoa(FromServer.sin_addr) << endl;
	cout << "DATA : " << buffer << endl;

}

WORD NetWorkProcess_UDP::CheckUserNum(char* ipAddr, int iPort)
{
	if (vSocketData.size() == 0 || InUserVector(ipAddr) == NULL)
	{
		PSOCKET_OBJ pSocketObj = new SOCKET_DATA();
		memset(pSocketObj, 0, sizeof(SOCKET_DATA));
		
		strcpy(pSocketObj->ipAddr, ipAddr);
		pSocketObj->bOnOff = TRUE;
		pSocketObj->iPort = iPort;
		pSocketObj->wUserNum = (++wUserCount);
		
		vSocketData.push_back(pSocketObj);
	}
	else
	{

	}
	return;
}

PSOCKET_OBJ NetWorkProcess_UDP::InUserVector(char* ipAddr)
{
	vector<PSOCKET_OBJ>::iterator itor = vSocketData.begin();
	
	for (itor; itor != vSocketData.end(); itor++)
	{
		if (!strcmp((*itor)->ipAddr,ipAddr))
		{
			return *itor;
		}
	}

		return NULL;
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

void NetWorkProcess_UDP::UDPRecive(WORD UserNum, WORD wCom, TCHAR* buffer, WORD wSize)
{
	switch (wCom)
	{
	case USER_IN:
		break;
	case USER_OUT:
		break;
	case GAME_COMMAND:
		break;
	}
}

void NetWorkProcess_UDP::UserNumbering(char* ipAddr, int iPort)
{

}