#ifndef __NETWORK_UDP_H__
#define __NETWORK_UDP_H__

#include "main.h"
#include "PacketSet.h"

class NetWorkProcess_UDP
{
public:
	NetWorkProcess_UDP();
	

	~NetWorkProcess_UDP()
	{}

public:
	void UnpackPacket();
	void SendPacket(TCHAR* Buffer);
	void ReceivePacket();

public:

	WSADATA wsaData;
	SOCKET ClientSocket;
	
	SOCKADDR_IN ToServer;
	SOCKADDR_IN FromServer;
	
	PacketSet pPacket;
	
	DWORD fSize;
	DWORD Recv_Size;
	DWORD Send_Size;

};

#endif // !__NETWORK_UDP_H__
