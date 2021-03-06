#ifndef __PACKETSET_H__
#define __PACKETSET_H__

#include"main.h"
#include "VersusInfo.h"

#define MESSAGE_REN 100
#define USER_REN 50
#define BUFFER_SIZE 1024

typedef struct PACKET_STRUCT
{
	DWORD command;
	TCHAR message[1024];
}UnPacket;

class PacketSet
{

public:
	PacketSet()
	{}

	~PacketSet()
	{}

public:
	//TCHAR* PackedPacket(TCHAR message[], WORD command);
	//UnPacket UnpackPacket(TCHAR recvPacket[]);
	
	void	Init();
	void	PutBYTE(BYTE	bByte);
	void    PutWORD(WORD	wWORD);
	void    Putint(int      iint);
	void	PutStr(TCHAR* sStr);
	void    GetInit(TCHAR*    ib_Buffer);
	
	BYTE	GetBYTE(void);
	WORD	GetWORD(void);
	int		GetInt(void);
	TCHAR*	GetStr(void);


private:
	int		m_iLen;
	TCHAR	m_szBuffr[2000];
	TCHAR*  m_rzBuffr;

};
#endif