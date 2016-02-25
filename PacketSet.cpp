#include "PacketSet.h"
#include "main.h"

UnPacket PacketSet::UnPacket PacketSet();
{


}

UnPacket PacketSet::~UnPacket PacketSet()
{

}

TCHAR* PacketSet::PackedPacket(TCHAR message[], WORD command)
{
	
	TCHAR szBuffer[1024];
	int offset = (sizeof(WORD) * 2);

	*(WORD *)(&szBuffer[0]) = (WORD)(_tcslen(message) + 6); 
	*(WORD *)(&szBuffer[2]) = command;						
	_tcscpy(&szBuffer[4], message);							
	
	offset += _tcslen(message);
	*(WORD *)(&szBuffer[offset]) = 00;					
	
	return szBuffer;
}


UnPacket PacketSet::UnpackPacket(TCHAR recvPacket[])
{
	UnPacket uPacket;
	uPacket.command = *(DWORD *)&recvPacket[2];
	_tcscpy(uPacket.message, (TCHAR *)(&recvPacket[4]));

	return uPacket;
}




