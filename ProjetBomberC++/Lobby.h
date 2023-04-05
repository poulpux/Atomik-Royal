#pragma once
#include<iostream>
#include"myWindow.h"
class Client;
class Player;
class Lobby
{
protected:
	sf::Sprite sprite;
	sf::Texture text;
	sf::Text txt;
	sf::Font font;

public:
	Lobby();
	~Lobby() {};

	void draw(Client& _client, myWindow& _window, Player& _player);
};

