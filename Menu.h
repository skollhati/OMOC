#ifndef __MENU_H__
#define __MENU_H__

#include "main.h"

class Menu
{
public:
	Menu()
	{}

	~Menu()
	{}

public:
	void InitMenu(WORD wOff);
	int ShowMainMenu();
	WORD ShowGameRoom(WORD wTotal);
	char* InputLoginInfo();
	void SendRefreshRoom();
	void ShowGameRoomPage(WORD page);
	void GameRoomSelector(int y);
	char* ShowGameMakeOption();
	void MenuSelector(int y);
	void EraseMenu(int offset);
	SENDING_GAME_ROOM g_List[50]; //구조체 이용하기

private:
	WORD menu_offset;
	WORD g_TotalPage = 0;
public:
	WORD room_num;
	char* room_title;

	
};
#endif  __MENU_H__