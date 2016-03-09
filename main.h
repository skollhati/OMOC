#ifndef __MAIN_H__
#define __MAIN_H__
#include "locale.h"


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
#include <queue>

#define USER_IN 1	
#define LOGIN_OK 2				//서버 접속에 사용
#define USER_OUT 4				
#define HEARTBEAT 5				//접속 중임을 주기적으로 알림

#define GAME_RETIRE 12
#define CHATTING 21


#define GAME_COMMAND 100		//돌의 움직임을 알림
#define GAME_REMATCH 101	    //게임 재경기 알림 ( 양쪽 모드 TRUE) 를 전송해야 리매치 성사
#define GAME_RESULT 102			//게임 결과 알림

#define GAME_ROOM_LIST 200
#define GAME_ROOM_LIST_HEAD 211
#define GAME_ROOM_LIST_BODY 212

#define GAME_ROOM_SELECTED 202
#define GAME_ROOM_REFRESH 203
#define GAME_ROOM_RIVAL_READY 204
#define GAME_ROOM_RIVAL_UNREADY 205

#define GAME_ROOM_START 210

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32
#define MAP_X 39
#define MAP_Y 24
#define ESC 27
#define MY_TURN 1
#define RIVAL_TURN 2
#define MAKE 49
#define REFRESH 53



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

typedef struct GAME_ROOM_DATA
{
	WORD roomNum;
	TCHAR title[50];
}gRoomData;
typedef struct UNPACK_DATA
{
	WORD com;
	TCHAR buf[50];
};

#endif