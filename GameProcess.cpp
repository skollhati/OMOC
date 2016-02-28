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

void GameProcess::initGame()
{
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
			menu();
			//exit(1);
		}
	}
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
						m_pNetProc->SendPacket(GAME_COMMAND,(TCHAR*)&hd);
						turn = RIVAL_TURN;
					}
				}
				break;
			case ESC:
				m_pNetProc->SendPacket(USER_OUT, NULL);
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

void GameProcess::setNetworkProc(NetWorkProcess_UDP* pNetProc)
{
	m_pNetProc = pNetProc;
}

void GameProcess::WaitingRival()
{

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