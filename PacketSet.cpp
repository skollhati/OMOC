#include "PacketSet.h"
#include "main.h"

void PacketSet::Init()
{
	m_iLen = 0;
	memset(m_szBuffr, 0, sizeof(m_szBuffr));
}

void PacketSet::PutSize()
{
	*(WORD *)(&m_szBuffr[0]) = m_iLen;
}

void PacketSet::PutBYTE(BYTE bByte)
{
	*(BYTE *)(&m_szBuffr[m_iLen]) = bByte;
	m_iLen += sizeof(bByte);
}

void PacketSet::PutWORD(WORD wWORD)
{
	*(WORD *)(&m_szBuffr[m_iLen]) = wWORD;
	m_iLen += sizeof(WORD);
}

void PacketSet::Putint(int iint)
{
	*(int *)(&m_szBuffr[m_iLen]) = iint;
	m_iLen += sizeof(int);
}

void PacketSet::PutStr(char* sStr,WORD buf_size)
{
	memcpy(&m_szBuffr[m_iLen],sStr,buf_size);

	m_iLen += buf_size;

}
void PacketSet::ClosePacket()
{
	*(WORD *)&m_szBuffr[m_iLen] = 0;
	m_iLen += sizeof(WORD);
}

void PacketSet::GetInit(char* ib_Buffer)
{
	m_rzBuffr = ib_Buffer;
	m_iLen = 0;
}

BYTE PacketSet::GetBYTE()
{
	BYTE bByte = *(BYTE *)&m_rzBuffr[m_iLen];
	m_iLen += sizeof(BYTE);

	return bByte;
}


WORD PacketSet::GetSize()
{
	WORD wSize = *(WORD *)&m_rzBuffr[0];

	return wSize;
}

WORD PacketSet::GetWORD()
{

	WORD wWORD = *(WORD *)&m_rzBuffr[m_iLen];
	m_iLen += sizeof(WORD);

	return wWORD;
}

int PacketSet::GetInt()
{
	int iINT = *(int *)&m_rzBuffr[m_iLen];
	m_iLen += sizeof(int);

	return iINT;
}

char* PacketSet::GetStr()
{
	char* sStr = (char *)&m_rzBuffr[m_iLen];
	//memcpy(sStr, &m_rzBuffr[m_iLen],);
	m_iLen += (strlen(sStr)+1);
	
	return sStr;
}

char* PacketSet::PrintBuffer()
{
	return m_szBuffr;
}






