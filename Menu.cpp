#include "Menu.h"


void Menu::InitMenu(WORD wOff)
{
	menu_offset = wOff;
}

int Menu::ShowMainMenu()
{
	//system("cls");

	printf("========================================\n");
	printf("============온라인 오목 대전!===========\n");
	printf("========================================\n");
	printf("[●]서버 접속 하기\n");
	printf("[  ]게임 종료\n");

	char ip = '\0';
	while (1)
	{
		if (kbhit())
		{
			ip = getch();
			switch (ip)
			{
			case UP:
				if (menu_offset > 3)
				{
					EraseMenu(menu_offset);
					menu_offset -= 1;
					MenuSelector(menu_offset);
				}
				break;

			case DOWN:
				if (menu_offset < 4)
				{
					EraseMenu(menu_offset);
					menu_offset += 1;
					MenuSelector(menu_offset);
				}
				break;
			case SPACE:
				return menu_offset;
				break;
			}
		}
	}

}

char* Menu::InputLoginInfo()
{
	char* p_name = new char[20];
	printf("유저명을 입력해주세요 :");
	scanf("%s", p_name);
	
	return p_name;
}

WORD Menu::ShowGameRoom(WORD wTotal)
{
	
	room_num = 0;
	//system("cls");
	WORD page_num = 0;
	menu_offset = 1;

	g_TotalPage = wTotal / 5;

	if (wTotal % 5 != 0)
		g_TotalPage++;

	if (wTotal != 0)
		page_num++;
	
	ShowGameRoomPage(page_num);
	
	char ip = '\0';
	while (1)
	{
		if (kbhit())
		{
			ip = getch();
			switch (ip)
			{
			case UP:
				if (menu_offset > 1)
				{
					EraseMenu(menu_offset);
					menu_offset -= 1;
					MenuSelector(menu_offset);
				}
				break;

			case DOWN:
				if (menu_offset < 5)
				{
					EraseMenu(menu_offset);
					menu_offset += 1;
					MenuSelector(menu_offset);
				}
				break;

			case RIGHT:
				if (page_num < g_TotalPage)
				{
					system("cls");
					InitMenu(2);
					page_num++;
					ShowGameRoomPage(page_num);
				}
				break;

			case LEFT:
				if (page_num > 1)
				{
					system("cls");
					InitMenu(2);
					page_num--;
					ShowGameRoomPage(page_num);
				}
				break;

			case ESC:
			
				return ESC;
				break;

			case SPACE:
				room_num = g_List[((page_num - 1) * 5) + (menu_offset - 2)].game_number;
				strcpy(room_title, g_List[((page_num - 1) * 5) + (menu_offset - 2)].title);
				return SPACE;
				break;

			case NUMBER_ONE:
				return NUMBER_ONE;
				break;

			case NUMBER_FIVE:
				return NUMBER_FIVE;
				break;
			}
		}
	}
}



char* Menu::ShowGameMakeOption()
{
	char title[30];
	system("cls");
	printf("==============================게임 생성=============================\n");
	printf("게임 방제 :");
	//방제 입력받기
	scanf("%s",title);

	return title;
}



void Menu::ShowGameRoomPage(WORD page)
{
	system("cls");


	printf("==============================게임 목록=============================\n");

	if (page == 0)
	{
		printf("게임이 존재하지 않습니다.\n");
	}
	else {


		for (int i = (page-1)*5; i < page * 5; i++)
		{
			if(g_List[i].game_number != 999)
			printf( "[  ] %d번방 %s \n", g_List[i].game_number+1,g_List[i].title);
		}
	}
	

	printf("===============================[%d /%d]===============================\n", page, g_TotalPage);
	printf("1 : 방 만들기 /SPACE : 입장 / ↑↓ : 방 선택 /← → : 페이지 전환 / \n 5 : 새로 고침 /ESC : 종료");
	
	
	char ip = '\0';

	
}



void Menu::EraseMenu(int offset)
{
	COORD pos = { 1,offset };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf(" ");

}

void Menu::MenuSelector(int y)
{
	COORD pos = { 1,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("●");
}






