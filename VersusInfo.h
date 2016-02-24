#ifndef __VERSUSINFO_H__
#define __VERSUSINFO_H__
#include "main.h"

typedef struct UserInfo
{
	TCHAR name[100];
	INT win = 0;
	INT lose = 0;
}USER_INFO;

class VersusInfo
{

public:
	VersusInfo()
	{}

	VersusInfo(TCHAR uName[])
	{
		_tcscpy(user.name, uName);
	}

	~VersusInfo()
	{}

public:
	
	USER_INFO getUserInfo(DWORD num) const
	{

		return user;
	}

	void setVersusUpdate(bool vRecord)
	{
		if(vRecord)
		{
			user.win++;
		}
		else
		{
			user.lose++;
		}
	}

private:
	USER_INFO user;
};

#endif // !__VERSUSINFO_H__
