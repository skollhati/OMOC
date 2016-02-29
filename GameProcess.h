#ifndef __GAMEPROCESS_H__
#define __GAMEPROCESS_H__

//---------�� �͵�-----------
//3.Į��Ǯ
//4.UDP
//4.�Ѹ� ���� ����� ������ ��(heartbeat)
//5.������ ���� ���

#include "main.h"
#include "NetworkProcess_UDP.h"

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32
#define MAP_X 39
#define MAP_Y 24
#define ESC 27
#define MY_TURN 1
#define RIVAL_TURN 2



using namespace std;



class GameProcess {

public:
	GameProcess();
	

	//GameProcess(NetWorkProcess_UDP* pNetProc);

	~GameProcess()
	{}

public:
	void gotoxy(int x, int y);
	void setTextColor(COLORREF color);
	void initGame();
	void checkStone(xy hd, int turn);
	void startGame();
	void setGame(MATCHING match);
//	void setNetworkProc(NetWorkProcess_UDP* pNetProc );
	void RivalStoneInput(int y, int x);
	void WaitingRival();
	int searchStone(xy hd, int, int, int);
	

	
	
	void menu();

public:
	
	HANDLE hEvent;
	char my_stone[3];
	char rival_stone[3];

	NetWorkProcess_UDP* m_pNetProc;

private:
	
	int GMap[MAP_Y][MAP_X];
	char cmd[256] = "\0";
	int turn = 0;
	xy hd;

	

	TCHAR player[50];
	TCHAR rival[50];
	//VersusInfo* vInfo;
};

#endif // !__GAMEPROCESS_H__
