#include "GameRoom.h"


void GameRoom::gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void GameRoom::JoinRival(short port_num,char* ip_addr,TCHAR* rivalplayer)
{
	InitNetwork(port_num,ip_addr);
	_tcscpy(rival, rivalplayer);
	ShowGameWaitingRoom();
}

void GameRoom::JoinGameRoomSocket(short port, char* ip_addr,SOCKET client_sock)
{
	InitNetwork(port, ip_addr, client_sock);
}

void GameRoom::DrawGameRoom()
{
	
}

void GameRoom::RivalOutWaitingRoom()
{
	ClearRivalInfo();
	
	if (!GameMaster)
		GameMaster = 1;

	_tcscpy(rival, _T(""));
}

void GameRoom::initGame()
{
	int GMap[MAP_Y][MAP_X] = { 0, };

	int i = 0, k = 0;
	for (i = 0; i < MAP_Y; i++)
	{
		for (k = 0; k < MAP_X; k++)
		{
			if (i == 0)
			{
				if (k == 0)
					printf("┌");
				else if (k + 1 == MAP_X)
					printf("┐");
				else
					printf("┬");
			}
			else if (i + 1 < MAP_Y)
			{
				if (k == 0)
					printf("├");
				else if (k + 1 == MAP_X)
					printf("┤");
				else
					printf("┼");
			}
			else
			{
				if (k == 0)
					printf("└");
				else if (k + 1 == MAP_X)
					printf("┘");
				else
					printf("┴");
			}
		}
		hd = { MAP_X / 2,MAP_Y / 2 };
		printf("\n");
	}
}

int GameRoom::searchStone(xy hd, int flag, int p, int sw)
{
	if (GMap[hd.y][hd.x] != flag) return 0;
	if (p == 0)
	{
		hd.y += sw;
	}
	else if (p == 1)
	{
		hd.x += sw;
	}
	else if (p == 2)
	{
		hd.x += sw;
		hd.y += sw;
	}
	else
	{
		hd.x += sw;
		hd.y -= sw;
	}
	return 1 + searchStone(hd, flag, p, sw);
}

void GameRoom::checkStone(xy hd, int turn)
{
	int i = 0, countStone = 0;
	for (i = 0; i < 4; i++)
	{
		countStone = 0;
		countStone += searchStone(hd, turn, i, 1);
		countStone += searchStone(hd, turn, i, -1);

		if (countStone == 6)
		{
			gotoxy(0, MAP_Y);
			if (turn == MY_TURN)
			{
				_tprintf(_T("%s"), player);
				//vInfo->setVersusUpdate(true);
			}
			else
			{
				_tprintf(_T("%s"), rival);
				//vInfo->setVersusUpdate(false);
			}
			printf("님이 승리하셨습니다.\n");
			getch();

			Sleep(2000);
			
		}
	}
}

void GameRoom::startGame()
{
	
	_tprintf(_T("매칭 완료!! 5초 후 게임을 시작합니다!\n"));

	system("cls");
	initGame();
	Sleep(5000);

	char ip = '\0';


	while (1)
	{
		if (kbhit())
		{
			ip = getch();
			switch (ip)
			{
			case LEFT:
				if (hd.x > 0)
					hd.x -= 1;
				break;
			case RIGHT:
				if (hd.x < MAP_X - 1)
					hd.x += 1;
				break;
			case UP:
				if (hd.y >0)
					hd.y -= 1;
				break;
			case DOWN:
				if (hd.y < MAP_Y - 1)
					hd.y += 1;
				break;
			case SPACE:
				if (GMap[hd.y][hd.x] == 0)
				{
					gotoxy(hd.x * 2, hd.y);

					if (turn == MY_TURN)
					{
						GMap[hd.y][hd.x] = MY_TURN;
						printf("%s", my_stone);
						checkStone(hd, turn);
						SendPacket(GAME_COMMAND, (TCHAR*)&hd);
						turn = RIVAL_TURN;
					}
				}
				break;
			case ESC:
				SendPacket(USER_OUT, NULL);
				exit(1);
				break;
			}
			gotoxy(hd.x * 2, hd.y);
		}
	}
}


