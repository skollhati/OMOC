#include "Menu.h"


void Menu::InitMenu()
{
	menu_offset = 3;
}

int Menu::ShowMainMenu()
{
	system("cls");

	cout << "========================================" << endl;
	cout << "============�¶��� ���� ����!============" << endl;
	cout << "========================================" << endl;
	cout << "[��]���� ���� �ϱ�" << endl;
	cout << "[  ]���� ����" << endl;


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

TCHAR* Menu::InputLoginInfo()
{
	TCHAR p_name[50];
	cout << "�������� �Է����ּ��� :";
	_tscanf(_T("%s"), p_name);

	return p_name;
}

WORD* Menu::ShowGameRoom()
{
	WORD roomData[2] = { 0, };

	system("cls");

	menu_offset = 1;
	int page_num = 0;

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
				if (menu_offset < 11)
				{
					EraseMenu(menu_offset);
					menu_offset += 1;
					MenuSelector(menu_offset);
				}
				break;

			case RIGHT:
				if (page_num < g_roomTotal)
				{
					system("cls");
					page_num++;
					ShowGameRoomPage(page_num);
				}
				break;

			case LEFT:
				if (page_num > 1)
				{
					system("cls");
					page_num--;
					ShowGameRoomPage(page_num);
				}
				break;

			case REFRESH:
				roomData[0] = 100;
				roomData[1] = 0;
				return roomData;
				break;

			case SPACE:
				roomData[0] = page_num;
				roomData[1] = menu_offset;
				return roomData;
				break;
			}
		}
	}
}

void Menu::ShowGameRoomPage(WORD page)
{
	cout << "===============================���� ���===============================" << endl;

	if (page == 0 && _tcscmp(g_List[0], _T("")) == 0)
	{
		cout << "������ �������� �ʽ��ϴ�." << endl;
	}
	else {


		for (int i = page; i < page + 10; i++)
		{
			cout << "[  ]" << g_List[page - 1] << endl;
		}


	}
	cout << "===============================[" << page + 1 << "/" << g_roomTotal << "]===============================" << endl;
	cout << "1 : �� ����� /SPACE : ���� / ��� : �� ���� /�� �� : ������ ��ȯ / 5 : ���� ��ħ /ESC : ����" << endl;
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






