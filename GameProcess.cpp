#include "GameProcess.h"

void GameProcess::gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

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

GameProcess::GameProcess(HANDLE* p_hSend)
{
	hSend = p_hSend;

	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	_tprintf(_T("�ڽ��� �г����� �Է��ϼ��� :"));
	_tscanf(_T("%s"), player);
	menu();

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
					printf("��");
				else if (k + 1 == MAP_X)
					printf("��");
				else
					printf("��");
			}
			else if (i + 1 < MAP_Y)
			{
				if (k == 0)
					printf("��");
				else if (k + 1 == MAP_X)
					printf("��");
				else
					printf("��");
			}
			else
			{
				if (k == 0)
					printf("��");
				else if (k + 1 == MAP_X)
					printf("��");
				else
					printf("��");
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
			printf("���� �¸��ϼ̽��ϴ�.\n");
			getch();
			
			//searchstone �Լ� ������ �������� ó���ϴ� ������� �ٲ� ��

				
			Sleep(2000);
			menu();
			//exit(1);
		}
	}
}

void GameProcess::SendEvent(WORD com, TCHAR* buf)
{
	UNPACK_DATA* unpack_data;
	unpack_data->com = com;
	_tcscpy(unpack_data->buf, buf);
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
						//m_pNetProc->SendPacket(GAME_COMMAND,(TCHAR*)&hd);
						turn = RIVAL_TURN;
					}
				}
				break;
			case ESC:
				SendEvent(USER_OUT, NULL);

				//m_pNetProc->SendPacket(USER_OUT, NULL);
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
	printf("> 2�ο� ���� ���� \n");
	printf("> Key - ����Ű, �����̽�\n");
	printf("	  - ����(ESC)\n\n");
	printf("������ �����Ϸ��� �ƹ�Ű�� ��������");
	getch();
	system("cls");
	SendEvent(USER_IN, player);
	//m_pNetProc->SendPacket(USER_IN, player);

	_tprintf(_T("���� ��븦 ��ٸ��ϴ�....\n"));
	WaitForSingleObject(hEvent, INFINITE);

	_tprintf(_T("��Ī �Ϸ�!! 5�� �� ������ �����մϴ�!\n"));

	int GMap[MAP_Y][MAP_X] = { 0, };
	initGame();

	Sleep(5000);

	startGame();
}

void GameProcess::WaitingRival()
{

}

void GameProcess::setGame(MATCHING match)
{
	_tcscpy(rival, match.rivalName);

	if (match.fPlay)
	{ 
		strcpy(my_stone,"��");
		strcpy(rival_stone, "��");
		turn = MY_TURN;
	}
	else
	{ 
		strcpy(my_stone, "��");
		strcpy(rival_stone, "��");
		turn = RIVAL_TURN;
	}
}