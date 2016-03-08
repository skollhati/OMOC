#include "GameProcess.h"



//원하는 색 지정 함수
//setTextColor(RGB(255,128,0));
//이미 있는 색상을 이용할 경우
//setConsoleTextAttribute(핸들,색 지정);
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

void GameProcess::UDPRecive(TCHAR* buffer, WORD wSize)
{
	pPacket.GetInit(buffer);


	//사이즈에 맞게 온 함수일 경우 차례대로 진행 아닐 경우 무시
	if (pPacket.GetSize() == wSize)
	{

		switch (pPacket.GetWORD())
		{
		case MATCHING_GAME:
			////선공 후공(0,1) + 상대 아이디
			//MATCHING match_game = *(MATCHING *)pPacket.GetStr();
			//setGame(match_game);
			//SetEvent(hEvent);
			break;

		case GAME_COMMAND:
		/*	XY temp_xy = strToXY(pPacket.GetStr());
			RivalStoneInput(temp_xy.y, temp_xy.x);*/
			break;

		case GAME_REMATCH:

			break;

		case GAME_RETIRE: //RetireWin();
			break;

		}

	}

}

