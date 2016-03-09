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
	virtual void UDPRecive(TCHAR* buffer, WORD wSize);
	void MenuSelected(int n_menu);
	void GameSelected(WORD* room_data);
	void GameRoomProc(WORD* select_num);
	void MakeGameRoom(TCHAR* title);
	void JoinWaitGameRoom(TCHAR* title,short port,char* ip_addr);
	void ShowGameList();
	void InsertGameList(PacketSet p_Packet);
public:
	HANDLE hEvent;
	Menu g_menu;
private:
	bool myPlayState = false;
	gRoomData gRoomList[50];
	GameRoom gRoom;
	
	char cmd[256] = "\0";
	WORD wTotalCount;
	WORD wReceiveCount = 0;
};

#endif // !__GAMEPROCESS_H__
