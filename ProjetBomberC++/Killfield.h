#pragma once
#include"myWindow.h"
#include<list>
#include<iostream>
#include"tools.h"

class Player;
class Client;
class Killfield
{
protected:
	sf::Texture text;
	sf::Sprite kill;
	sf::Text txt;
	sf::Font font;

	float timer;
	float TAffich;
	std::string tueur;
	std::string tuee;
public:
	Killfield();
	Killfield(std::string& _tueur, std::string& _tue);
	void Init();
	void Update();
	void ouiiiii();

	void Display(myWindow& _window,Player& _player, Client& _client);

	std::list<Killfield*>killList;


};

