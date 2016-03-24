#ifndef __GAMEPROCESS_H__
#define __GAMEPROCESS_H__

//---------할 것들-----------
//3.칼라풀
//4.UDP
//4.한명 연결 종료시 종료할 것(heartbeat)
//5.비정상 종료 대비

#include "main.h"
#include "NetworkProcess_UDP.h"
#include "Menu.h"
#include "GameRoom.h"




using namespace std;



class GameProcess :NetWorkProcess_UDP{

public:
	//GameProcess(BOOL(*pSend)(WORD, TCHAR*));
	GameProcess();
	

	//GameProcess(NetWorkProcess_UDP* pNetProc);

	~GameProcess()
	{}

public:

	void setTextColor(COLORREF color);
	static UINT WINAPI WaittingTimer(LPVOID lpParam);
	void UDPRecive(char* buffer);
	void MenuSelected(int n_menu);
	void GameSelected(WORD room_data);
	void GameRoomProc(WORD select_num);
	void MakeGameRoom(char* title);
	void JoinWaitGameRoom(char* title,short port,char* ip_addr);
	void InsertGameList();
	void NetworkThread();
	void RoomProcess(WORD task_num);
	void StartClient();
	static UINT WINAPI ReceiveThread(LPVOID lpParam);

public:
	HANDLE hEvent;
	Menu g_menu;
private:
	PSOCKET_OBJ HOST;

	bool myPlayState = false;
	SENDING_GAME_ROOM gRoomList[50];
	GameRoom gRoom;
	WORD offset=0;
	char cmd[256] = "\0";
	char player_name[30];
	WORD wTotalCount;
	WORD wReceiveCount = 0;
};

#endif // !__GAMEPROCESS_H__
