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
	void InitMenu();
	int ShowMainMenu();
	
	WORD* ShowGameRoom();
	TCHAR* InputLoginInfo();

	void ShowGameRoomPage(WORD page);
	void GameRoomSelector(int y);
	void MenuSelector(int y);
	void EraseMenu(int offset);

private:
	WORD menu_offset;
	WORD g_roomTotal = 0;
	TCHAR g_List[50][50];
};
#endif  __MENU_H__