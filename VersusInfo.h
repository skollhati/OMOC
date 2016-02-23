#ifndef __VERSUSINFO_H__
#define __VERSUSINFO_H__
#include "main.h"

typedef struct UserInfo
{
	LPTSTR name;
	INT win = 0;
	INT lose = 0;
}USER_INFO;

class VersusInfo
{
public:
	VersusInfo()
	{}

	VersusInfo(LPTSTR U1, LPTSTR U2)
	{
		memccpy(user1.name, U1, 0, _tcslen(U1));
		memccpy(user2.name, U2, 0, _tcslen(U2));
	}

	~VersusInfo()
	{}

public:
	
	USER_INFO getUserInfo(DWORD num) const
	{
		if (num == 1)
			return user1;
		else 
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
