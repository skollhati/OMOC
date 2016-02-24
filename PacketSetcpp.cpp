#include "PacketSet.h"
#include "main.h"

TCHAR* PacketSet::PackedPacket(TCHAR message[], WORD command)
{
	
	TCHAR szBuffer[1024];
	int offset = (sizeof(WORD) * 2);

	*(WORD *)(&szBuffer[0]) = (WORD)(_tcslen(message) + 6); //���� �޼��� ������ + ����ũ��(2) + ��ŶŸ��(2) + 00
	*(WORD *)(&szBuffer[2]) = command;						//Ŀ�ǵ�
	_tcscpy(&szBuffer[4], message);							//���� �޽���
	
	offset += _tcslen(message);
	*(WORD *)(&szBuffer[offset]) = 00;					//��Ŷ ��� 00
	
	return szBuffer;
}


UnPacket PacketSet::UnpackPacket(TCHAR recvPacket[])
{
	UnPacket uPacket;
	uPacket.command = *(DWORD *)&recvPacket[2];
	_tcscpy(uPacket.message, (TCHAR *)(&recvPacket[4]));

	return uPacket;
}




