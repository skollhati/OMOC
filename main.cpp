#include "main.h"
//���� �ҽ�
#include"GameProcess.h"


//PacketSet	sPacketSet;
//sPacketSet.Init();
//sPacketSet.PutBYTE(1);
//
//sPacketSet.Send(UserNum);






//���� �ҽ�

int _tmain(int argc, char* argv[])
{
	setlocale(LC_ALL, "");
	//int a = 1;
	//int x = 0;
	//int i;
	//---------------------------���� �ҽ�------------------------

	//NetWorkProcess_UDP *pNetwork = new NetWorkProcess_UDP();

	GameProcess GameProc = GameProcess();
	GameProc.StartClient();
	
	while (1)
	{
		Sleep(200);
	}
	
	
	return 0;


}