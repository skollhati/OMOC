#ifndef __GAMEPROCESS_H__
#define __GAMEPROCESS_H__

//---------�� �͵�-----------
//3.Į��Ǯ
//4.UDP
//4.�Ѹ� ���� ����� ������ ��(heartbeat)
//5.������ ���� ���

#include "main.h"



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
	GameProcess(HANDLE* p_hSend);
	

	//GameProcess(NetWorkProcess_UDP* pNetProc);

	~GameProcess()
	{}

public:
	void RetireWin();
	void gotoxy(int x, int y);
	void setTextColor(COLORREF color);
	void initGame();
	static UINT WINAPI WaittingTimer(LPVOID lpParam);
	void checkStone(xy hd, int turn);
	void startGame();
	void setGame(MATCHING match);
	void RivalStoneInput(int y, int x);
	void WaitingRival();
	int searchStone(xy hd, int, int, int);
	void menu();
	void RematchMenu();
	void SendEvent(WORD com, TCHAR* buf);
public:

	HANDLE *hSend;
	HANDLE hEvent;
	char my_stone[3];
	char rival_stone[3];
	queue<UNPACK_DATA*> q_SendData;
	

private:
	
	int GMap[MAP_Y][MAP_X];
	char cmd[256] = "\0";
	int turn = 0;

	xy hd;
	TCHAR player[50];
	TCHAR rival[50];

};

#endif // !__GAMEPROCESS_H__
