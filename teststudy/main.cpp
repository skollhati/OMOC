#include <iostream>
#include <Windows.h>
#include <tchar.h>


#define STRING_LEN 100


using namespace std;

void setTextColor(COLORREF color)
{
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFOEX csbi;

	csbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(hConsoleOutput, &csbi);

	csbi.ColorTable[1] = color;

	SetConsoleScreenBufferInfoEx(hConsoleOutput, &csbi);
	SetConsoleTextAttribute(hConsoleOutput, 1);
}

int func(int a)
{
	return a * 2;
}

int _tmain(int argc, TCHAR* argv[])
{
	int i;
	int(*pf)(int);
	pf = func;
	i = (*pf)(30);
	printf("%d", i);

}