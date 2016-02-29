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

		_tprintf(_T("�ڽ��� �г����� �Է��ϼ��� :"));
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
		printf("> 2�ο� ���� ���� \n");
		printf("> Key - ����Ű, �����̽�\n");
		printf("	  - ����(ESC)\n\n");
		printf("������ �����Ϸ��� �ƹ�Ű�� ��������");
		getch();
		system("cls");
		
		m_pNetProc->SendPacket(USER_IN,player);
		
		_tprintf(_T("���� ��븦 ��ٸ��ϴ�....\n"));
		m_pNetProc->ReceivePacket();
		WaitForSingleObject(hEvent,INFINITE);
		
		_tprintf(_T("��Ī �Ϸ�!! 5�� �� ������ �����մϴ�!\n"));
		
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
