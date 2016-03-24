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
	BOOL SendPacket(PSOCKET_OBJ p_sock);
	void JoinRival(char* player_name);
	void ChangeUserState(char* player, bool b_ready);
	void SetSocket(SOCKET m_sock);
	void DrawGameRoom();
	void JoinGameRoomSocket(short port, char* ip_addr);
	void ChatArea(char* chatData);
	void InsertChat(char* chat_str);
	//게임 플레이 관련 함수
	void gotoxy(int x, int y);
	void checkStone(xy hd, int turn);
	void initGame();
	void startGame();
	void setGame();
	void RivalStoneInput(int y, int x);
	int searchStone(xy hd, int, int, int);
	void RetireWin();
	void RivalOutWaitingRoom();
	void ShowChatFrame();
	void InputChat();
	void ShowGameWaitingRoom(char* title,char* cPlayer);
	void InsertRivalName(char* rival_name);
	void ClearRivalInfo();
	void PlayerReady(bool ready);
public:
	PSOCKET_OBJ RivalPlayer;


private:
	int turn = 0;
	int GMap[MAP_Y][MAP_X];
	char my_stone[3];
	char rival_stone[3];
	PacketSet pPacket;
	BOOL GameMaster;
	char title[30];
	SOCKET ClientSocket;
	char player[30];
	WORD Send_Size;
	xy hd;
	char rival[30]="\0";
	char* chatData[8];
};
#endif