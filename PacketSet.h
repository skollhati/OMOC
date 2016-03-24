#ifndef __PACKETSET_H__
#define __PACKETSET_H__

#include"main.h"
#include "PacketSet.h"


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
	{
		memset(m_szBuffr, 0, sizeof(m_szBuffr));
	}

	~PacketSet()
	{}

public:
	//TCHAR* PackedPacket(TCHAR message[], WORD command);
	//UnPacket UnpackPacket(TCHAR recvPacket[]);
	
	void	Init();
	void	PutBYTE(BYTE	bByte);
	void    PutWORD(WORD	wWORD);
	void    Putint(int      iint);
	void	PutStr(char* sStr,WORD buf_size);
	void	PutSize();
	void ClosePacket();
	char*	PrintBuffer();
	void    GetInit(char*    ib_Buffer);
	BYTE	GetBYTE(void);
	WORD	GetWORD(void);
	int		GetInt(void);
	char*	GetStr(void);
	WORD	GetSize(void);
	
	
	int		m_iLen;


private:
	char	m_szBuffr[2000];
	char*  m_rzBuffr;

};
#endif