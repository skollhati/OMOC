#include "GameRoom.h"


void GameRoom::gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void GameRoom::JoinRival(char* rivalplayer)
{
	strcpy(rival, rivalplayer);
	//ShowGameWaitingRoom(title,rivalplayer);
}

void GameRoom::JoinGameRoomSocket(short port_num, char* ip_addr)
{
	RivalPlayer->iPort = port_num;
	strcpy(RivalPlayer->ipAddr, ip_addr);

}

void GameRoom::DrawGameRoom()
{

}

void GameRoom::RivalOutWaitingRoom()
{
	ClearRivalInfo();

	if (!GameMaster)
		GameMaster = 1;

	strcpy(rival, "");
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

BOOL GameRoom::SendPacket(PSOCKET_OBJ p_sock)
{
	
	SOCKADDR_IN ToClient;
	ToClient.sin_family = AF_INET;
	ToClient.sin_addr.s_addr = inet_addr(p_sock->ipAddr);
	ToClient.sin_port = p_sock->iPort;

	WORD SendSize = pPacket.m_iLen;
	Send_Size = sendto(ClientSocket, (const char*)pPacket.PrintBuffer(), BUFFER_SIZE, 0, (struct sockaddr*)&ToClient, sizeof(ToClient));

	if (Send_Size == pPacket.m_iLen)
	{
		//HeartBeatTimerReset();
		return true;
	}

	return false;
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
				if (hd.y > 0)
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
						//SendPacket(GAME_COMMAND, (char*)&hd,sizeof(hd));
						turn = RIVAL_TURN;
					}
				}
				break;
			case ESC:
				//	SendPacket(USER_OUT, "",1);
				exit(1);
				break;
			}
			gotoxy(hd.x * 2, hd.y);
		}
	}
}

void GameRoom::SetSocket(SOCKET m_sock)
{
	ClientSocket = m_sock;
}

//void GameRoom::setGame()
//{
//	_tcscpy(rival, match.rivalName);
//
//	if (match.fPlay)
//	{
//		strcpy(my_stone, "●");
//		strcpy(rival_stone, "○");
//		turn = MY_TURN;
//	}
//	else
//	{
//		strcpy(my_stone, "○");
//		strcpy(rival_stone, "●");
//		turn = RIVAL_TURN;
//	}
//}

void GameRoom::RivalStoneInput(int y, int x)
{
	GMap[y][x] = RIVAL_TURN;
	printf("%s", rival_stone);
	checkStone(hd, turn);
	turn = MY_TURN;
}

void GameRoom::RetireWin()
{
	cout << "상대방이 종료했습니다. 5초 후 대기실로 돌아갑니다." << endl;

	Sleep(5000);
	ClearRivalInfo();

}

void GameRoom::ShowGameWaitingRoom(char* title, char* cPlayer)
{
	if (strcmp(this->title, title) != 0)
		strcpy(this->title, title);

	strcpy(player, cPlayer);
	printf("방제 : %s \n", title);
	printf("방장 :\n");
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
	printf("플레이어 : %s", player);

	gotoxy(33, 3);
	printf("상대방 : %s", rival);

	/*if (!(strcmp(rival, "") == 0))
		cout << rival;
*/
	gotoxy(0, 4);
	printf("준비 상태:");
	gotoxy(33, 4);
	printf("준비 상태:");

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

void GameRoom::PlayerReady(bool ready)
{
	if (ready)
	{
		gotoxy(0, 4);
		printf("준비 상태: 준비 완료");
	}
	else
	{
		gotoxy(0, 4);
		printf("준비 상태:                 ");
	}
}

void GameRoom::InsertRivalName(char* rival_name)
{
	strcpy(rival, rival_name);
	gotoxy(33, 3);
	printf("상대방 : %s", rival_name);
}

void GameRoom::ClearRivalInfo()
{
	memset(&RivalPlayer, 0, sizeof(RivalPlayer));
	strcpy(rival, "");
	gotoxy(33, 3);
	printf("상대방 :                           ");

}

void GameRoom::InputChat()
{
	char chat_str[30];
	gotoxy(0, 24);
	for (int i = 0; i < 100; i++)
	{
		printf(" ");
	}
	gotoxy(0, 24);

	printf("채팅 입력:");

	scanf("%s", chat_str);
	
	if (strcmp(chat_str, "#준비완료") == 0)
	{
		PlayerReady(true);
		pPacket.Init();
		pPacket.PutWORD(GAME_ROOM_RIVAL_READY);
		pPacket.ClosePacket();
		SendPacket(RivalPlayer);
	}
	else if (strcmp(chat_str, "#게임시작") == 0)
	{
		pPacket.Init();
		pPacket.PutWORD(GAME_ROOM_START);
		pPacket.ClosePacket();
		SendPacket(RivalPlayer);
	}else
	{
		InsertChat(chat_str);
	}
	//SendPacket(CHATTING,chat_str,strlen(chat_str));

	InputChat();
}

void GameRoom::InsertChat(char* chat_str)
{
	for (int i = 0; i <8; i++)
	{
		chatData[7 - i - 1] = chatData[7 - i];
	}
	chatData[8] = chat_str;

	

	for (int i = 0; i < 8; i++)
	{
		gotoxy(0, 11 + i);
		printf("                                                ");
		gotoxy(0, 11 + i);
		if(strcmp(chatData[i],"") != 0)
		printf("%s", chatData[i]);
	}
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

