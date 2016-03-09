#ifndef __GAMEROOM_H__
#define __GAMEROOM_H__

#include "main.h"
#include "NetworkProcess_UDP.h"

class GameRoom
{
public :
	GameRoom()
	{}

	~GameRoom()
	{}


public:
	BOOL SendPacket(WORD com, TCHAR* Buffer);
	void JoinRival(TCHAR* player_name);
	void ChangeUserState(TCHAR* player, bool b_ready);
	void SetSocket(SOCKET m_sock);
	void DrawGameRoom();
	void JoinGameRoomSocket(short port, char* ip_addr,SOCKET client_sock);
	void ChatArea(TCHAR* chatData);
	
	//게임 플레이 관련 함수
	void gotoxy(int x, int y);
	void checkStone(xy hd, int turn);
	void initGame();
	void startGame();
	void setGame(MATCHING match);
	void RivalStoneInput(int y, int x);
	int searchStone(xy hd, int, int, int);
	void UDPRecive(TCHAR* buffer, WORD wSize);
	void RetireWin();
	void RivalOutWaitingRoom();
	void ShowChatFrame();
	void InputChat();
	void ShowGameWaitingRoom(TCHAR* title);
	void InsertRivalName(TCHAR* rival_name);
	void ClearRivalInfo();


private:
	int turn = 0;
	int GMap[MAP_Y][MAP_X];
	char my_stone[3];
	char rival_stone[3];
	PacketSet pPacket;
	TCHAR rival[50];
	BOOL GameMaster;
	TCHAR* title;
	SOCKET ClientSocket;
	SOCKADDR_IN ToRival;
	WORD Send_Size;
	xy hd;
	TCHAR player[50];
};
#endif