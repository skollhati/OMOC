#ifndef __NETWORK_UDP_H__
#define __NETWORK_UDP_H__

#include "main.h"
#include "PacketSet.h"


#define USER_IN 1
#define USER_OUT 4
#define GAME_COMMAND 100
#define HEARTBEAT 5

class NetWorkProcess_UDP
{
public:
	NetWorkProcess_UDP();


	~NetWorkProcess_UDP()
	{}

public:
	WORD CheckUserNum(char* ipAddr,int iPort);
	void SendPacket(TCHAR* Buffer);
	void ReceivePacket();
	void UDPRecive(WORD UserNum,TCHAR* buffer,WORD wSize);
	void IniSocketObj();
	PSOCKET_OBJ InUserVector(char* ipAddr);
public:

	WSADATA wsaData;
	SOCKET ClientSocket;

	SOCKADDR_IN ToServer;
	SOCKADDR_IN FromServer;

	PacketSet pPacket;

	DWORD wUserCount;
	DWORD fSize;
	DWORD Recv_Size;
	DWORD Send_Size;
	vector<PSOCKET_OBJ> vSocketData;
};

#endif // !__NETWORK_UDP_H__
