#include "PacketSet.h"
#include "main.h"

TCHAR* PacketSet::PackedPacket(TCHAR message[], WORD command)
{
	
	TCHAR szBuffer[1024];
	int offset = (sizeof(WORD) * 2);

	*(WORD *)(&szBuffer[0]) = (WORD)(_tcslen(message) + 6); //보낼 메세지 사이즈 + 가변크기(2) + 패킷타입(2) + 00
	*(WORD *)(&szBuffer[2]) = command;						//커맨드
	_tcscpy(&szBuffer[4], message);							//보낼 메시지
	
	offset += _tcslen(message);
	*(WORD *)(&szBuffer[offset]) = 00;					//패킷 경계 00
	
	return szBuffer;
}


UnPacket PacketSet::UnpackPacket(TCHAR recvPacket[])
{
	UnPacket uPacket;
	uPacket.command = *(DWORD *)&recvPacket[2];
	_tcscpy(uPacket.message, (TCHAR *)(&recvPacket[4]));

	return uPacket;
}




