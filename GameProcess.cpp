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
void GameProcess::NetworkThread()
{
	hReceive = (HANDLE)_beginthreadex(NULL, 0, GameProcess::ReceiveThread, (LPVOID)this, 0, NULL);
	//hHeartBeat = (HANDLE)_beginthreadex(NULL, 0, NetWorkProcess_UDP::CheckHeartBeat, (LPVOID)this, 0,NULL);
}

UINT WINAPI GameProcess::ReceiveThread(LPVOID lpParam)
{
	GameProcess* m_GameProc = (GameProcess *)lpParam;

	while (1)
	{
		m_GameProc->UDPRecive(m_GameProc->ReceivePacket());
	}
	return 0;
}

GameProcess::GameProcess()
{
	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	for (int i = 0; i < 50; i++)
	{
		gRoomList[i] = SENDING_GAME_ROOM();
	}

	g_menu = Menu();
	g_menu.InitMenu(3);
}

void GameProcess::StartClient()
{
	MenuSelected(g_menu.ShowMainMenu());
}

void GameProcess::GameSelected(WORD room_data)
{
	//���ľ���
	char* buf = (char*)room_data;
	SendPacket(JOIN_GAME, buf, sizeof(buf));
}

void GameProcess::GameRoomProc(WORD select_num)
{
	if (select_num == REFRESH)
	{
		SendPacket(GAME_ROOM_LIST, "", 1);
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
		InitNetwork(8800, "127.0.0.1");
		strcpy(player_name, g_menu.InputLoginInfo());
		NetworkThread();
		
		//Sleep(200);
		SendPacket(USER_IN, player_name, strlen(player_name));
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
			pGP->SendPacket(GAME_REMATCH, "0", 1);
		}
	}

	return 0;
}

void GameProcess::JoinWaitGameRoom(char* title, short port, char* ip_addr)
{
	gRoom = GameRoom();
//	gRoom.ShowGameWaitingRoom(title);
//	gRoom.JoinGameRoomSocket(port, ip_addr, this->ClientSocket);
	SuspendThread(hReceive);
}

void GameProcess::MakeGameRoom(char* title)
{
	gRoom = GameRoom();
	gRoom.SetSocket(ClientSocket);
	gRoom.ShowGameWaitingRoom(title,player_name);
	SuspendThread(hReceive);
}



//���Ӹ���Ʈ �Է�
void GameProcess::InsertGameList()
{
	int body_size = pPacket.GetWORD();
	
	for (int i = 0; i < body_size; i++)
	{
		(g_menu.g_List[offset + i]).game_number = pPacket.GetWORD();
		strcpy((g_menu.g_List[offset + i]).title, pPacket.GetStr());
	}

	offset += body_size;

	if (wTotalCount == offset)
	{
		WORD task = g_menu.ShowGameRoom(wTotalCount);
		RoomProcess(task);
		offset = 0;
	}
}

void GameProcess::RoomProcess(WORD task_num)
{
	char title[30];
	switch (task_num)
	{
	
	case NUMBER_ONE:
		strcpy(title,g_menu.ShowGameMakeOption());
		gRoom.ShowGameWaitingRoom(title,player_name);
		SendPacket(GAME_ROOM_MAKE, title, strlen(title));
		break;
	
	case NUMBER_FIVE:
		pPacket.Init();
		pPacket.PutWORD(GAME_ROOM_LIST);
		pPacket.ClosePacket();
		SendPacket(server_obj);
		break;
	
	case SPACE:
		pPacket.Init();
		pPacket.PutWORD(JOIN_GAME);
		pPacket.PutWORD(g_menu.room_num);
		pPacket.ClosePacket();
		SendPacket(server_obj);
		break;
	
	case ESC: exit(0);
		break;
	}
}

//networkprocess_udp ���� ��ġ�� ���ú���Ʈ..��ü �Լ��� �θ���?
void GameProcess::UDPRecive(char* buffer)
{
	pPacket.GetInit(buffer);


	//����� �°� �� �Լ��� ��� ���ʴ�� ���� �ƴ� ��� ����


	switch (pPacket.GetWORD())
	{
	case USER_IN:
		//���� ��ü �ֱ�
		//gRoom.JoinRival(pPacket.GetStr(),player_name);
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
	case HEAD:wTotalCount = pPacket.GetWORD();
		break;

	case BODY:InsertGameList();
		break;

	case JOIN_GAME: 
		
		HOST->iPort = pPacket.GetWORD();
		strcpy(HOST->ipAddr, pPacket.GetStr());
		
		pPacket.Init();
		pPacket.PutWORD(USER_IN);
		pPacket.PutStr(player_name,strlen(player_name));
		pPacket.ClosePacket();
		SendPacket(HOST);

		gRoom.ShowGameWaitingRoom(g_menu.room_title,player_name);
		break;

	case LOGIN_OK:
		//	GameRoomProc(g_menu.ShowGameRoom());
		break;

	case GAME_ROOM_START:
		break;

	case CHATTING:
		break;

	case GAME_RETIRE: //RetireWin();
		break;

	}



}

