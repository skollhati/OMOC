#include "GameProcess.h"



//���ϴ� �� ���� �Լ�
//setTextColor(RGB(255,128,0));
//�̹� �ִ� ������ �̿��� ���
//setConsoleTextAttribute(�ڵ�,�� ����);
void GameProcess::setTextColor(COLORREF color)
{
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFOEX csbi;

	csbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(hConsoleOutput, &csbi);

	csbi.ColorTable[1] = color;

	SetConsoleScreenBufferInfoEx(hConsoleOutput, &csbi);
	SetConsoleTextAttribute(hConsoleOutput, 1);
}


GameProcess::GameProcess()
{
	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	
	for (int i = 0; i < 50; i++)
	{
		gRoomList[i] = gRoomData();
	}

	g_menu = Menu();
	g_menu.InitMenu();
	MenuSelected(g_menu.ShowMainMenu());
}

void GameProcess::GameSelected(WORD* room_data)
{
	TCHAR* buf = (TCHAR*)room_data;
	SendPacket(GAME_ROOM_SELECTED,buf);
}

void GameProcess::GameRoomProc(WORD* select_num)
{
	if(select_num[0] == REFRESH)
	{
		SendPacket(GAME_ROOM_REFRESH, _T(""));
	}
	else
	{
		GameSelected(select_num);
	}
}

void GameProcess::MenuSelected(int n_menu)
{
	switch (n_menu)
	{
	case 3: 
		InitNetwork(8800,"127.0.0.1"); 
		SendPacket(USER_IN,g_menu.InputLoginInfo());
		Sleep(500);
		
		Sleep(1000);
		break;
	case 4: exit(0);
		break;
	}
}


UINT WINAPI GameProcess::WaittingTimer(LPVOID lpParam)
{
	GameProcess *pGP = (GameProcess *)lpParam;
	for (int i = 1; i < 11; i++)
	{
		Sleep(1000);
		if (i == 10)
		{
			pGP->SendPacket(GAME_REMATCH, _T("0"));
		}
	}
	
	return 0;
}

void GameProcess::JoinWaitGameRoom(TCHAR* title,short port,char* ip_addr)
{
	gRoom = GameRoom();
	gRoom.ShowGameWaitingRoom(title);
	gRoom.JoinGameRoomSocket(port, ip_addr,this->ClientSocket);
	SuspendThread(hReceive);
}

void GameProcess::MakeGameRoom(TCHAR* title)
{
	gRoom = GameRoom();
	gRoom.SetSocket(ClientSocket);
	gRoom.ShowGameWaitingRoom(title);
	SuspendThread(hReceive);
}

void GameProcess::ShowGameList()
{

}

void GameProcess::InsertGameList(PacketSet p_Packet)
{
	//���� Ŀ�ǵ�
	if (p_Packet.GetWORD() == GAME_ROOM_LIST_HEAD)
	{
		wTotalCount = p_Packet.GetWORD();
		wReceiveCount = 0;
	}
	else if (p_Packet.GetWORD() == GAME_ROOM_LIST_BODY)
	{
		WORD wtemp = p_Packet.GetWORD();
		gRoomList[wReceiveCount] = *(gRoomData *)p_Packet.GetStr();
		wReceiveCount += wtemp;
	}

	if (wReceiveCount == wTotalCount)
		ShowGameList();
	//ī��Ʈ
}

//networkprocess_udp ���� ��ġ�� ���ú���Ʈ..��ü �Լ��� �θ���?
void GameProcess::UDPRecive(TCHAR* buffer, WORD wSize)
{
	pPacket.GetInit(buffer);


	//����� �°� �� �Լ��� ��� ���ʴ�� ���� �ƴ� ��� ����
	if (pPacket.GetSize() == wSize)
	{

		switch (pPacket.GetWORD())
		{
		case USER_IN:
			gRoom.JoinRival(pPacket.GetStr());
			break;

		case USER_OUT:
			//���̹��� ������ ���� ���¿� ���� �Լ� ȣ��
			//���� ���̳� �����̳�
			if (myPlayState)
			{
				//������ ������ ��
			}
			else
			{
				//���ǿ��� �����°�
				gRoom.RivalOutWaitingRoom();
			}

			break;

		case GAME_COMMAND:
			XY temp_xy = strToXY(pPacket.GetStr());
			gRoom.RivalStoneInput(temp_xy.y, temp_xy.x);
			break;

		case GAME_ROOM_LIST:
			InsertGameList(pPacket);
			break;
		case LOGIN_OK:
			GameRoomProc(g_menu.ShowGameRoom());
			break;
		case GAME_ROOM_START:
			
			break;
	
		case CHATTING:

			break;
	

		case GAME_RETIRE: //RetireWin();
			break;

		}

	}

}

