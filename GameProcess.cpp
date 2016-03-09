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
	g_menu = Menu();
	//hSend = p_hSend;

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
		Sleep(1000);
		GameRoomProc(g_menu.ShowGameRoom());
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
			//������ ���̹� ����
			break;

		case USER_OUT:
			//���̹��� ������ ���� ���¿� ���� �Լ� ȣ��
			//���� ���̳� �����̳�
			break;

		case GAME_COMMAND:
			XY temp_xy = strToXY(pPacket.GetStr());
			gRoom.RivalStoneInput(temp_xy.y, temp_xy.x);

			break;

		case GAME_ROOM_LIST:
			//����Ʈ�� �ѹ��� �ٹ޾Ƽ� ����
			//refresh�� ���� ���� ����
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

