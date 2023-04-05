#pragma once
#include"myWindow.h"
#include"stateManager.h"

class Client;
class Player;

class Victory
{
protected:
	std::string stWin, stLoose, stPseudoWin, stRetourMenu;
	sf::Text txWin, txFin, txLoose;
	sf::Font fFin;

public:
	bool bReset;
	float timer;

	void init();
	void Update(Client& _client, Player& _player, myWindow& _window);
	void draw(myWindow& _window);
	void reset(Player& _player);

	void initFin(myWindow& _window) {
		fFin.loadFromFile("../Ressources/Fonts/Typewriter.ttf");

		stWin = { "Victoire !!! Felicitation "};
		stLoose = { "Perdu, vous ferez mieux la prochaine\n Felicitation a " };
		stRetourMenu = { "\nAppuyer sur Entrer pour retourner au menu" };

		txFin.setFont(fFin);
		txFin.setFillColor(sf::Color::Black);

		txLoose.setFont(fFin);
		txLoose.setFillColor(sf::Color::Black);

		txWin.setFont(fFin);
		txWin.setFillColor(sf::Color::Black);

	};
};

