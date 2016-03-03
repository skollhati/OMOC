#include "GameProcess.h"

void GameProcess::gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

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

GameProcess::GameProcess(HANDLE* p_hSend)
{
	hSend = p_hSend;

	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	_tprintf(_T("자신의 닉네임을 입력하세요 :"));
	_tscanf(_T("%s"), player);
	menu();

}

void GameProcess::initGame()
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

int GameProcess::searchStone(xy hd, int flag, int p, int sw)
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

void GameProcess::checkStone(xy hd,  int turn)
{
	int i = 0, countStone = 0;
	for (i = 0; i < 4; i++)
	{
		countStone = 0;
		countStone += searchStone(hd, turn, i, 1);
		countStone += searchStone(hd,  turn, i, -1);

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
			
			//searchstone 함수 연산을 서버에서 처리하는 방식으로 바꿀 것

				
			Sleep(2000);
			RematchMenu();
			//exit(1);
		}
	}
}

void GameProcess::RematchMenu()
{
	char com;
	cout << "(미입력시 10초 후 자동으로 종료됩니다.)" << endl;
	cout << "동일 상대와 다시 경기를 하시겠습니까? (y/n):";
	HANDLE hWTimer = (HANDLE)_beginthreadex(NULL, 0, GameProcess::WaittingTimer, (LPVOID)this, 0, NULL);
	
	cin >> com;

	if (com == 'y')
	{
		SuspendThread(hWTimer);
		GetExitCodeThread(hWTimer, NULL);
		initGame();
		SendEvent(GAME_REMATCH, _T("1"));
		CloseHandle(hWTimer);
		cout << "재경기를 선택하셨습니다. 상대방을 기다립니다." << endl;
	}
	else if (com == 'n')
	{
		SuspendThread(hWTimer);
		GetExitCodeThread(hWTimer, NULL);
		cout << "경기 포기를 선택하셨습니다. 메뉴로 이동합니다." << endl;
		SendEvent(GAME_REMATCH, _T("0"));
		CloseHandle(hWTimer);
		menu();
		
	}
	else
	{
		
		SuspendThread(hWTimer); 
		GetExitCodeThread(hWTimer, NULL);
		cout << "올바른 입력이 아닙니다 다시 입력해 주십시오" << endl;
		CloseHandle(hWTimer);
		RematchMenu();
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
			pGP->SendEvent(GAME_REMATCH, _T("0"));
		}
	}
	
	return 0;
}

void GameProcess::SendEvent(WORD com, TCHAR* buf)
{
	UNPACK_DATA* unpack_data = new UNPACK_DATA();
	unpack_data->com = com;
	try {
		_tcscpy(unpack_data->buf, buf);
	}
	catch (exception e)
	{
		printf("%s", e);
	}
	this->q_SendData.push(unpack_data);
	SetEvent(*hSend);
}

void GameProcess::startGame()
{
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
						printf("%s",my_stone);
						checkStone(hd, turn);
						SendEvent(GAME_COMMAND, (TCHAR*)&hd);
						turn = RIVAL_TURN;
					}
				}
				break;
			case ESC:
				SendEvent(USER_OUT, NULL);
				exit(1);
				break;
			}
			gotoxy(hd.x * 2, hd.y);
		}
	}
}

void GameProcess::RivalStoneInput(int y ,int x)
{
	GMap[y][x] = RIVAL_TURN;
	printf("%s",rival_stone);
	checkStone(hd, turn);
	turn = MY_TURN;
}


void GameProcess::menu()
{
	printf("> 2인용 오목 게임 \n");
	printf("> Key - 방향키, 스페이스\n");
	printf("	  - 종료(ESC)\n\n");
	printf("게임을 시작하려면 아무키나 누르세요");

	getch();
	system("cls");
	SendEvent(USER_IN, player);
	//m_pNetProc->SendPacket(USER_IN, player);

	_tprintf(_T("대전 상대를 기다립니다....\n"));
	WaitForSingleObject(hEvent, INFINITE);

	_tprintf(_T("매칭 완료!! 5초 후 게임을 시작합니다!\n"));

	
	initGame();

	Sleep(5000);

	startGame();
}

void GameProcess::RetireWin()
{
	cout << "상대방이 종료했습니다. 5초후 메뉴로 돌아갑니다." << endl;

	Sleep(5000);
	menu();

}

void GameProcess::WaitingRival()
{
	_tprintf(_T("상대방을 기다리는 중입니다."));
}

void GameProcess::setGame(MATCHING match)
{
	_tcscpy(rival, match.rivalName);

	if (match.fPlay)
	{ 
		strcpy(my_stone,"●");
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