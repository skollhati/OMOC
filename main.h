#ifndef __MAIN_H__
#define __MAIN_H__


#include <WinSock2.h>

#include <stdio.h>
#include<Windows.h>
#include<process.h>
#include<CommCtrl.h>
#include<stdlib.h>
#include<mmsystem.h>
#include<time.h>
#include<tchar.h>
#include<iostream>
#include<vector>
#include<conio.h>


using namespace std;
typedef struct XY {
	int x;
	int y;
}xy;


typedef struct SOCKET_DATA
{
	WORD wUserNum;
	char ipAddr[30];
	int iPort;
	int time;
	bool bOnOff;
}*PSOCKET_OBJ;


#endif