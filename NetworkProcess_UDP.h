#ifndef __NETWORK_UDP_H__
#define __NETWORK_UDP_H__

#include "main.h"
//#include "GameProcess.h"
#include "PacketSet.h"

//UDP 500 πŸ¿Ã∆Æ
static CRITICAL_SECTION m_cs;

class NetWorkProcess_UDP
{
public:
	NetWorkProcess_UDP()
	{}
	

	//NetWorkProcess_UDP(GameProcess *pGame);


	virtual ~NetWorkProcess_UDP() = 0;
	

public:
	WORD CheckUserNum(char* ipAddr,int iPort);
	BOOL SendPacket(WORD com,TCHAR* Buffer);
	void InitNetwork(short port,char* ip_addr);
	void InitNetwork(short port, char* ip_addr,SOCKET client_sock);

	void ReceivePacket();
	virtual void UDPRecive(TCHAR* buffer,WORD wSize) = 0;
	void DisConnect();
	void IniSocketObj();
	void HeartBeatTimerReset();
	XY strToXY(TCHAR* sPacket);
	PSOCKET_OBJ InUserVector(char* ipAddr);
	
	static UINT WINAPI CheckHeartBeat(LPVOID lpParam);
	static UINT WINAPI ReceiveThread(LPVOID lpParam);

public:
	WSADATA wsaData;
	SOCKET ClientSocket;
	SOCKADDR_IN ToServer;
	SOCKADDR_IN FromServer;
	
	PacketSet pPacket;

	bool sending = false;
	DWORD wUserCount;
	DWORD fSize;
	DWORD Recv_Size;
	DWORD Send_Size;

	HANDLE hReceive;
	HANDLE hSend;
	HANDLE hTimer;
	HANDLE hHeartBeat;
	LARGE_INTEGER liDueTime;

	
	vector<PSOCKET_OBJ> vSocketData;
};

#endif // !__NETWORK_UDP_H__
