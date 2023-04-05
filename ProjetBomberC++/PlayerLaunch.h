#pragma once
#include"myWindow.h"
#include<list>
class Host;
class Client;
//
//struct zonee
//{
//	int zone;
//	bool utilise;
//};

class PlayerLaunch
{
protected:
	sf::Vector2f pos;
public:
	void initposPlayer(Host& _host, Client& _client);
	void getPos(int& zone);
	std::list<int>listZone;
};

