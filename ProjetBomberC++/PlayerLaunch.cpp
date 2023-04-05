#include "PlayerLaunch.h"
#include "Host.h"
#include"Client.h"
void PlayerLaunch::initposPlayer(Host& _host, Client& _client)
{
	int a = 0; int total = 0;
	auto i = _host.listClients.begin(); auto n = _host.listClients.end();
	while (i!=n)
	{
		bool Complete = false;
		a = tools::iRand2(0, 8);
		while (!Complete)
		{
			bool check = false;
			auto j = listZone.begin(); auto q = listZone.end();
			while (j != q)
			{
				if (a == (*j)) check = true;
				j++;
			}
			if (check == false)
			{
				Complete = true; listZone.push_back(a);
			}
			else if (a < 8) a++;
			else a = 0;
		}
		
		getPos(a);
		_client.initPos(pos, (*i)->id);
		total++;
		i++;
	}
}

void PlayerLaunch::getPos(int& zone)
{
	int a = 0;
	a = tools::iRand2(1, 3);
	switch (zone)
	{
	case 0:
		if (a == 1)pos = { 380,300 };
		if (a == 2)pos = { 422, 1305 };
		if (a == 3)pos = { 620,510 };
		break;
	case 1:
		if (a == 1)pos = { 860, 315 };
		if (a == 2)pos = { 1450,465 };
		if (a == 3)pos = { 1065,1185 };
		break;
	case 2:
		if (a == 1)pos = { 1816,400 };
		if (a == 2)pos = { 2470, 625 };
		if (a == 3)pos = { 2265,1535 };
		break;
	case 3:
		if (a == 1)pos = { 1045,820 };
		if (a == 2)pos = { 1147, 1860 };
		if (a == 3)pos = { 1810,1678 };
		break;
	case 4:
		if (a == 1)pos = { 2065,1500 };
		if (a == 2)pos = { 2170, 1870 };
		if (a == 3)pos = { 3645,2030 };
		break;
	case 5:
		if (a == 1)pos = { 2115,1755 };
		if (a == 2)pos = { 2157, 1937 };
		if (a == 3)pos = { 2845,1640 };
		break;
	case 6:
		if (a == 1)pos = { 645,2800 };
		if (a == 2)pos = { 470, 2800 };
		if (a == 3)pos = { 370,3300 };
		break;
	case 7:
		if (a == 1)pos = { 2920,2240 };
		if (a == 2)pos = { 1500, 2800 };
		if (a == 3)pos = { 1690, 2260 };
		break;
	case 8:
		if (a == 1)pos = { 4500,4525 };
		if (a == 2)pos = { 4020, 3879 };
		if (a == 3)pos = { 3365,3325 };
		break;
	default:
		break;
	}
}
