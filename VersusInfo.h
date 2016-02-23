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

	VersusInfo(TCHAR U1[], TCHAR U2[])
	{
		_tcscpy(user1.name, U1);
		_tcscpy(user2.name, U2);

		_tprintf(_T(" test :%s\n"), user1.name);
		_tprintf(_T("%s\n"), user2.name);
	}

	~VersusInfo()
	{}

public:
	
	USER_INFO getUserInfo(DWORD num) const
	{
		if (num == 1)
			return user1;
		else if (num == 2)
			return user2;

	}

	void setVersusUpdate(bool vRecord)
	{
		if(vRecord)
		{
			user1.win++;
			user2.lose++;
		}
		else
		{
			user2.win++;
			user1.lose++;
		}
	}

private:
	USER_INFO user1, user2;
};

#endif // !__VERSUSINFO_H__
