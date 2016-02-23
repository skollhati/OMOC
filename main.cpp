#include"GameProcess.h"

char cmd[256] = "\0";

//���� �ҽ�


typedef struct XY {
	int x;
	int y;
}xy;

void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void initGame()
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


		printf("\n");
	}
}

int searchStone(xy hd, int GMap[MAP_Y][MAP_X], int flag, int p, int sw)
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
	return 1 + searchStone(hd, GMap, flag, p, sw);
}

void checkStone(xy hd, int GMap[MAP_Y][MAP_X], int turn)
{
	int i = 0, countStone = 0;
	for (i = 0; i < 4; i++)
	{
		countStone = 0;
		countStone += searchStone(hd, GMap, turn, i, 1);
		countStone += searchStone(hd, GMap, turn, i, -1);
		
		if (countStone == 6)
		{
			gotoxy(0, MAP_Y);
			if (turn == U1)
				printf("����� 1");
			else
				printf("����� 2");

			printf("���� �¸��ϼ̽��ϴ�.");
			getch();
			exit(1);
		}
	}
}


void startGame(int GMap[MAP_Y][MAP_X])
{
	char ip = '\0';
	int turn = U1;
	
	xy hd = { MAP_X / 2,MAP_Y / 2 };
	
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

					if (turn == U1)
					{
						GMap[hd.y][hd.x] = U1;
						printf("��");
						checkStone(hd, GMap, turn);
						turn = U2;
					}
					else
					{
						GMap[hd.y][hd.x] = U2;
						printf("��");
						checkStone(hd, GMap, turn);
						turn = U1;
					}
				}
				break;
			case ESC:
				exit(1);
				break;
			}
			gotoxy(hd.x * 2, hd.y);
		}
	}
}

//���� �ҽ�

int _tmain(int argc, char* argv[])
{
	int a = 1;
	int x = 0;
	int i;
	//---------------------------���� �ҽ�------------------------
	int GMap[MAP_Y][MAP_X] = { 0, };
	printf("> 2�ο� ���� ���� \n");
	printf("> Key - ����Ű, �����̽�\n");
	printf("	  - ����(ESC)\n\n");
	printf("������ �����Ϸ��� �ƹ�Ű�� ��������");
	getch();
	system("cls");
	initGame();
	startGame(GMap);

	Sleep(3000);
	return 0;


}