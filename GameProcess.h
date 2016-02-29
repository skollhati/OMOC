#ifndef __GAMEPROCESS_H__
#define __GAMEPROCESS_H__

//---------할 것들-----------
//3.칼라풀
//4.UDP
//4.한명 연결 종료시 종료할 것(heartbeat)
//5.비정상 종료 대비

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

	GameProcess()
	{
	/*	TCHAR uName1[100];
		TCHAR uName2[100];
		
		_tprintf(_T("user1 name:"));
		_tscanf(_T("%s"), uName1);
		_tprintf(_T("user2 name:"));
		_tscanf(_T("%s"), uName2);

		_tprintf(_T("user1 : %s user2 : %s\n"),uName1,uName2);


		vInfo = new VersusInfo(uName1);*/
		hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

		_tprintf(_T("자신의 닉네임을 입력하세요 :"));
		_tscanf(_T("%s"), player);
		menu();

	}

	~GameProcess()
	{}

public:
	void gotoxy(int x, int y);
	void setTextColor(COLORREF color);
	void initGame();
	void checkStone(xy hd, int turn);
	void startGame();
	void setGame(MATCHING match);
	void setNetworkProc(NetWorkProcess_UDP* pNetProc );
	void RivalStoneInput(int y, int x);
	void WaitingRival();
	int searchStone(xy hd, int, int, int);
	

	void insertUser();
	
	void menu()
	{
		printf("> 2인용 오목 게임 \n");
		printf("> Key - 방향키, 스페이스\n");
		printf("	  - 종료(ESC)\n\n");
		printf("게임을 시작하려면 아무키나 누르세요");
		getch();
		system("cls");
		
		m_pNetProc->SendPacket(USER_IN,player);
		
		_tprintf(_T("대전 상대를 기다립니다....\n"));
		m_pNetProc->ReceivePacket();
		WaitForSingleObject(hEvent,INFINITE);
		
		_tprintf(_T("매칭 완료!! 5초 후 게임을 시작합니다!\n"));
		
		int GMap[MAP_Y][MAP_X] = { 0, };
		initGame();
		
		Sleep(5000);
		
		startGame();
	}

public:
	
	HANDLE hEvent;
	char my_stone[3];
	char rival_stone[3];

private:
	
	int GMap[MAP_Y][MAP_X];
	char cmd[256] = "\0";
	int turn = 0;
	xy hd;
	NetWorkProcess_UDP* m_pNetProc;
	TCHAR player[50];
	TCHAR rival[50];
	//VersusInfo* vInfo;
};

#endif // !__GAMEPROCESS_H__
