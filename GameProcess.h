#ifndef __GAMEPROCESS_H__
#define __GAMEPROCESS_H__

//---------�� �͵�-----------
//3.Į��Ǯ
//4.UDP
//4.�Ѹ� ���� ����� ������ ��(heartbeat)
//5.������ ���� ���

#include "main.h"
#include "VersusInfo.h"

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


using namespace std;



class GameProcess {

public:

	GameProcess()
	{
		TCHAR uName1[100];
		TCHAR uName2[100];
		
		_tprintf(_T("user1 name:"));
		_tscanf(_T("%s"), uName1);
		_tprintf(_T("user2 name:"));
		_tscanf(_T("%s"), uName2);

		_tprintf(_T("user1 : %s user2 : %s\n"),uName1,uName2);


		vInfo = new VersusInfo(uName1);
		menu();

	}

	~GameProcess()
	{}

public:
	void gotoxy(int x, int y);
	void setTextColor(COLORREF color);
	void initGame();
	void checkStone(xy hd, int GMap[MAP_Y][MAP_X], int turn);
	void startGame(int GMap[MAP_Y][MAP_X]);
	int searchStone(xy hd, int GMap[MAP_Y][MAP_X], int, int, int);
	
	void insertUser();
	
	void menu()
	{
		printf("> 2�ο� ���� ���� \n");
		printf("> Key - ����Ű, �����̽�\n");
		printf("	  - ����(ESC)\n\n");
		printf("������ �����Ϸ��� �ƹ�Ű�� ��������");
		getch();
		system("cls");

		int GMap[MAP_Y][MAP_X] = { 0, };
		initGame();
		startGame(GMap);
	}

private:
	char cmd[256] = "\0";
	VersusInfo* vInfo;
};

#endif // !__GAMEPROCESS_H__
