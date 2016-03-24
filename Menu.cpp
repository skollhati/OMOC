#include "Menu.h"


void Menu::InitMenu(WORD wOff)
{
	menu_offset = wOff;
}

int Menu::ShowMainMenu()
{
	//system("cls");

	printf("========================================\n");
	printf("============�¶��� ���� ����!===========\n");
	printf("========================================\n");
	printf("[��]���� ���� �ϱ�\n");
	printf("[  ]���� ����\n");

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
	printf("�������� �Է����ּ��� :");
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
	printf("==============================���� ����=============================\n");
	printf("���� ���� :");
	//���� �Է¹ޱ�
	scanf("%s",title);

	return title;
}



void Menu::ShowGameRoomPage(WORD page)
{
	system("cls");


	printf("==============================���� ���=============================\n");

	if (page == 0)
	{
		printf("������ �������� �ʽ��ϴ�.\n");
	}
	else {


		for (int i = (page-1)*5; i < page * 5; i++)
		{
			if(g_List[i].game_number != 999)
			printf( "[  ] %d���� %s \n", g_List[i].game_number+1,g_List[i].title);
		}
	}
	

	printf("===============================[%d /%d]===============================\n", page, g_TotalPage);
	printf("1 : �� ����� /SPACE : ���� / ��� : �� ���� /�� �� : ������ ��ȯ / \n 5 : ���� ��ħ /ESC : ����");
	
	
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
	printf("��");
}






