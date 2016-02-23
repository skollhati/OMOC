#ifndef __GAMEPROCESS_H__
#define __GAMEPROCESS_H__

#include "main.h"

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32
#define MAP_X 39
#define MAP_Y 24
#define ESC 27
#define U1 1
#define U2 2

typedef struct XY {
	int x;
	int y;
}xy;

class GameProcess {

public:
	GameProcess()
	{
		menu();
	}

	~GameProcess()
	{}

public:
	void gotoxy(int x, int y);
	void initGame();
	void checkStone(xy hd, int GMap[MAP_Y][MAP_X], int turn);
	void startGame(int GMap[MAP_Y][MAP_X]);
	int searchStone(xy hd, int GMap[MAP_Y][MAP_X], int, int, int);

	void menu()
	{
		printf("> 2인용 오목 게임 \n");
		printf("> Key - 방향키, 스페이스\n");
		printf("	  - 종료(ESC)\n\n");
		printf("게임을 시작하려면 아무키나 누르세요");
		getch();
		system("cls");

		int GMap[MAP_Y][MAP_X] = { 0, };
		initGame();
		startGame(GMap);
	}

private:
	char cmd[256] = "\0";

};

#endif // !__GAMEPROCESS_H__