void GameRoom::setGame(MATCHING match)
{
	_tcscpy(rival, match.rivalName);

	if (match.fPlay)
	{
		strcpy(my_stone, "●");
		strcpy(rival_stone, "○");
		turn = MY_TURN;
	}
	else
	{
		strcpy(my_stone, "○");
		strcpy(rival_stone, "●");
		turn = RIVAL_TURN;
	}
}

void GameRoom::RivalStoneInput(int y, int x)
{
	GMap[y][x] = RIVAL_TURN;
	printf("%s", rival_stone);
	checkStone(hd, turn);
	turn = MY_TURN;
}

void GameRoom::UDPRecive(TCHAR* buffer, WORD wSize)
{
	pPacket.GetInit(buffer);


	//사이즈에 맞게 온 함수일 경우 차례대로 진행 아닐 경우 무시
	if (pPacket.GetSize() == wSize)
	{

		switch (pPacket.GetWORD())
		{
		case USER_IN:
			
			break;

		case GAME_COMMAND:
			XY temp_xy = strToXY(pPacket.GetStr());
			RivalStoneInput(temp_xy.y, temp_xy.x);
			break;

		case GAME_REMATCH:

			break;

		case GAME_RETIRE: RetireWin();
			break;

		}

	}

}

void GameRoom::RetireWin()
{
	cout << "상대방이 종료했습니다. 5초 후 대기실로 돌아갑니다." << endl;

	Sleep(5000);
	ClearRivalInfo();

}

void GameRoom::SetSocket(SOCKET m_sock)
{
	memcpy(&my_sock, &m_sock, sizeof(m_sock));
	hReceive = (HANDLE)_beginthreadex(NULL,0,NetWorkProcess_UDP::ReceiveThread)
}

void GameRoom::ShowGameWaitingRoom(TCHAR* title)
{
	if (_tcscmp(this->title, title) != 0);
		_tcscpy(this->title, title);

	cout << "방제 : " << title << endl;
	cout << "방장 : ";
	gotoxy(0, 2);
	for (int i = 0; i < 15; i++)
	{
		printf("─");
	}

	gotoxy(33, 2);
	for (int i = 0; i < 15; i++)
	{
		printf("─");
	}
	gotoxy(0, 3);
	cout << "플레이어 1 : "<<player;

	gotoxy(33, 3);
	cout << "플레이어 2 : ";
	
	if (!(_tcscmp(rival, _T("")) == 0))
		cout << rival;

	gotoxy(0, 4);
	cout << "준비 상태:";
	gotoxy(33, 4);
	cout << "준비 상태:";

	gotoxy(0, 5);
	for (int i = 0; i < 15; i++)
	{
		printf("─");
	}

	gotoxy(33, 5);
	for (int i = 0; i < 15; i++)
	{
		printf("─");
	}


	ShowChatFrame();
	gotoxy(0, 23);
	printf("채팅창 \"#준비완료\" 입력 : 준비완료 / 방장 \"#게임시작\" 입력 : 게임시작 ");

	InputChat();
}

void GameRoom::InsertRivalName(TCHAR* rival_name)
{
	
	gotoxy(33, 3);
	cout << "플레이어 2: "<<rival_name;
}

void GameRoom::ClearRivalInfo()
{
	memset(&ToServer, 0, sizeof(ToServer));
	_tcscpy(rival, _T(""));
	ShowGameWaitingRoom("");
}

void GameRoom::InputChat()
{
	TCHAR* chat_str;
	gotoxy(0, 24);
	for (int i = 0; i < 100; i++)
	{
		printf(" ");
	}
	gotoxy(0, 24);

	printf("채팅 입력:");
	
	_tcscanf(_T("%s"), chat_str);
	SendPacket(CHATTING,chat_str);

	InputChat();
}

void GameRoom::ShowChatFrame()
{
	gotoxy(0, 9);
	printf("채팅창");

	gotoxy(0, 10);
	for (int i = 0; i < 32; i++)
	{
		printf("─");
	}

	gotoxy(0, 20);
	for (int i = 0; i < 32; i++)
	{
		printf("─");
	}

	gotoxy(0, 10);
	printf("┌");
	gotoxy(0, 20);
	printf("└");
	gotoxy(62, 10);
	printf("┐");
	gotoxy(62, 20);
	printf("┘");

}

