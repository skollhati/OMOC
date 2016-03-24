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


	~NetWorkProcess_UDP()
	{}
	

public:
	WORD CheckUserNum(char* ipAddr,int iPort);
	BOOL SendPacket(WORD com,char* Buffer,WORD buf_size);
	void InitNetwork(short port,char* ip_addr);
	void InitNetwork(short port, char* ip_addr,SOCKET client_sock);
	BOOL SendPacket(PSOCKET_OBJ Client);

	char* ReceivePacket();
	virtual void UDPRecive(char* buffer) = 0;
	void DisConnect();
	void IniSocketObj();
	void HeartBeatTimerReset();
	XY strToXY(char* sPacket);
	PSOCKET_OBJ InUserVector(char* ipAddr);
	
	static UINT WINAPI CheckHeartBeat(LPVOID lpParam);

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

	PSOCKET_OBJ server_obj;
	
	vector<PSOCKET_OBJ> vSocketData;
};

#endif // !__NETWORK_UDP_H__
