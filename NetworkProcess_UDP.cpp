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

	IniSocketObj();


}

//������������ ��ü �ʱ�ȭ
void NetWorkProcess_UDP::IniSocketObj()
{
	for (int i = 0; i < 10; i++)
	{
		PSOCKET_OBJ pSocketObj = new SOCKET_DATA();
		memset(pSocketObj, 0, sizeof(SOCKET_DATA));
		pSocketObj->wUserNum = i;
		vSocketData.push_back(pSocketObj);
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

		if (wUserNum == -1)
		{
			//���� ��� �뷮 ��� �˸�
		}

		UDPRecive(wUserNum, buffer, Recv_Size);
	}

	cout << "Recv From " << inet_ntoa(FromServer.sin_addr) << endl;
	cout << "DATA : " << buffer << endl;

}

//�����ѹ��� üũ�ϴ� �Լ� 
WORD NetWorkProcess_UDP::CheckUserNum(char* ipAddr, int iPort)
{
	PSOCKET_OBJ pSocket = InUserVector(ipAddr);

	if (pSocket->bOnOff == 0)
	{
		strcpy(pSocket->ipAddr, ipAddr);
		pSocket->bOnOff = TRUE;
		pSocket->iPort = iPort;

		return pSocket->wUserNum;
	}
	else if (pSocket == NULL)
	{
		return -1; //�� ��ü�� ������- ������� �뷮�� �����
	}


	return pSocket->wUserNum;
}

//�������� ������ ���� ���Ϳ��� ���� ��ü�� �ִ��� ã�� �Լ�
PSOCKET_OBJ NetWorkProcess_UDP::InUserVector(char* ipAddr)
{

	if (vSocketData.size() == 0)
		return NULL;

	vector<PSOCKET_OBJ>::iterator itor = vSocketData.begin();
	PSOCKET_OBJ pEmptyObj = NULL;
	for (itor; itor != vSocketData.end(); itor++)
	{
		if (!strcmp((*itor)->ipAddr, ipAddr))
		{
			return (*itor);
		}
		if ((*itor)->bOnOff == 0)
		{
			pEmptyObj = *itor;
		}

	}
	return pEmptyObj;
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

void NetWorkProcess_UDP::UDPRecive(WORD UserNum, TCHAR* buffer, WORD wSize)
{
	pPacket.GetInit(buffer);
	//����� �°� �� �Լ��� ��� ���ʴ�� ���� �ƴ� ��� ����
	if (pPacket.GetSize() == wSize)
	{
		switch (pPacket.GetWORD())
		{
		case USER_IN:
			//���� ���� ��� ã���ֱ�
			break;
		case USER_OUT:
			//�ش� ���� �ƿ� �� ��ü ����
			break;
		case GAME_COMMAND:
			//Ŀ�ǵ� �Լ� GameProcess��ü�� �Ѱ��ֱ�
			break;
		}
	}
}





