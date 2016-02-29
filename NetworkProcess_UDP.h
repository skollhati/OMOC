#ifndef __NETWORK_UDP_H__
#define __NETWORK_UDP_H__

#include "main.h"



class NetWorkProcess_UDP
{
public:
	NetWorkProcess_UDP();
	

	//NetWorkProcess_UDP(GameProcess *pGame);


	~NetWorkProcess_UDP()
	{}

public:
	WORD CheckUserNum(char* ipAddr,int iPort);
	BOOL SendPacket(WORD com,TCHAR* Buffer);
	void ReceivePacket();
	UNPACK_DATA UDPRecive(WORD UserNum,TCHAR* buffer,WORD wSize);
	void IniSocketObj();
	void HeartBeatTimerReset();
	XY strToXY(TCHAR* sPacket);
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

	HANDLE hTimer;
	HANDLE hHeartBeat;
	LARGE_INTEGER liDueTime;

	queue<UNPACK_DATA> qUnpackData;
	vector<PSOCKET_OBJ> vSocketData;
};

#endif // !__NETWORK_UDP_H__
