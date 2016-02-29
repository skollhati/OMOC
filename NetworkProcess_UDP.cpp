#include "NetworkProcess_UDP.h"
#pragma comment(lib,"ws2_32.lib")
#include <iostream>
using namespace std;

NetWorkProcess_UDP::NetWorkProcess_UDP()
{
	
	short port_num = 8800;
	wUserCount = 0;
	
	hTimer = CreateWaitableTimer(NULL, FALSE, NULL);

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

	hHeartBeat = (HANDLE)_beginthreadex(NULL, 0, NetWorkProcess_UDP::CheckHeartBeat, (LPVOID)this, 0,NULL);
	IniSocketObj();
}

//유저소켓정보 객체 초기화
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
			//접속 허용 용량 벗어남 알림
		}

		qUnpackData.push( UDPRecive(wUserNum, buffer, Recv_Size));
	}

	cout << "Recv From " << inet_ntoa(FromServer.sin_addr) << endl;
	cout << "DATA : " << buffer << endl;

}

//유저넘버를 체크하는 함수 
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
		return -1; //빈 객체가 없을때- 접속허용 용량을 벗어날때
	}


	return pSocket->wUserNum;
}

//유저소켓 정보를 가진 벡터에서 같은 객체가 있는지 찾는 함수
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

BOOL NetWorkProcess_UDP::SendPacket(WORD com,TCHAR* Buffer)
{
	pPacket.Init();
	pPacket.PutWORD(com);
	pPacket.PutStr(Buffer);
	pPacket.PutSize();


	Send_Size = sendto(ClientSocket, (const char*)Buffer, BUFFER_SIZE, 0, (struct sockaddr*)&ToServer, sizeof(ToServer));

	if (Send_Size == pPacket.m_iLen)
	{
		HeartBeatTimerReset();
		return true;
	}

	return false;
}

UNPACK_DATA NetWorkProcess_UDP::UDPRecive(WORD UserNum, TCHAR* buffer, WORD wSize)
{
	pPacket.GetInit(buffer);
	UNPACK_DATA m_Unpack;

	//사이즈에 맞게 온 함수일 경우 차례대로 진행 아닐 경우 무시
	if (pPacket.GetSize() == wSize)
	{
		m_Unpack.com = pPacket.GetWORD();
		_tcscpy(m_Unpack.buf, pPacket.GetStr());


		//switch (pPacket.GetWORD())
		//{
		//case MATCHING_GAME:
		//	//선공 후공(0,1) + 상대 아이디
		//	/*MATCHING match_game = *(MATCHING *)pPacket.GetStr();
		//	pGameProc->setGame(match_game);
		//	SetEvent(pGameProc->hEvent);*/
		//	break;

		//case GAME_COMMAND:
		//	/*XY temp_xy = strToXY(pPacket.GetStr());
		//	pGameProc->RivalStoneInput(temp_xy.y, temp_xy.x);*/
		//	break;

		//case GAME_INFO:
		//	//승패
		//	//게임 결과 유저정보 갱신 (상대편 정보도 표시)
		//	break;
		//}

	}
	else
		m_Unpack = { 0, };

	return m_Unpack;
}

XY NetWorkProcess_UDP::strToXY(TCHAR* sPacket)
{

	XY unpack_xy = *(XY *)&sPacket[0];

	return unpack_xy;
}

void NetWorkProcess_UDP::HeartBeatTimerReset()
{
	CancelWaitableTimer(hTimer);
	SetWaitableTimer(hTimer, &liDueTime, 30000, NULL, NULL, FALSE);
}

UINT WINAPI NetWorkProcess_UDP::CheckHeartBeat(LPVOID lpParam)
{
	
	NetWorkProcess_UDP* m_NetProc = (NetWorkProcess_UDP *)lpParam;
	SetWaitableTimer(m_NetProc->hTimer, &(m_NetProc->liDueTime), 30000, NULL, NULL, FALSE);
	
	while (1)
	{
		WaitForSingleObject(m_NetProc->hTimer,INFINITE);
		m_NetProc->SendPacket(HEARTBEAT, NULL);
	}


	return 0;
}



