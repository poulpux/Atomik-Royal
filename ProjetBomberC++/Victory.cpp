#include "Victory.h"
#include"Player.h"
#include"Client.h"


void Victory::init()
{
	txWin.setString("");
	bReset = false;
}

void Victory::Update(Client& _client, Player& _player, myWindow& _window)
{
	//std::cout << "Nb: " << _client.nbSurvivant << std::endl;
	if (_client.nbSurvivant <= 1)
	{
		if (_player.getState() == PLAYER)
		{
			stPseudoWin = _client.pseudo;
			txWin.setPosition(_window.getRenderWindow().mapPixelToCoords(sf::Vector2i(700, 500)));
			txFin.setPosition(_window.getRenderWindow().mapPixelToCoords(sf::Vector2i(700, 500)));
			txFin.setString(stWin + stPseudoWin + stRetourMenu);
			//txWin.setString(stWin + stPseudoWin);
			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
			bReset = true;
			//}
		}
		else
		{
			auto i = _client.Ennemies.begin(); auto n = _client.Ennemies.end();
			while (i != n)
			{
				if (!(*i)->dead) {
					stPseudoWin =  (*i)->username;
				}
				i++;
			}
			txLoose.setPosition(_window.getRenderWindow().mapPixelToCoords(sf::Vector2i(700, 500)));
			txFin.setPosition(_window.getRenderWindow().mapPixelToCoords(sf::Vector2i(700, 500)));
			txFin.setString(stLoose + stPseudoWin + stRetourMenu);
			//txLoose.setString(stLoose + stPseudoWin);
			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			bReset = true;
			//}
		}
	}
}

void Victory::draw(myWindow& _window)
{
	_window.Draw(txFin);
	/*_window.Draw(txWin);
	_window.Draw(txLoose);*/
}

void Victory::reset(Player& _player) {
}
