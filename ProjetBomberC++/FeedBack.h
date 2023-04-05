#pragma once
#include "tools.h"
#include "Player.h"
#include "Client.h"

class Player;

class FeedBack : public Client
{
protected:

	sf::Texture Inutile; //Ne SURTOUT pas toucher
	sf::Sprite Inutile2; //Idem

	sf::Texture TExplo;
	sf::Sprite SExplo;

	sf::Vector2f ScaleExplo = { 2,2 };
	sf::IntRect RectExplo = { 0,0,64,64 };

	float TimerBombe = 0.0f;
	int FrameExplo = 0;

	int i = 0;

public:

	FeedBack() {};
	~FeedBack() {};

	void initFeedBack();
	void updateFeedBack(Player& _player);
	void displayFeedBack(myWindow& _window,Player& _player);
};